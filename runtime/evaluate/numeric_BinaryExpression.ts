// deno-lint-ignore-file no-unused-vars
import { OperatorLiteral } from "../../frontend/ast.ts";
import { TokenType } from "../../frontend/lexer.ts";
import Enviroment from "../enviroment.ts";
import { MAKE_NULL, MAKE_NUMBER, NumberValue, RunTimeValue } from "../values.ts";

export function evaluate_numeric_BinaryExpression(leftHandSide:NumberValue,operator:OperatorLiteral,rightHandSide:NumberValue,env: Enviroment):RunTimeValue{
	switch(operator.Type){
		case TokenType.PLUS:{
			return MAKE_NUMBER(leftHandSide.Value+rightHandSide.Value);
		}		case TokenType.MINUS:{
			return MAKE_NUMBER(leftHandSide.Value-rightHandSide.Value);
		} 
		case TokenType.MULTIPLY:{
			return MAKE_NUMBER(leftHandSide.Value*rightHandSide.Value);
		} 
		case TokenType.DIVIDE:{
			return MAKE_NUMBER(leftHandSide.Value/rightHandSide.Value);
		}
		case TokenType.MODULUS:{
			return MAKE_NUMBER(leftHandSide.Value%rightHandSide.Value);
		}
		case TokenType.BIGGER:{
			if(leftHandSide.Value > rightHandSide.Value){return leftHandSide;}else{return rightHandSide;}
		}
		case TokenType.SMALLER:{
			if(leftHandSide.Value < rightHandSide.Value){return leftHandSide;}else{return rightHandSide;}
		}
		default:{
			return MAKE_NULL();
		}
	}
}
