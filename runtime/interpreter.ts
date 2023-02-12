// deno-lint-ignore-file no-unreachable
import { RunTimeValue, MAKE_NULL, _MAKE_BOOL, NumberValue } from "./values.ts"
import {   Word, Keyword, BinaryExpression, Program, Statement, NumericLiteral, VariableDeclaration, ObjectLiteral, Jointword } from "../frontend/ast.ts"
import Enviroment from "./enviroment.ts"
import { evaluate_BinaryExpression } from "./evaluate/BinaryExpression.ts";
import { evaluate_Program } from "./evaluate/Program.ts";
import { evaluate_VariableDeclaration } from "./evaluate/VariableDeclaration.ts";
import { evaluate_Word } from "./evaluate/Word.ts";
import { evaluate_Keyword, evaluate_SubKeyword } from "./evaluate/Keyword.ts";
import { evaluate_Jointword } from "./evaluate/Jointword.ts";
import { evaluate_ObjectExpression } from "./evaluate/ObjectExpression.ts";


export let Env=undefined

var CallChain:Enviroment[] = []
export function NowHere(Target:Enviroment){
	if(Env != undefined)CallChain.push(Env)
	Env=Target;
}

export function NowBack(){
	if(CallChain.length > 0){
		CallChain.reverse()
		Env = CallChain.shift();
		CallChain.reverse();
	}
}

export function evaluate(astNode: Statement,env?: Enviroment): RunTimeValue{
	if(Env == undefined){
		const nEnv=new Enviroment("Root");
		Enviroment.Add(nEnv);
		NowHere(nEnv);
	}
	switch(astNode.Kind){
		case "Program":{
			return evaluate_Program((astNode as Program),Env);
		}break;
		case "BinaryExpression":{
			return evaluate_BinaryExpression((astNode as BinaryExpression),Env);
		}break;
		case "NumericLiteral":{
			return {Value:((astNode as NumericLiteral).Value), Type: "number"} as NumberValue;
		}break;
		case "ObjectLiteral":{
			return evaluate_ObjectExpression((astNode as ObjectLiteral),Env);
		}break;
		case "Baseword":{
			switch(astNode.SubKind){
				case "Word":{
					return evaluate_Word((astNode as Word),Env);
				}break;
				case "Keyword":{
					return evaluate_Keyword((astNode as Keyword),Env);
				}break;
				case "Jointword":{
					if(astNode.Symbol.SubKind == "Keyword"){
						return evaluate_SubKeyword((astNode as Jointword),Env);
					}
					return evaluate_Jointword((astNode as Jointword),Env);
				}break;
				default:{
					return MAKE_NULL();
				}break;
			}
		}break;
		case "VariableDeclaration":{
			return evaluate_VariableDeclaration((astNode as VariableDeclaration),Env);
		}break;
		default:{
			console.log("Interpreter doesn't not what to do with this.");
			console.log(astNode);
			return MAKE_NULL();
		}break;
	}
}