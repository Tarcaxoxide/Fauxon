import Parser from "./frontend/parser.ts"
import { TypeToString } from "./frontend/lexer.ts";
import { evaluate } from "./runtime/interpreter.ts"
import Enviroment from "./runtime/enviroment.ts"
import { NumberValue, MAKE_NUMBER } from "./runtime/values.ts"

export async function run(filename:string) {
    const parser = new Parser();
    const srcCode = await Deno.readTextFile(filename)
    const program = parser.produceAST(srcCode);
    const results = evaluate(program);
    console.log(results);
}


export async function repl() {
    const parser = new Parser();
    while(!false){
        const input = prompt(":>");
        if(!input || input.includes("exit")){Deno.exit(0);}
        const program = parser.produceAST(input);
		const results = evaluate(program);
		console.log(results);
	}
}
