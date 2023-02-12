// deno-lint-ignore-file no-unused-vars
import { Keyword, Word, Jointword } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { MAKE_BOOL, MAKE_NULL, RunTimeValue } from "../values.ts";

export function evaluate_Jointword(word: Jointword ,env: Enviroment): RunTimeValue{
	const EnvName = word.Symbol.Symbol.Value
    const VarName = word.SecondSymbol.Value
    const Tenv = Enviroment.Find(EnvName);
    if(Tenv == undefined)return MAKE_NULL();
	return Tenv.LookupVariable(VarName);
}
