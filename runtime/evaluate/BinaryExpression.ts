import { BinaryExpression } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { NumberValue, RunTimeValue } from "../values.ts";
import { evaluate_BooleanMath } from "./BooleanMath.ts";
import { evaluate_numeric_BinaryExpression } from "./numeric_BinaryExpression.ts";

export function evaluate_BinaryExpression(binop:BinaryExpression,env: Enviroment): RunTimeValue{
	const leftHandSide = evaluate(binop.Left,env);
	const rightHandSide = evaluate(binop.Right,env);
	if(leftHandSide.Type == "number" && rightHandSide.Type == "number"){
		return evaluate_numeric_BinaryExpression(leftHandSide as NumberValue,binop.Operator,rightHandSide as NumberValue,env);
	}
	return evaluate_BooleanMath(binop,env);
}
