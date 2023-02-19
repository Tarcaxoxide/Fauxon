// deno-lint-ignore-file no-unused-vars
import { Keyword, Word, Jointword, VariableDeclaration } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { MAKE_BOOL, MAKE_NULL, RunTimeValue } from "../values.ts";

export function evaluate_Jointword(word: Jointword ,env: Enviroment): RunTimeValue{
	let EnvName;
    if(word.Symbol.Kind == "Token"){
        EnvName = word.Symbol.Value;
    }else if(word.Symbol.Kind == "Baseword"){
        EnvName = word.Symbol.Symbol.Value;
    }
    const VarName = word.SecondSymbol.Value;
    const Tenv = Enviroment.Find(EnvName);
    console.log
    if(Tenv == undefined)return MAKE_NULL();
	return Tenv.LookupVariable(VarName);
}
