import { run } from "./EntryPoints.ts"




for(const filename of Deno.args){
    run(`./${filename}`)
}