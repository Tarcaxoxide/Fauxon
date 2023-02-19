import { UnaryExpression, Word } from "../frontend/ast.ts";
import Enviroment from "./enviroment.ts";

// deno-lint-ignore-file no-explicit-any
export type ValueType = "number" | "boolean" | "word" | "jointword" | "object" | "nativefuncion";


// jointword is 'EnvironmentName::VariableName'

export interface RunTimeValue{
	Type: ValueType,
	Value: any,
}

export interface NumberValue extends RunTimeValue{
	Type: "number",
	Value: number
}

export interface BooleanValue extends RunTimeValue{
	Type: "boolean",
	Value: number
}

export interface WordValue extends RunTimeValue{
	Type: "word",
	Value: string
}

export interface ObjectValue extends RunTimeValue{
	Type: "object",
	Properties: Map<string,RunTimeValue>
}

export interface JointWordValue extends RunTimeValue{
	Type: "jointword",
	Value1: string,
	Value2: string,
}

export type FunctionCall = (Arguments:RunTimeValue[], env: Enviroment) => RunTimeValue;

export interface NativeFuncionValue extends RunTimeValue{
	Type:"nativefuncion",
	call:FunctionCall
}

// functions
export function MAKE_NUMBER(num = 0){
	return {Value: num, Type: "number"} as NumberValue;
}

export function _MAKE_BOOL(num: number):BooleanValue{
	if(num >0)num=1;
	if(num<0)num=-1;
	return {Value: num, Type: "boolean"} as BooleanValue;
}

export function MAKE_WORD(word: string){
	return {Value: word, Type: "word"} as WordValue;
}

export function MAKE_JOINTWORD(worda: string,wordb:string){
	return {Value1: worda, Value2: wordb, Type: "jointword"} as JointWordValue;
}

export function MAKE_NULL(){
	return _MAKE_BOOL(0);
}

export function MAKE_BOOL(b: boolean):BooleanValue{
	if(b)return _MAKE_BOOL(1);
	return _MAKE_BOOL(-1);
}
export function MAKE_NATIVE_FUNCTION(call:FunctionCall):NativeFuncionValue{
	return {Type:"nativefuncion",call} as NativeFuncionValue;
}