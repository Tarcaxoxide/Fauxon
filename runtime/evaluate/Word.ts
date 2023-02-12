// deno-lint-ignore-file no-unused-vars
import { Keyword, Word } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { MAKE_BOOL, MAKE_NULL, RunTimeValue } from "../values.ts";

export function evaluate_Word(word: Word ,env: Enviroment): RunTimeValue{
	const val = env.LookupVariable(word.Symbol.Value);
	return val;
}
