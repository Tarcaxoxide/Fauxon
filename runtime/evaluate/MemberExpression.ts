// deno-lint-ignore-file no-unused-vars

import { MemberExpression, Word } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { MAKE_NULL, ObjectValue, RunTimeValue } from "../values.ts";

export function evaluate_MemberExpression(exp: MemberExpression ,env: Enviroment): RunTimeValue{
    const obj = evaluate(exp.Object) as ObjectValue;
    const val = obj.Properties.get((exp.Property as Word).Symbol.Value)

    if(val == undefined)return MAKE_NULL();
    return val;
}


/*
{
  Kind: "MemberExpression",
  SubKind: "None",
  Object: {
    Kind: "Baseword",
    SubKind: "Word",
    Symbol: { Value: "testvar", Type: 4, Kind: "Token" }
  },
  Property: {
    Kind: "Baseword",
    SubKind: "Word",
    Symbol: { Value: "b", Type: 4, Kind: "Token" }
  },
  Computed: { Value: -1, Type: "boolean" }
}
*/

//??testvar.b

/*
{
  Type: "object",
  Properties: Map {
    { Value: "a", Type: 4, Kind: "Token" } => { Value: 10, Type: "number" },
    { Value: "b", Type: 4, Kind: "Token" } => { Value: 15, Type: "number" }
  }
}
*/