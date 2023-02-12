// deno-lint-ignore-file no-unreachable
import { Statement, Program, Expression, BinaryExpression, NumericLiteral, Keyword, Property, CallExpression, MemberExpression, ObjectLiteral } from "./ast.ts";
import { Token, TypeToString, tokenize, TokenType, IsIn } from "./lexer.ts";
import { MAKE_BOOL, MAKE_WORD, MAKE_JOINTWORD } from "../runtime/values.ts";
import { VariableDeclaration, Word, OperatorLiteral } from "./ast.ts";

export default class Parser{
    private tokens: Token[]=[];
    private at():Token{
        const tk = this.tokens[0] as Token;
        return tk;
    }
    private eat():Token{
        const tk:Token = this.tokens.shift() as Token;
        return tk;
    }
    private expect(type:TokenType, err:string): Token{
		const tk:Token = this.eat() as Token
		if(!tk || tk.Type != type){
			console.log("Parser error:\t[",err,"| Got:",TypeToString(tk.Type),"| Expected:",TypeToString(type),"]");
			Deno.exit(1);
		}
		return tk;
	}
    private not_eof():boolean{return (this.at().Type != TokenType.EOF);}

    public produceAST(sourceCode: string):Program{
        this.tokens = tokenize(sourceCode);
        const program:Program = {
            Kind: "Program",
            SubKind: "None",
            Body:[]
        }
        while(this.not_eof()){
            program.Body.push(this.parse_Statement(program));
        }
        return program;
    }

    private parse_Statement(prog:Program):Statement{
        return this.parse_Expression(prog);
    }
    private parse_Expression(prog:Program):Expression{
        switch(this.at().Type){
            case TokenType.EQUALS:{
                return this.parse_VariableDeclaration(prog);
            }break;
            case TokenType.LEFT_CURLYBRACE:{
                return this.parse_ObjectExpression(prog);
            }break;
            default:{
                return this.parse_AdditionExpression(prog);
            }break;
        }
    }
    private parse_VariableDeclaration(prog:Program):Statement{
        if(prog.Body.length < 1)throw "can't set a variable to nothing";
        const exp = prog.Body[prog.Body.length-1] as Expression;
        prog.Body.reverse().shift();
        prog.Body.reverse();
        this.expect(TokenType.EQUALS,'this should have been equals?');
        const ID = this.parse_PrimaryExpression(prog)
        if(ID.Kind != "Baseword" && ID.SubKind == "Word")throw 'a variable name as a word was expected.';
        let allcap = true;
        for(const Letter of (ID as Word).Symbol.Value ){
            if(IsIn(Letter,"abcdefghijklmnopqrstuvwxyz"))allcap=false;
        }
        if(this.at().Type != TokenType.COLON_COLON)return {Kind: "VariableDeclaration", Constant: MAKE_BOOL(allcap), Word: MAKE_WORD((ID as Word).Symbol.Value), Value: exp} as VariableDeclaration;
        return this.parse_JVariableDeclaration(prog,(ID as Word),(exp as Expression),allcap);
    }
    private parse_ObjectExpression(prog:Program):Expression{
        this.eat();
        const properties = new Array<Property>();
        while(this.not_eof() && this.at().Type != TokenType.RIGHT_CURLYBRACE){
            let _Value;
            if(this.at().Type == TokenType.LEFT_CURLYBRACE){
                _Value = this.parse_ObjectExpression(prog);
            }else{
                _Value = this.parse_PrimaryExpression(prog);
            }
            console.log(_Value)
            this.eat();
            const _Key = this.expect(TokenType.WORD,"Word as key expected.");
            if(this.at().Type != TokenType.RIGHT_CURLYBRACE)this.expect(TokenType.COMMA,"Comma seperator expected");
            properties.push({Kind:"Property", SubKind:"None", Key:_Key, Value:_Value} as Property);
        }
        this.expect(TokenType.RIGHT_CURLYBRACE,"Object not closed.");
        return { Kind:"ObjectLiteral", SubKind:"None", Properties: properties} as ObjectLiteral
    }
    private parse_JVariableDeclaration(prog:Program,EnvName:Word,exp:Expression,PrevAllCap:boolean):Statement{
        // EXP = EnvName(::)ID
        let allcap = PrevAllCap
        this.expect(TokenType.COLON_COLON,'this should have been COLON_COLON?');
        const ID = this.parse_PrimaryExpression(prog)
        for(const Letter of (ID as Word).Symbol.Value ){
            if(IsIn(Letter,"abcdefghijklmnopqrstuvwxyz"))allcap=false;
        }
        return {Kind: "VariableDeclaration", Constant: MAKE_BOOL(allcap), Word: MAKE_JOINTWORD((EnvName as Word).Symbol.Value,(ID as Word).Symbol.Value), Value: exp} as VariableDeclaration;
    }
    private parse_AdditionExpression(prog:Program):Expression{
        let left = this.parse_MultiplicationExpression(prog);
        while(this.at().Value == "+" || this.at().Value == "-" || this.at().Value == "<>" || this.at().Value == "><"){
            const operator = this.eat();
            const right = this.parse_MultiplicationExpression(prog);
            left = {
                Kind: "BinaryExpression",
                Left: left,
				Operator: ({Kind:"OperatorLiteral",Type:operator.Type} as OperatorLiteral),
				Right: right
            } as BinaryExpression
        }
        return left;
    }
    private parse_MultiplicationExpression(prog:Program):Expression{
        let left = this.parse_MemberCallExpression(prog);
        while(this.at().Value == "*" || this.at().Value == "/"|| this.at().Value == "%"){
            const operator = this.eat();
            const right = this.parse_MemberCallExpression(prog);
            left = {
                Kind: "BinaryExpression",
                Left: left,
				Operator: ({Kind:"OperatorLiteral",Type:operator.Type} as OperatorLiteral),
				Right: right
            } as BinaryExpression
        }
        return left;
    }
    private parse_MemberCallExpression(prog:Program):Expression{
        const member = this.parse_MemberExpression(prog)
        if(this.at().Type == TokenType.LEFT_PARENTHESIS){
            return this.parse_CallExpression(member,prog);
        }
        return member;
    }
    private parse_CallExpression(Caller:Expression,prog:Program):Expression{
        let call_expression: Expression = {
            Kind: "CallExpression",
            SubKind:"None",
            Caller,
            Arguments: this.parse_Arguments(prog)
        } as CallExpression
        if(this.at().Type == TokenType.LEFT_PARENTHESIS){
            call_expression = this.parse_CallExpression(call_expression,prog);
        }
        return call_expression;
    }
    private parse_Arguments(prog:Program):Expression[]{
        this.expect(TokenType.LEFT_PARENTHESIS,"Left parenthesis expected");
        const args = this.at().Type == TokenType.RIGHT_PARENTHESIS
        ? []
        : this.parse_Arguments_List(prog);
        this.expect(TokenType.RIGHT_PARENTHESIS,"Right parenthesis expected");
        return args;
    }
    private parse_Arguments_List(prog:Program):Expression[]{
        const args = [this.parse_Expression(prog)];
        while( this.at().Type == TokenType.COMMA && this.eat()){
            args.push(this.parse_Expression(prog));
        }
        return args;
    }
    private parse_MemberExpression(prog:Program):Expression{
        let Object = this.parse_PrimaryExpression(prog);
        while(this.at().Type == TokenType.DOT || this.at().Type == TokenType.LEFT_BRACE){
            const operator = this.eat();
            let Property:Expression
            let _Computed = false;
            // None computed values (DOT)
            if(operator.Type == TokenType.DOT){
                Property = this.parse_PrimaryExpression(prog)
                if(Property.Kind != "Baseword" || Property.SubKind != "Word"){
                    throw 'can not use dot operator when the right side is not a word';
                }

            }else{
                _Computed = true;
                Property = this.parse_Expression(prog);
                this.expect(TokenType.RIGHT_BRACE,"right brace expected to close member expression.");
            }
            Object = {Kind:"MemberExpression",SubKind:"None",Object,Property,Computed:MAKE_BOOL(_Computed)} as MemberExpression;
        }
        return Object;
    }
    //private parse_UnaryExpression(prog:Program):Expression{
    //    return this.parse_PrimaryExpression(prog);
    //}
    private parse_PrimaryExpression(prog:Program):Expression{
        const tt:TokenType = this.at().Type;
        switch(tt){
            case TokenType.WORD:{
                return {Kind: "Baseword", SubKind: "Word",Symbol: this.eat()} as Word;
            }break;
            case TokenType.COLON_COLON:{// ::
                this.eat()
                const SecondS = this.eat()
                let S = prog.Body[prog.Body.length-1] as Word;
                if(S.Kind == "BinaryExpression"){
                    S.Right = {Kind: "Baseword", SubKind: "Jointword",Symbol: S.Right, SecondSymbol: SecondS} as Jointword;
                    return S;
                }
                return {Kind: "Baseword", SubKind: "Jointword",Symbol: S, SecondSymbol: SecondS} as Jointword;
            }
            case TokenType.KEYWORD:{
                const _a = this.eat();
                let _b=this.at();
                if(_b.Value == "EOF"){_b=_a;}else{
                    _b = this.parse_Expression();
                }
                return {Kind: "Baseword",SubKind: "Keyword",Symbol: _a,Target: _b} as Keyword;
            }break;
            case TokenType.NUMBER:{
                return {Kind: "NumericLiteral",SubKind:"None",Value: parseFloat(this.eat().Value)} as NumericLiteral;
            }break;
            case TokenType.LEFT_PARENTHESIS:{
		    this.eat();// Parenthesis are delicious XD 
		    const value = this.parse_Expression(prog);
		    this.expect(TokenType.RIGHT_PARENTHESIS,"Missing Parenthesis");
		    return value;
	    }break;
	    default:{
                console.log("Unexpected token during parsing: {"+TypeToString(this.at().Type)+":"+this.at().Value+"}");
                Deno.exit(1);
            }break;
        }
    }
}