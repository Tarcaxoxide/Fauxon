import { CallExpression } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { MAKE_NULL, NativeFuncionValue, RunTimeValue } from "../values.ts";



export function evaluate_CallExpression(expr:CallExpression,env:Enviroment):RunTimeValue{
    const args = expr.Arguments.map((arg)=>evaluate(arg,env));
    const fun = evaluate(expr.Caller,env);

    if(fun.Type != "nativefuncion"){
        throw 'cannot call a value that is not a function.'+JSON.stringify(fun);
    }

    let ret = (fun as NativeFuncionValue).call(args,env);
    return ret;
}