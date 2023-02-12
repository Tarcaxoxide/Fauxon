import { VariableDeclaration } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { evaluate } from "../interpreter.ts";
import { JointWordValue, MAKE_NULL, RunTimeValue } from "../values.ts";

export function evaluate_VariableDeclaration(VarToSet:VariableDeclaration,env: Enviroment): RunTimeValue{
    const Valuetmp=VarToSet.Value;
    let Value;
    let ret;
    let Tenv=env
    if(Valuetmp != undefined)Value = evaluate(Valuetmp,Tenv);
    if(VarToSet.Word.Type == "jointword"){
        const EnvName = (VarToSet.Word as JointWordValue).Value1
        const VarName = (VarToSet.Word as JointWordValue).Value2
        Tenv = Enviroment.Find(EnvName);
        if(Tenv == undefined)Enviroment.New(EnvName)
        Tenv = Enviroment.Find(EnvName);
        if(Value == undefined){ret = Tenv.DeclareVariable(VarName,MAKE_NULL());}else{ret = Tenv.DeclareVariable(VarName,Value);}
        if(ret.Value == -1 && VarToSet.Constant.Value == -1){
            if(Value == undefined){ret = Tenv.AssignVariable(VarName,MAKE_NULL());}else{ret = Tenv.AssignVariable(VarName,Value);}
        }else if(ret.Value == -1 && VarToSet.Constant.Value == 1){
            return Tenv.LookupVariable(VarName);
        }
    }else{
        if(Value == undefined){ret = Tenv.DeclareVariable(VarToSet.Word.Value,MAKE_NULL());}else{ret = Tenv.DeclareVariable(VarToSet.Word.Value,Value);}
        if(ret.Value == -1 && VarToSet.Constant.Value == -1){
            if(Value == undefined){ret = Tenv.AssignVariable(VarToSet.Word.Value,MAKE_NULL());}else{ret = Tenv.AssignVariable(VarToSet.Word.Value,Value);}
        }else if(ret.Value == -1 && VarToSet.Constant.Value == 1){
            return Tenv.LookupVariable(VarToSet.Word.Value);
        }
    }

    if(Value != undefined)return Value;
    return MAKE_NULL();
}