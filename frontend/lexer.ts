import { KEYWORDS } from "../runtime/evaluate/Keyword.ts"

export enum TokenType{
	NULL
	,NUMBER
	,IDENTIFIER
	,EQUALS
	,WORD
	,KEYWORD
	,PLUS
	,MINUS
	,MULTIPLY
	,DIVIDE
	,PLUS_EQUALS
	,MINUS_EQUALS
	,MULTIPLY_EQUALS
	,DIVIDE_EQUALS
	,MODULUS
	,DOT
	,LESS
	,SMALLER
	,MORE
	,BIGGER
	,NOT
	,SEMICOLON
	,COLON
	,COLON_COLON
	,COMMA
	,EQUALS_EQUALS
	,LESS_EQUALS
	,MORE_EQUALS
	,NOT_EQUALS
	,MODULUS_EQUALS
	,LEFT_PARENTHESIS
	,RIGHT_PARENTHESIS
	,LEFT_BRACE
	,RIGHT_BRACE
	,LEFT_CURLYBRACE
	,RIGHT_CURLYBRACE
	,EOF
	,ERROR
}

// '10><5' -> '5'
// '10<>5' -> '5'

export interface Token{
 	Type: TokenType,
	Value: string;
}

export function token (Value = "", Type: TokenType): Token{
	return {Value, Type};
}

export function TypeToString(Type:TokenType): string{
	let result = ''
	switch(Type){
		case TokenType.NULL:{result="NULL";}break;
		case TokenType.NUMBER:{result="NUMBER";}break;
		case TokenType.IDENTIFIER:{result="IDENTIFIER";}break;
		case TokenType.EQUALS:{result="EQUALS";}break;
		case TokenType.WORD:{result="WORD";}break;
		case TokenType.KEYWORD:{result="KEYWORD";}break;
		case TokenType.PLUS:{result="PLUS";}break;
		case TokenType.MINUS:{result="MINUS";}break;
		case TokenType.MULTIPLY:{result="MULTIPLY";}break;
		case TokenType.DIVIDE:{result="DIVIDE";}break;
		case TokenType.PLUS_EQUALS:{result="PLUS_EQUALS";}break;
		case TokenType.MINUS_EQUALS:{result="MINUS_EQUALS";}break;
		case TokenType.MULTIPLY_EQUALS:{result="MULTIPLY_EQUALS";}break;
		case TokenType.DIVIDE_EQUALS:{result="DIVIDE_EQUALS";}break;
		case TokenType.MODULUS:{result="MODULUS";}break;
		case TokenType.DOT:{result="DOT";}break;
		case TokenType.LESS:{result="LESS";}break;
		case TokenType.SMALLER:{result="SMALLER";}break;
		case TokenType.MORE:{result="MORE";}break;
		case TokenType.BIGGER:{result="BIGGER"}break;
		case TokenType.NOT:{result="NOT";}break;
		case TokenType.SEMICOLON:{result="SEMICOLON";}break;
		case TokenType.COLON:{result="COLON";}break;
		case TokenType.COLON_COLON:{result="COLON_COLON";}break;
		case TokenType.COMMA:{result="COMMA";}break;
		case TokenType.EQUALS_EQUALS:{result="EQUALS_EQUALS";}break;
		case TokenType.LESS_EQUALS:{result="LESS_EQUALS";}break;
		case TokenType.MORE_EQUALS:{result="MORE_EQUALS";}break;
		case TokenType.NOT_EQUALS:{result="NOT_EQUALS";}break;
		case TokenType.MODULUS_EQUALS:{result="MODULUS_EQUALS";}break;
		case TokenType.LEFT_PARENTHESIS:{result="LEFT_PARENTHESIS";}break;
		case TokenType.RIGHT_PARENTHESIS:{result="RIGHT_PARENTHESIS";}break;
		case TokenType.LEFT_BRACE:{result="LEFT_BRACE";}break;
		case TokenType.RIGHT_BRACE:{result="RIGHT_BRACE";}break;
		case TokenType.LEFT_CURLYBRACE:{result="LEFT_CURLYBRACE";}break;
		case TokenType.RIGHT_CURLYBRACE:{result="RIGHT_CURLYBRACE";}break;
		case TokenType.EOF:{result="EOF";}break;
		case TokenType.ERROR:{result="ERROR";}break;
	}
	return result;
}
export function IsIn(Ta:string, Ar:string): boolean{
	for (const c of Ar.split('')){
		if(Ta == c)return true;
	}
	return false;
}

export function IsInKeywords(Ta:string): boolean{
	for (const z of KEYWORDS){
		if(z == Ta)return true;
		
	}
	return false;
}


export function tokenize (sourceCode: string): Token[]{
	const tokens = new Array<Token>();
	const zourceCode = sourceCode+'';
	const src = zourceCode.split("");
	while(src.length > 0){
		if(src[0].trim() === ''){
			src.shift();
			continue;
		}
		switch(src[0]){
			case '(':{
				tokens.push(token(src.shift(),TokenType.LEFT_PARENTHESIS));
			}break;
			case ')':{
				tokens.push(token(src.shift(),TokenType.RIGHT_PARENTHESIS));
			}break;
			case '[':{
				tokens.push(token(src.shift(),TokenType.LEFT_BRACE));
			}break;
			case ']':{
				tokens.push(token(src.shift(),TokenType.RIGHT_BRACE));
			}break;
			case '{':{
				tokens.push(token(src.shift(),TokenType.LEFT_CURLYBRACE));
			}break;
			case '}':{
				tokens.push(token(src.shift(),TokenType.RIGHT_CURLYBRACE));
			}break;
			case '+':{
				tokens.push(token(src.shift(),TokenType.PLUS));	
			}break;
			case '-':{
				tokens.push(token(src.shift(),TokenType.MINUS));
			}break;
			case '*':{
				tokens.push(token(src.shift(),TokenType.MULTIPLY));
			}break;
			case '/':{
				tokens.push(token(src.shift(),TokenType.DIVIDE));
			}break;
			case '!':{
				tokens.push(token(src.shift(),TokenType.NOT));
			}break;
			case ';':{
				tokens.push(token(src.shift(),TokenType.SEMICOLON));
			}break;
			case ':':{
				if(tokens.length == 0){
					tokens.push(token(src.shift(),TokenType.COLON));
					continue;
				}
				switch(tokens[tokens.length-1].Type){
					case TokenType.COLON:{
						tokens[tokens.length-1].Type = TokenType.COLON_COLON;
                        tokens[tokens.length-1].Value+=':';src.shift();
					}break;
					default:{
						tokens.push(token(src.shift(),TokenType.COLON));
					}break;
				}
			}break;
			case ',':{
				tokens.push(token(src.shift(),TokenType.COMMA));
			}break;
			case '>':{
				switch(tokens[tokens.length-1].Type){
					case TokenType.LESS:{ // '<>' == SMALLER
						tokens[tokens.length-1].Type = TokenType.SMALLER;
                        tokens[tokens.length-1].Value+='>';src.shift();
					}break;
					default:{
						tokens.push(token(src.shift(),TokenType.MORE));
					}break;
				}
			}break;
			case '<':{
				switch(tokens[tokens.length-1].Type){
					case TokenType.MORE:{ // '><' == BIGGER
						tokens[tokens.length-1].Type = TokenType.BIGGER;
						tokens[tokens.length-1].Value+='<';src.shift();
					}break;
					default:{
						tokens.push(token(src.shift(),TokenType.LESS));
					}break;
				}
			}break;
			case '%':{
				tokens.push(token(src.shift(),TokenType.MODULUS));
			}break;
			case '.':{
				tokens.push(token(src.shift(),TokenType.DOT));
			}break;
			case '=':{
				switch(tokens[tokens.length-1].Type){
					case TokenType.PLUS:{
						tokens[tokens.length-1].Type=TokenType.PLUS_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.MINUS:{
						tokens[tokens.length-1].Type=TokenType.MINUS_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.MULTIPLY:{
						tokens[tokens.length-1].Type=TokenType.MULTIPLY_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.DIVIDE:{
						tokens[tokens.length-1].Type=TokenType.DIVIDE_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.MORE:{
						tokens[tokens.length-1].Type=TokenType.MORE_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.LESS:{
						tokens[tokens.length-1].Type=TokenType.LESS_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.EQUALS:{
						tokens[tokens.length-1].Type=TokenType.EQUALS_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.NOT:{
						tokens[tokens.length-1].Type=TokenType.NOT_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					case TokenType.MODULUS:{
						tokens[tokens.length-1].Type=TokenType.MODULUS_EQUALS;
						tokens[tokens.length-1].Value+='=';src.shift()
					}break;
					default:{
						tokens.push(token(src.shift(),TokenType.EQUALS));
					}break;
				}
			}break;
			default:{
				
				if(IsIn(src[0],"0123456789")){
					let num_str = "";
					let dot_count = 0;
					while(IsIn(src[0],"0123456789.")){
						if(src[0] == '.'){
							if(dot_count == 1)break;
							dot_count++;
						}
						num_str+=src.shift();
					}
					tokens.push(token(num_str,TokenType.NUMBER));
				}else if(IsIn(src[0],"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_")){
					let word_str = "";
					while(IsIn(src[0],"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789")){
						word_str+=src.shift();
					}
					tokens.push(token(word_str,TokenType.WORD));
				}else{
					tokens.push(token("Unknown Character:"+src.shift()+"",TokenType.ERROR));
				}
				if(tokens[tokens.length-1].Type == TokenType.WORD && IsInKeywords(tokens[tokens.length-1].Value)){
					tokens[tokens.length-1].Type=TokenType.KEYWORD;
				}
			}break;
		}
	}
	tokens.push(token("EOF",TokenType.EOF,))
	return tokens;
}
