#include <Parse.hpp>

std::shared_ptr<Node::SegmentNode> Parse_Segment(const std::deque<Token::Token>& tokens){
	std::shared_ptr<Node::SegmentNode> Result = std::make_shared<Node::SegmentNode>();
	for(size_t i=0;i<tokens.size();i++){
		switch(tokens[i].Type){
			case Token::Type_en::comparison:{
				assert(Result->size()>0);
				auto leftSide = Result->pop_back();
				Result->push_back(std::make_shared<Node::ComarisonNode>(leftSide,tokens[i],std::make_shared<Node::ValueNode>(tokens[i+1])));
				if(2+i<tokens.size()&&!(tokens[i+2].Type==Token::Type_en::assignment||tokens[i+2].Type==Token::Type_en::equation||tokens[i+2].Type==Token::Type_en::comparison))i++;
			}break;
			case Token::Type_en::equation:{
				assert(1+i<tokens.size()&&(tokens[1+i].Type == Token::Type_en::identifier||tokens[1+i].Type == Token::Type_en::string||tokens[1+i].Type == Token::Type_en::strongstring||tokens[1+i].Type == Token::Type_en::weakstring||tokens[1+i].Type == Token::Type_en::number));
				assert(Result->size()>0);
				auto leftSide = Result->pop_back();
				Result->push_back(std::make_shared<Node::EquationNode>(leftSide,tokens[i],std::make_shared<Node::ValueNode>(tokens[i+1])));
				i++;
			}break;
			case Token::Type_en::assignment:{
				assert(1+i<tokens.size()&&tokens[1+i].Type == Token::Type_en::identifier);
				assert(Result->size()>0);
				auto leftSide = Result->pop_back();
				Result->push_back(std::make_shared<Node::AssignmentNode>(leftSide,tokens[i],std::make_shared<Node::ValueNode>(tokens[i+1])));
				if(2+i<tokens.size()&&!(tokens[i+2].Type==Token::Type_en::assignment||tokens[i+2].Type==Token::Type_en::equation||tokens[i+2].Type==Token::Type_en::comparison))i++;
			}break;
			default:{
				Result->push_back(std::make_shared<Node::ValueNode>(tokens[i]));
			}break;
		}
	}
	return Result;
}

std::shared_ptr<Node::BlockNode> Parse_Block(const std::deque<Token::Token>& tokens){
	std::shared_ptr<Node::BlockNode> Result = std::make_shared<Node::BlockNode>();
	std::deque<std::deque<Token::Token>> RawSegments;
	std::deque<Token::Token> CurrentRawSegment{};
	for(size_t i=0;i<tokens.size();i++){
		if(tokens[i].Type == Token::Type_en::brace && tokens[i].Value == "{"){
			for(;i<tokens.size();i++){
				CurrentRawSegment.push_back(tokens[i]);
				if(tokens[i].Type == Token::Type_en::brace && tokens[i].Value == "}")break;
			}
			RawSegments.push_back(CurrentRawSegment);
			CurrentRawSegment.clear();
		}
	}
	for(size_t i=0;i<RawSegments.size();i++){
		Result->push_back(Parse_Segment(RawSegments[i]));
	}
	return Result;
}



/*
{
	{
		{
			a + 10 + 2 / 6 = a
		} = [a]DoAthing[10] = a
	}
	DoAthing[3] = c
}

*/


namespace Node{
	Type_en ValueNode::type(){return Type_en::value;}
	Type_en PixelNode::type(){return Type_en::pixel;}
	Type_en ComarisonNode::type(){return Type_en::comarison;}
	Type_en AssignmentNode::type(){return Type_en::assignment;}
	Type_en EquationNode::type(){return Type_en::equation;}
	Type_en SegmentNode::type(){return Type_en::segment;}
	Type_en BlockNode::type(){return Type_en::block;}
	std::string ValueNode::str(){
		return m_value.Value;
	}

/*
uint8_t Color_Red;
uint8_t Color_Green;
uint8_t Color_Blue;
uint8_t Color_Alpha;
uint8_t Position_X;
uint8_t Position_Y;
uint8_t Position_Z;
uint8_t Position_Scalar;
*/

	std::string PixelNode::str(){
		return std::string("{")+std::string("Red ")+std::to_string(m_pixel.Color_Red)+std::string(":")+\
								std::string("Green ")+std::to_string(m_pixel.Color_Green)+std::string(":")+\
								std::string("Blue ")+std::to_string(m_pixel.Color_Blue)+std::string(":")+\
								std::string("Alpha ")+std::to_string(m_pixel.Color_Alpha)+std::string(",")+\
								std::string("X ")+std::to_string(m_pixel.Position_X)+std::string(":")+\
								std::string("Y ")+std::to_string(m_pixel.Position_Y)+std::string(":")+\
								std::string("Z ")+std::to_string(m_pixel.Position_Z)+std::string(":")+\
								std::string("Scalar ")+std::to_string(m_pixel.Position_Scalar)+std::string("}");
	}
	std::string ComarisonNode::str(){
		return m_leftSide->str()+std::string(" ")+m_operater.Value+std::string(" ")+m_rightSide->str();
	}
	std::string AssignmentNode::str(){
		return m_leftSide->str()+std::string(" ")+m_operater.Value+std::string(" ")+m_rightSide->str();
	}
	std::string EquationNode::str(){
		return m_leftSide->str()+std::string(" ")+m_operater.Value+std::string(" ")+m_rightSide->str();
	}
	std::string SegmentNode::str(){
		std::string Result="";
		for(size_t i=0;i<m_body.size();i++){
			Result+=m_body[i]->str();
			Result+=" ";
		}
		return Result;
	}
	std::string BlockNode::str(){
		std::string Result="";
		for(size_t i=0;i<m_body.size();i++){
			Result+=m_body[i]->str();
			Result+="\n";
		}
		return Result;
	}
	std::deque<std::shared_ptr<Node>> EquationNode::Flatten(){
		std::deque<std::shared_ptr<Node>> Result;
		if(m_leftSide->type() == Type_en::equation){
			std::deque<std::shared_ptr<Node>> tmpResult = as_equation(m_leftSide)->Flatten();
			do{
				Result.push_back(tmpResult.back());
				tmpResult.pop_back();
			}while(tmpResult.size());
			Result.push_back(std::make_shared<EquationNode>(std::make_shared<ValueNode>(Token::Token{Token::Type_en::nil,"..."}),m_operater,m_rightSide));
		}else{
			Result.push_back(std::make_shared<EquationNode>(m_leftSide,m_operater,m_rightSide));
		}
		return Result;
	}
};