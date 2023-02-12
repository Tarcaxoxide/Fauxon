import { BinaryExpression } from "../../frontend/ast.ts";
import { TokenType } from "../../frontend/lexer.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { MAKE_BOOL, MAKE_NULL, RunTimeValue } from "../values.ts";

export function evaluate_BooleanMath(binop:BinaryExpression,env: Enviroment):RunTimeValue{
	const leftHandSide = evaluate(binop.Left,env);
	const rightHandSide = evaluate(binop.Right,env);
	const operator = binop.Operator;
	if(leftHandSide.Type == "boolean" && leftHandSide.Value == 0)return MAKE_NULL();
	if(rightHandSide.Type == "boolean" && rightHandSide.Value == 0)return MAKE_NULL();
	switch(operator.Type){
		case TokenType.PLUS:{
			if(leftHandSide.Value >0 && rightHandSide.Value >0)return MAKE_BOOL(true);
			if(leftHandSide.Type == "boolean" && leftHandSide.Value >0)return MAKE_BOOL(true);
			return MAKE_BOOL(false);
		}
        case TokenType.MINUS:{
			if(leftHandSide.Type == "boolean")return leftHandSide;
			if(leftHandSide.Value >0 && rightHandSide.Value >0)return rightHandSide;
			return MAKE_BOOL((rightHandSide.Value >0));
		}
        case TokenType.MULTIPLY:{
			if(leftHandSide.Type == "boolean" && rightHandSide.Type != "boolean")return leftHandSide;
			if(leftHandSide.Type != "boolean" && rightHandSide.Type == "boolean")return rightHandSide;
			if(leftHandSide.Value != rightHandSide.Value)return MAKE_NULL();
			return leftHandSide;
		}
        case TokenType.DIVIDE:{
			if(leftHandSide.Type == "boolean" && rightHandSide.Type == "boolean" && rightHandSide.Value != leftHandSide.Value)return MAKE_NULL();
			if(rightHandSide.Type == "boolean" && leftHandSide.Type != "boolean")return MAKE_NULL();
			return leftHandSide;
		}
        case TokenType.MODULUS:{
			if(rightHandSide.Type == "boolean" && rightHandSide.Value>0)return leftHandSide;
			return MAKE_NULL();
		}
        case TokenType.BIGGER:{
			if(rightHandSide.Type == "boolean" && leftHandSide.Type == "boolean"){
				if(rightHandSide.Value > leftHandSide.Value){return rightHandSide;}else{return leftHandSide}
			}
			if(rightHandSide.Type == "boolean" && leftHandSide.Type != "boolean"){
				if(rightHandSide.Value>0){return rightHandSide}else{return leftHandSide}
			}
			if(rightHandSide.Type != "boolean" && leftHandSide.Type == "boolean"){
				if(leftHandSide.Value>0){return leftHandSide}else{return rightHandSide}
			}
		}break;
		case TokenType.SMALLER:{
			if(rightHandSide.Type == "boolean" && leftHandSide.Type == "boolean"){
				if(rightHandSide.Value < leftHandSide.Value){return rightHandSide;}else{return leftHandSide}
			}
			if(rightHandSide.Type == "boolean" && leftHandSide.Type != "boolean"){
				if(rightHandSide.Value<0){return rightHandSide}else{return leftHandSide}
			}
			if(rightHandSide.Type != "boolean" && leftHandSide.Type == "boolean"){
				if(leftHandSide.Value<0){return leftHandSide}else{return rightHandSide}
			}
		}break;
		default:{
			return MAKE_NULL();
		}	
    }
	return MAKE_NULL();
}
