// deno-lint-ignore-file no-empty-interface
import { Token, TokenType } from "./lexer.ts"
import { BooleanValue, WordValue, JointWordValue } from "../runtime/values.ts"

export type NodeType =
		| "Program"
		| "VariableDeclaration"
		| "NumericLiteral"
		| "OperatorLiteral"
		| "Baseword"
		| "Word"
		| "Keyword"
		| "BinaryExpression"
		| "UnaryExpression"
		| "ObjectLiteral"
		| "Property"
		| "MemberExpression"
		| "CallExpression"

export interface Statement{
	Kind: NodeType,
	SubKind: string
}

export interface Program extends Statement{
	Kind: "Program",
	SubKind: "None",
	Body: Statement[]
}

export interface VariableDeclaration extends Statement{
	Kind: "VariableDeclaration",
	SubKind: "None",
	Constant: BooleanValue,
	Word: WordValue|JointWordValue|UnaryExpression,
	Value?: Expression,
	Print:boolean
}

export interface Expression extends Statement{}

export interface OperatorLiteral extends Expression{
	Kind:"OperatorLiteral",
	SubKind: "None",
	Type:TokenType
}

export interface BinaryExpression extends Expression{
	Kind: "BinaryExpression",
	SubKind: "None",
	Left: Expression,
	Operator: OperatorLiteral,
	Right: Expression
}

export interface UnaryExpression extends Expression{
	Kind: "UnaryExpression",
	SubKind: "None",
	Operator: OperatorLiteral,
	Right: Expression
}

export interface CallExpression extends Expression{
	Kind: "CallExpression",
	SubKind: "None",
	Arguments: Expression[],
	Caller: Expression
}

export interface MemberExpression extends Expression{
	Kind: "MemberExpression",
	SubKind: "None",
	Object: Expression,
	Property: Expression,
	Computed: BooleanValue,
}

export interface ObjectLiteral extends Expression{
	Kind: "ObjectLiteral",
	SubKind: "None",
	Properties: Property[]
}

export interface Property extends Expression{
	Kind: "Property",
	SubKind: "None",
	Key: string,
	Value?: Expression
}

export interface Baseword extends Expression{
	Kind: "Baseword",
	SubKind: string,
	Symbol: Token
}

export interface Word extends Baseword{
	Kind: "Baseword",
	SubKind: "Word",
	Symbol: Token
}

export interface Jointword extends Baseword{
	Kind: "Baseword",
	SubKind: "Jointword",
	Symbol: Token,
	SecondSymbol: Token
}

export interface Keyword extends Baseword{
	Kind: "Baseword",
	SubKind: "Keyword",
	Symbol: Token,
	Target?: Expression
}

export interface NumericLiteral extends Expression{
	Kind: "NumericLiteral",
	Value: number
}