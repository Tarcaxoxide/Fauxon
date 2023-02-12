import { MAKE_BOOL, MAKE_NULL, RunTimeValue } from "./values.ts"


export default class Enviroment{
	private Parent?: Enviroment;
	static ALL: Map<string, Enviroment>;
	private Variables: Map<string, RunTimeValue>;
	private ID:string
	constructor(nID: string,ParentEnv?:Enviroment){
		this.ID=nID;
		this.Parent=ParentEnv
		this.Variables = new Map()
		if(this.Parent != undefined)console.log(`Enviroment ${this.Here()} created.`)
		this.SetVariable("TRUE",MAKE_BOOL(true));
		this.SetVariable("FALSE",MAKE_BOOL(false));
		this.SetVariable("NULL",MAKE_NULL());
	}
	public DeclareVariable(varname: string, varvalue: RunTimeValue): RunTimeValue{
		if(this.Variables.has(varname)){
			return MAKE_BOOL(false);
		}
		this.Variables.set(varname,varvalue);
		return MAKE_BOOL(true);
	}
	public AssignVariable(varname: string, varvalue: RunTimeValue): RunTimeValue{
		const env = this.resolve(varname);
		if(env == undefined)return MAKE_BOOL(false);
		env.Variables.set(varname,varvalue);
		return MAKE_BOOL(true);
	}
	public SetVariable(varname: string, varvalue: RunTimeValue){
		this.Variables.set(varname,varvalue);
	}
	public LookupVariable(varname: string): RunTimeValue{
		if(this.Variables.has(varname)){
			return this.Variables.get(varname);
		}
		return MAKE_NULL();
	}
	public resolve(varname:string):Enviroment|undefined{
		if(this.Variables.has(varname))return this;
		if(this.Parent == undefined)return undefined;
		return this.Parent.resolve(varname);
	}
	public Here(): string{
		return this.ID;
	}
	static Find(toID:string){
		if(this.ALL == undefined)this.ALL = new Map();
		return this.ALL.get(toID)
	}
	static New(nID:string){
		if(this.ALL == undefined)this.ALL = new Map();
		if(this.ALL.has(nID))return;
		const nEnviroment = new Enviroment(nID,this);
		this.ALL.set(nID,nEnviroment);
	}
	static List(){
		if(this.ALL == undefined)this.ALL = new Map();
		let ret=""
		for(const key of this.ALL.keys()){
			ret+=key+",";
		}
		return ret;
	}
	static Add(e:Enviroment){
		if(this.ALL == undefined)this.ALL = new Map();
		if(this.ALL.has(e.ID))return;
		this.ALL.set(e.ID,e);
	}
	static Delete(oID:string){
		if(this.ALL == undefined)this.ALL = new Map();
		if(!this.ALL.has(oID))return;
		this.ALL.delete(oID);
		console.log(`Enviroment ${oID} deleted.`)
	}
}
