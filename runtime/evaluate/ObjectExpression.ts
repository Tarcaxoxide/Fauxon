import { Expression, ObjectLiteral } from "../../frontend/ast.ts";
import { Token } from "../../frontend/lexer.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { MAKE_NULL, ObjectValue, RunTimeValue } from "../values.ts";


export function evaluate_ObjectExpression(obj:ObjectLiteral,env: Enviroment): RunTimeValue{
    const object = {Type:"object",Properties: new Map} as ObjectValue
    for(const {Key,Value} of obj.Properties){
      let RunTimeValue = MAKE_NULL();
      if(Value != undefined)RunTimeValue=evaluate(Value);
      object.Properties.set(Key,RunTimeValue);
    }
    return object;
}
