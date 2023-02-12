import { Program } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { RunTimeValue,MAKE_NULL } from "../values.ts";

export function evaluate_Program(program:Program,env: Enviroment): RunTimeValue{
	let lastEvaluated:RunTimeValue = MAKE_NULL();
	for (const statement of program.Body){
		lastEvaluated = evaluate(statement,env);
	}
	return lastEvaluated;
}