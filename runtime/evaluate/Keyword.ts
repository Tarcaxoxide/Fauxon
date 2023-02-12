// deno-lint-ignore-file no-unused-vars
import { Baseword, Jointword, Keyword, NumericLiteral, VariableDeclaration, Word } from "../../frontend/ast.ts";
import Enviroment from "../enviroment.ts";
import { RunTimeValue, MAKE_NULL, MAKE_BOOL, MAKE_WORD, MAKE_NUMBER } from "../values.ts";
import { TokenType, IsIn } from "../../frontend/lexer.ts"
import { NowHere, NowBack, Env, evaluate } from "../interpreter.ts"
import { evaluate_VariableDeclaration } from "./VariableDeclaration.ts";



export const KEYWORDS: string[]=[
	"TIME",
	"HELP",
	"ENV_HERE",
	"ENV_JUMP",
	"ENV_RETURN",
	"ENV_NEW",
	"ENV_DELETE",
	"ENV_LIST"
]

const KEYWORDS_DESCRIPTIONS:Record<string,string> = {
	"TIME"		:"A keyword equivalent to the current unix time",
	"HELP"		:"this",
	"ENV_HERE"	:"Displays the current environment",
	"ENV_JUMP"	:"Jumps to the given environment",
	"ENV_RETURN":"Returns to the previews environment",
	"ENV_NEW"	:"Creates a new environment",
	"ENV_DELETE":"Deletes an environment",
	"ENV_LIST"	:"Lists all current enviroments",
}


export function evaluate_SubKeyword(word: Jointword,env: Enviroment){
	const tag = {Kind: "Baseword", SubKind: "Jointword", Symbol: word.Symbol.Target.Symbol, SecondSymbol: word.SecondSymbol} as Jointword
	const keyworda = {Kind: "Baseword", SubKind: "Keyword", Symbol: word.Symbol.Symbol, Target: tag} as Keyword
	return evaluate_Keyword(keyworda,env);
}

export function evaluate_Keyword(word: Keyword ,env: Enviroment): RunTimeValue{
	switch(word.Symbol.Value){
		case "HELP":{
			let retstring=""
			if(word.Target.Target){
				retstring = KEYWORDS_DESCRIPTIONS[word.Target.Target.Value];
				return MAKE_WORD(retstring);
			}
			for(const Fun of KEYWORDS){
				retstring+=Fun+",";
			}
			return MAKE_WORD(retstring);
		}
		case "TIME":{
			const val = MAKE_NUMBER(Date.now())
			if(word.Target != undefined && word.Target.Kind == "Baseword" && word.Target.SubKind == "Word"){
				const exp = { Kind: "NumericLiteral", Value: val.Value } as NumericLiteral;
				const ID = word.Target;
				let allcap = true;
        		for(const Letter of (ID as Word).Symbol.Value ){
        		    if(IsIn(Letter,"abcdefghijklmnopqrstuvwxyz"))allcap=false;
        		}
				const Request = {Kind: "VariableDeclaration", Constant: MAKE_BOOL(allcap), Word: MAKE_WORD((ID as Word).Symbol.Value), Value: exp} as VariableDeclaration;
				return evaluate_VariableDeclaration(Request,env);
			}
			if(word.Target != undefined && word.Target.Kind == "Baseword" && word.Target.SubKind == "Jointword"){
				const exp = { Kind: "NumericLiteral", Value: val.Value } as NumericLiteral;
				const EnvName = (word.Target as Jointword).Symbol.Value
				const VarName = (word.Target as Jointword).SecondSymbol.Value
        		let Tenv = Enviroment.Find(EnvName);
        		if(Tenv == undefined)Enviroment.New(EnvName)
        		Tenv = Enviroment.Find(EnvName);
        		let allcap = true;
        		for(const Letter of VarName){
        		    if(IsIn(Letter,"abcdefghijklmnopqrstuvwxyz"))allcap=false;
        		}
				const Request = {Kind: "VariableDeclaration", Constant: MAKE_BOOL(allcap), Word: MAKE_WORD(VarName), Value: exp} as VariableDeclaration;
				return evaluate_VariableDeclaration(Request,Tenv);
			}
			return val;
		}
		case "ENV_HERE":{
			return MAKE_WORD(Env.Here());
		}
		case "ENV_RETURN":{
			NowBack();
			if(word.Target != undefined && word.Target.Kind == "Baseword" && word.Target.SubKind == "Word"){
				const VarName = (word.Target as Jointword).Symbol.Value
				const VarValue = env.LookupVariable(VarName);
				if(VarValue != undefined)Env.SetVariable(VarName,VarValue);
		   	}
			return MAKE_WORD(Env.Here());
		}
		case "ENV_JUMP":{
			if(word.Target != undefined && word.Target.Kind == "Baseword"){
				const tmp = Enviroment.Find(word.Target.Symbol.Value);
				if(tmp != undefined)NowHere(tmp);
			}
			return MAKE_WORD(Env.Here());
		}
		case "ENV_NEW":{
			if(word.Target != undefined && word.Target.Kind == "Baseword"){
				Enviroment.New(word.Target.Symbol.Value);
			}
			return MAKE_WORD(Enviroment.List());
		}
		case "ENV_DELETE":{
			if(word.Target != undefined && word.Target.Kind == "Baseword"){
				Enviroment.Delete(word.Target.Symbol.Value);
			}
			return MAKE_WORD(Enviroment.List());
		}
		case "ENV_LIST":{
			return MAKE_WORD(Enviroment.List());
		}
        default:{
			return MAKE_NULL();
		}
    }
}