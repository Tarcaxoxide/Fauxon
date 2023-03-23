#pragma once
#include <string>
#include <deque>

namespace Token{
	enum Type_en{
		nil,
		identifier,
		weakstring,
		strongstring,
		string,
		number,
		brace,
		assignment,
		equation,
		comparison,
		pixel
	};
	struct Token{
		Type_en Type;
		std::string Value;
	};
	inline std::string ToString(Token t){
		std::string Result="";
		switch(t.Type){
			case Type_en::nil:{Result+="<nil: ";}break;
			case Type_en::identifier:{Result+="<identifier: ";}break;
			case Type_en::weakstring:{Result+="<weakstring: ";}break;
			case Type_en::strongstring:{Result+="<strongstring: ";}break;
			case Type_en::string:{Result+="<string: ";}break;
			case Type_en::number:{Result+="<number: ";}break;
			case Type_en::brace:{Result+="<brace: ";}break;
			case Type_en::assignment:{Result+="<assignment: ";}break;
			case Type_en::equation:{Result+="<equation: ";}break;
			case Type_en::comparison:{Result+="<comparison: ";}break;
			case Type_en::pixel:{Result+="<pixel: ";}break;
		}
		Result+=t.Value;
		Result+=">";
		return Result;
	}
};

std::deque<Token::Token> Tokenize(const std::string& src);
