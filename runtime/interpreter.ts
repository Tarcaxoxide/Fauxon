// deno-lint-ignore-file no-unreachable
import { RunTimeValue, MAKE_NULL, _MAKE_BOOL, NumberValue, NativeFuncionValue } from "./values.ts"
import {   Word, Keyword, BinaryExpression, Program, Statement, NumericLiteral, VariableDeclaration, ObjectLiteral, Jointword, CallExpression, UnaryExpression, MemberExpression } from "../frontend/ast.ts"
import Enviroment from "./enviroment.ts"
import { evaluate_BinaryExpression } from "./evaluate/BinaryExpression.ts";
import { evaluate_Program } from "./evaluate/Program.ts";
import { evaluate_VariableDeclaration } from "./evaluate/VariableDeclaration.ts";
import { evaluate_Word } from "./evaluate/Word.ts";
import { evaluate_Keyword, evaluate_SubKeyword } from "./evaluate/Keyword.ts";
import { evaluate_Jointword } from "./evaluate/Jointword.ts";
import { evaluate_ObjectExpression } from "./evaluate/ObjectExpression.ts";
import { evaluate_CallExpression } from "./evaluate/CallExpression.ts";
import { evaluate_UnaryExpression } from "./evaluate/UnaryExpression.ts";
import { evaluate_MemberExpression } from "./evaluate/MemberExpression.ts";


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
		}
		case "BinaryExpression":{
			return evaluate_BinaryExpression((astNode as BinaryExpression),Env);
		}
		case "NumericLiteral":{
			return {Value:((astNode as NumericLiteral).Value), Type: "number"} as NumberValue;
		}
		case "ObjectLiteral":{
			return evaluate_ObjectExpression((astNode as ObjectLiteral),Env);
		}
		case "Baseword":{
			switch(astNode.SubKind){
				case "Word":{
					return evaluate_Word((astNode as Word),Env);
				}
				case "Keyword":{
					return evaluate_Keyword((astNode as Keyword),Env);
				}
				case "Jointword":{
					if(astNode.Symbol.SubKind == "Keyword"){
						return evaluate_SubKeyword((astNode as Jointword),Env);
					}
					return evaluate_Jointword((astNode as Jointword),Env);
				}
				default:{
					return MAKE_NULL();
				}
			}
		}break;
		case "VariableDeclaration":{
			return evaluate_VariableDeclaration((astNode as VariableDeclaration),Env);
		}
		case "CallExpression":{
			return evaluate_CallExpression((astNode as CallExpression),Env);
		}
		case "UnaryExpression":{
			return evaluate_UnaryExpression((astNode as UnaryExpression),Env);
		}
		case "MemberExpression":{
			return evaluate_MemberExpression((astNode as MemberExpression),Env);
		}break;
		default:{
			console.log("Interpreter doesn't not what to do with this.");
			console.log(astNode);
			return MAKE_NULL();
		}
	}
}