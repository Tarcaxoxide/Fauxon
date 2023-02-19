// deno-lint-ignore-file no-unused-vars
import { Keyword, Word, Jointword, UnaryExpression, OperatorLiteral, NumericLiteral } from "../../frontend/ast.ts";
import { TokenType } from "../../frontend/lexer.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { MAKE_BOOL, MAKE_NULL, RunTimeValue } from "../values.ts";

export function evaluate_UnaryExpression(unary: UnaryExpression ,env: Enviroment): RunTimeValue{
    switch(unary.Operator.Type){
        case TokenType.PLUS:{
            if(unary.Right.Kind == "NumericLiteral")(unary.Right as NumericLiteral).Value = +(unary.Right as NumericLiteral).Value;
        }break;
        case TokenType.MINUS:{
            if(unary.Right.Kind == "NumericLiteral"){
                (unary.Right as NumericLiteral).Value = +(unary.Right as NumericLiteral).Value;
            }
        }break;
        case TokenType.QUESTION_MARK:{
            const V = evaluate(unary.Right);
            console.log(V);
        }break;
        default:{}break;
    }
	
	return evaluate(unary.Right);
}


/*
{
  Kind: "UnaryExpression",
  SubKind: "None",
  Operator: { Kind: "OperatorLiteral", SubKind: "None", Type: 16 },
  Right: { Kind: "NumericLiteral", SubKind: "None", Value: 90 }
}
*/