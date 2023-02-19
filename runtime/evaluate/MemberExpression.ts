// deno-lint-ignore-file no-unused-vars

import { Jointword, MemberExpression, Word } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { MAKE_NULL, ObjectValue, RunTimeValue } from "../values.ts";
import { evaluate_Jointword } from "./Jointword.ts";
import { evaluate_Word } from "./Word.ts";

export function evaluate_MemberExpression(exp: MemberExpression ,env: Enviroment): RunTimeValue{
  let obj;


  if(exp.Object.SubKind == "Word")obj = evaluate_Word((exp.Object as Word),env) as ObjectValue;
  if(exp.Object.SubKind == "Jointword")obj = evaluate_Jointword((exp.Object as Jointword),env) as ObjectValue;
  const val = obj.Properties.get((exp.Property as Word).Symbol.Value)

  if(val == undefined)return MAKE_NULL();
  return val;
}
