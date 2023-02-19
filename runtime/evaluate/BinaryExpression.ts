import { BinaryExpression, Jointword } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { NumberValue, RunTimeValue } from "../values.ts";
import { evaluate_BooleanMath } from "./BooleanMath.ts";
import { evaluate_Jointword } from "./Jointword.ts";
import { evaluate_numeric_BinaryExpression } from "./numeric_BinaryExpression.ts";

export function evaluate_BinaryExpression(binop:BinaryExpression,env: Enviroment): RunTimeValue{
	let leftHandSide;
	let rightHandSide;
	if(binop.Left.SubKind == "None"){
		leftHandSide = evaluate(binop.Left,env);
	}else if(binop.Left.SubKind == "Jointword"){
		leftHandSide = evaluate_Jointword((binop.Left as Jointword),env);
	}else{
		leftHandSide = evaluate(binop.Left,env);
	}

	if(binop.Right.SubKind == "None"){
		rightHandSide = evaluate(binop.Right,env);
	}else if(binop.Right.SubKind == "Jointword"){
		rightHandSide = evaluate_Jointword((binop.Right as Jointword),env);
	}else{
		rightHandSide = evaluate(binop.Right,env);
	}

	if(leftHandSide.Type == "number" && rightHandSide.Type == "number"){
		return evaluate_numeric_BinaryExpression(leftHandSide as NumberValue,binop.Operator,rightHandSide as NumberValue,env);
	}
	return evaluate_BooleanMath(binop,env);
}
