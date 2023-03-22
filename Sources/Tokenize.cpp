#include <Tokenize.hpp>

bool Match(char Char,std::deque<char>& Targets){
	for(size_t i=0;i<Targets.size();i++)if(Targets[i] == Char)return true;
	return false;
}
bool NotMatch(char Char,std::deque<char>& Targets){
	for(size_t i=0;i<Targets.size();i++)if(Targets[i] == Char)return false;
	return true;
}
std::string UntilMatch(const std::string& src,size_t& Index,std::deque<char> Targets,bool included){
	size_t start=Index;
	while(++Index<src.size()&&NotMatch(src[Index],Targets));
	size_t length = Index-start;
	return src.substr(start,length+included);
}
std::string UntilNotMatch(const std::string& src,size_t& Index,std::deque<char> Targets,bool included){
	size_t start=Index;
	while(++Index<src.size()&&Match(src[Index],Targets));
	size_t length = Index-start;
	return src.substr(start,length+included);
}

std::deque<Token::Token> Tokenize(const std::string& src){
	std::deque<Token::Token> Result;
	size_t Index{0};
	std::string DefaultBuffer="";
	for(;Index<src.size();Index++){
		switch(src[Index]){
			case '\n':case '\t':case '\r':case ' ':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
			}break;
			case '(':case ')':case '{':case '}':case '[':case ']':case '<':case '>':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				Result.push_back({Token::Type_en::brace,src.substr(Index,1)});
			}break;
			case '+':case '-':case '*':case '/':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				Result.push_back({Token::equation,src.substr(Index,1)});
			}break;
			case '!':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				Result.push_back({Token::identifier,src.substr(Index,1)});
			}break;
			case '=':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				Token::Token result{Token::Type_en::assignment,"="};
				if(++Index<src.size()&&(src[Index]=='<'||src[Index]=='>'||src[Index]=='+'||src[Index]=='-'||src[Index]=='*'||src[Index]=='/')){result.Value+=src[Index];}else{Index--;}
				Result.push_back(result);
			}break;
			case '?':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				Token::Token result{Token::Type_en::comparison,"?"};
				if(++Index<src.size()&&(src[Index]=='<'||src[Index]=='>'||src[Index]=='=')){result.Value+=src[Index];}else{Index--;}
				Result.push_back(result);
			}break;
			case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':{
				if(Index+2<src.size()&&src[Index]=='.'&&src[Index+1]=='.'&&src[Index+2]=='.'){
					Result.push_back({Token::Type_en::identifier,"..."});
					Index+=2;
					break;
				}else if(Index+1<src.size()&&src[Index]=='.'&&src[Index+1]=='.'){
					Result.push_back({Token::Type_en::identifier,".."});
					Index++;
					break;
				}
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				std::string result = (UntilNotMatch(src,Index,{'0','1','2','3','4','5','6','7','8','9','.'},false));
				Result.push_back({Token::Type_en::number,result});
				Index--;
			}break;
			case '"':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				std::string result = (UntilMatch(src,Index,{'"'},true));
				Result.push_back({Token::Type_en::string,result});
			}break;
			case '\'':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				std::string result = (UntilMatch(src,Index,{'\''},true));
				Result.push_back({Token::Type_en::strongstring,result});
			}break;
			case '`':{
				if(DefaultBuffer.size()){
					Result.push_back({Token::Type_en::identifier,DefaultBuffer});
					DefaultBuffer="";
				}
				std::string result = (UntilMatch(src,Index,{'`'},true));
				Result.push_back({Token::Type_en::weakstring,result});
			}break;
			default:{
				DefaultBuffer+=src[Index];
			}break;
		}
	}
	if(DefaultBuffer.size()){
		Result.push_back({Token::Type_en::identifier,DefaultBuffer});
		DefaultBuffer="";
	}
	return Result;
}
