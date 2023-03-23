#pragma once
#include <string>
#include <deque>
#include <Tokenize.hpp>
#include <memory>
#include <cassert>


namespace Node{
	enum Type_en{
		value,
		pixel,
		comarison,
		assignment,
		equation,
		segment,
		block
	};
	class Node{
		public:
			virtual Type_en type() = 0;
			virtual std::string str() = 0;
	};
	class ValueNode:public Node{
		public:
			ValueNode(Token::Token value):m_value(value){}
			virtual Type_en type();
			virtual std::string str();
			inline Token::Token expose(){return m_value;}
		protected:
			Token::Token m_value;
	};
	class PixelNode:public ValueNode{
		public:
			//A.B.C.D.E.F.G.H
			struct PixelStructure{
				uint8_t Color_Red;			//A
				uint8_t Color_Green;		//B
				uint8_t Color_Blue;			//C
				uint8_t Color_Alpha;		//D
				uint8_t Position_X;			//E
				uint8_t Position_Y;			//F
				uint8_t Position_Z;			//G
				uint8_t Position_Scalar;	//H
			}__attribute__((packed));
			PixelNode(PixelStructure pixel):m_pixel(pixel),ValueNode(Token::Token{Token::Type_en::pixel,""}){
				m_value.Value=str();
			}
			PixelNode(uint64_t pixel):m_pixel(*(PixelStructure*)&pixel),ValueNode(Token::Token{Token::Type_en::pixel,""}){
				m_value.Value=str();
			}
			virtual Type_en type();
			virtual std::string str();
			
			inline PixelStructure expose(){return m_pixel;}
		protected:
			PixelStructure m_pixel;
	};
	class ComarisonNode:public Node{
		public:
			ComarisonNode(std::shared_ptr<Node> leftSide,Token::Token operater,std::shared_ptr<ValueNode> rightSide):m_leftSide(leftSide),m_operater(operater),m_rightSide(rightSide){}
			virtual Type_en type();
			virtual std::string str();
		protected:
			std::shared_ptr<Node> m_leftSide;
			Token::Token m_operater;
			std::shared_ptr<ValueNode> m_rightSide;
	};
	class AssignmentNode:public Node{
		public:
			AssignmentNode(std::shared_ptr<Node> leftSide,Token::Token operater,std::shared_ptr<ValueNode> rightSide):m_leftSide(leftSide),m_operater(operater),m_rightSide(rightSide){}
			virtual Type_en type();
			virtual std::string str();
			struct e{std::shared_ptr<Node> left;Token::Token operater;std::shared_ptr<Node> right;}; 
			e expose(){return{m_leftSide,m_operater,m_rightSide};}
		protected:
			std::shared_ptr<Node> m_leftSide;
			Token::Token m_operater;
			std::shared_ptr<ValueNode> m_rightSide;
	};
	class EquationNode:public Node{
		public:
			EquationNode(std::shared_ptr<Node> leftSide,Token::Token operater,std::shared_ptr<Node> rightSide):m_leftSide(leftSide),m_operater(operater),m_rightSide(rightSide){}
			virtual Type_en type();
			virtual std::string str();
			std::deque<std::shared_ptr<Node>> Flatten();
			struct e{std::shared_ptr<Node> left;Token::Token operater;std::shared_ptr<Node> right;}; 
			e expose(){return{m_leftSide,m_operater,m_rightSide};}
		protected:
			std::shared_ptr<Node> m_leftSide;
			Token::Token m_operater;
			std::shared_ptr<Node> m_rightSide;
	};
	class SegmentNode:public Node{
		public:
			SegmentNode():m_body({}){}
			virtual Type_en type();
			virtual std::string str();
			inline void push_back(std::shared_ptr<Node> node){m_body.push_back(node);}
			inline std::shared_ptr<Node> pop_back(){std::shared_ptr<Node> node=m_body.back();m_body.pop_back();return node;}
			inline void push_front(std::shared_ptr<Node> node){m_body.push_front(node);}
			inline std::shared_ptr<Node> pop_front(){std::shared_ptr<Node> node=m_body.front();m_body.pop_front();return node;}
			inline std::shared_ptr<Node> peek(size_t at){return m_body.at(at);}
			inline std::shared_ptr<Node> front(){return peek(0);}
			inline size_t size(){return m_body.size();}
			inline std::shared_ptr<Node> back(){return peek(size()-1);}
		protected:
			std::deque<std::shared_ptr<Node>> m_body;
	};
	class BlockNode:public Node{
		public:
			BlockNode():m_body({}){}
			virtual Type_en type();
			virtual std::string str();
			inline void push_back(std::shared_ptr<SegmentNode> node){m_body.push_back(node);}
			inline std::shared_ptr<SegmentNode> pop_back(){std::shared_ptr<SegmentNode> node=m_body.back();m_body.pop_back();return node;}
			inline void push_front(std::shared_ptr<SegmentNode> node){m_body.push_front(node);}
			inline std::shared_ptr<SegmentNode> pop_front(){std::shared_ptr<SegmentNode> node=m_body.front();m_body.pop_front();return node;}
			inline std::shared_ptr<SegmentNode> peek(size_t at){return m_body.at(at);}
			inline std::shared_ptr<SegmentNode> front(){return peek(0);}
			inline size_t size(){return m_body.size();}
			inline std::shared_ptr<SegmentNode> back(){return peek(size()-1);}
		protected:
			std::deque<std::shared_ptr<SegmentNode>> m_body;
	};

	inline std::shared_ptr<Node> as_generic(std::shared_ptr<Node> that){return that;}
	inline std::shared_ptr<Node> as_generic(std::shared_ptr<ValueNode> that){return std::static_pointer_cast<Node>(that);}
	inline std::shared_ptr<Node> as_generic(std::shared_ptr<ComarisonNode> that){return std::static_pointer_cast<Node>(that);}
	inline std::shared_ptr<Node> as_generic(std::shared_ptr<AssignmentNode> that){return std::static_pointer_cast<Node>(that);}
	inline std::shared_ptr<Node> as_generic(std::shared_ptr<EquationNode> that){return std::static_pointer_cast<Node>(that);}
	inline std::shared_ptr<Node> as_generic(std::shared_ptr<SegmentNode> that){return std::static_pointer_cast<Node>(that);}
	inline std::shared_ptr<ValueNode> as_value(std::shared_ptr<Node> that){return std::static_pointer_cast<ValueNode>(that);}
	inline std::shared_ptr<ValueNode> as_value(std::shared_ptr<PixelNode> that){return std::static_pointer_cast<ValueNode>(that);}
	inline std::shared_ptr<PixelNode> as_pixel(std::shared_ptr<ValueNode> that){return std::static_pointer_cast<PixelNode>(that);}
	inline std::shared_ptr<ComarisonNode> as_comarison(std::shared_ptr<Node> that){return std::static_pointer_cast<ComarisonNode>(that);}
	inline std::shared_ptr<AssignmentNode> as_assignment(std::shared_ptr<Node> that){return std::static_pointer_cast<AssignmentNode>(that);}
	inline std::shared_ptr<EquationNode> as_equation(std::shared_ptr<Node> that){return std::static_pointer_cast<EquationNode>(that);}
	inline std::shared_ptr<SegmentNode> as_segment(std::shared_ptr<Node> that){return std::static_pointer_cast<SegmentNode>(that);}
};


std::shared_ptr<Node::SegmentNode> Parse_Segment(const std::deque<Token::Token>& tokens);
std::shared_ptr<Node::BlockNode> Parse_Block(const std::deque<Token::Token>& tokens);