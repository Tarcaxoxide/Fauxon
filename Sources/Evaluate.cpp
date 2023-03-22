#include <Evaluate.hpp>
#include <iostream>
#include <deque>

std::deque<std::shared_ptr<Node::ValueNode>> global_stack;

struct Enviroment{
	std::deque<std::shared_ptr<Node::ValueNode>> local_stack;
	std::deque<std::shared_ptr<Node::ValueNode>> VariableNames;
	std::deque<std::shared_ptr<Node::ValueNode>> VariableValues;
	void Set(std::shared_ptr<Node::ValueNode> value,std::shared_ptr<Node::ValueNode> name){
		if(name->expose().Value == "..."){
			local_stack.push_back(value);
			return;
		}else if(name->expose().Value == ".."){
			global_stack.push_back(value);
			return;
		}
		for(size_t i=0;i<VariableValues.size();i++){
			if(name->expose().Value == VariableNames[i]->expose().Value){
				VariableValues[i]=value;
				return;
			}
		}
		VariableNames.push_back(name);
		VariableValues.push_back(value);
	}
	std::shared_ptr<Node::ValueNode> Get(std::shared_ptr<Node::ValueNode> name){
		if(name->expose().Value == "..."){
			std::shared_ptr<Node::ValueNode> Result = local_stack.back();
			local_stack.pop_back();
			return Result;
		}else if(name->expose().Value == ".."){
			std::shared_ptr<Node::ValueNode> Result = global_stack.back();
			global_stack.pop_back();
			return Result;
		}
		for(size_t i=0;i<VariableValues.size();i++){
			if(name->expose().Value == VariableNames[i]->expose().Value){
				return VariableValues[i];
			}
		}
		return std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,"0"});
	}
};

void Eval_Equation(Enviroment*& SegmentEnviroment,std::shared_ptr<Node::Node>& currentInstruction){
	if(currentInstruction->type() == Node::Type_en::value){
		SegmentEnviroment->local_stack.push_back(Node::as_value(currentInstruction));
		return;
	}
	std::deque<std::shared_ptr<Node::Node>> FlatEquation = Node::as_equation(currentInstruction)->Flatten();
	for(size_t i=0;i<FlatEquation.size();i++){
		auto equate = as_equation(FlatEquation[i])->expose();
		auto left = equate.left;
		auto operater = equate.operater;
		auto right = equate.right;
		while(left->type()==Node::Type_en::value&&Node::as_value(left)->expose().Type==Token::Type_en::identifier){
			left=SegmentEnviroment->Get(Node::as_value(left));
		}
		while(right->type()==Node::Type_en::value&&Node::as_value(right)->expose().Type==Token::Type_en::identifier){
			right=SegmentEnviroment->Get(Node::as_value(right));
		}
		assert(left->type()==Node::Type_en::value&&Node::as_value(left)->expose().Type==Token::Type_en::number);
		assert(right->type()==Node::Type_en::value&&Node::as_value(right)->expose().Type==Token::Type_en::number);
		switch(operater.Value[0]){
			case '+':{
				int64_t Result = std::stoll(Node::as_value(left)->expose().Value)+std::stoll(Node::as_value(right)->expose().Value);
				SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
			}break;
			case '-':{
				int64_t Result = std::stoll(Node::as_value(left)->expose().Value)-std::stoll(Node::as_value(right)->expose().Value);
				SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
			}break;
			case '*':{
				int64_t Result = std::stoll(Node::as_value(left)->expose().Value)*std::stoll(Node::as_value(right)->expose().Value);
				SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
			}break;
			case '/':{
				int64_t Result = std::stoll(Node::as_value(left)->expose().Value)/std::stoll(Node::as_value(right)->expose().Value);
				SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
			}break;
			case '?':{
				if(operater.Value.size()>1){
					switch(operater.Value[1]){
						case '<':{
							int64_t Result = (int64_t)(std::stoll(Node::as_value(left)->expose().Value)<std::stoll(Node::as_value(right)->expose().Value));
							SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
						}break;
						case '>':{
							int64_t Result = (int64_t)(std::stoll(Node::as_value(left)->expose().Value)>std::stoll(Node::as_value(right)->expose().Value));
							SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
						}break;
					}
				}else{
					int64_t Result = (int64_t)(std::stoll(Node::as_value(left)->expose().Value)==std::stoll(Node::as_value(right)->expose().Value));
					SegmentEnviroment->local_stack.push_back(std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(Result)}));
				}
			}break;
		}
	}
}

void Evalutate(const std::shared_ptr<Node::BlockNode>& block){
	for(size_t SegmentId=0;SegmentId<block->size();SegmentId++){
		Enviroment* SegmentEnviroment = new Enviroment;
		for(size_t InstructionPointer=0;InstructionPointer<block->peek(SegmentId)->size();InstructionPointer++){
			std::shared_ptr<Node::Node> currentInstruction = block->peek(SegmentId)->peek(InstructionPointer);
			switch(currentInstruction->type()){
				case Node::Type_en::value:{}break;
				case Node::Type_en::comarison:{
					Eval_Equation(SegmentEnviroment,currentInstruction);
					int64_t result = std::stoll(SegmentEnviroment->local_stack.back()->expose().Value);
					if(!result)InstructionPointer++;
				}break;
				case Node::Type_en::equation:{
					Eval_Equation(SegmentEnviroment,currentInstruction);
				}break;
				case Node::Type_en::assignment:{
					auto leftSide = Node::as_assignment(currentInstruction)->expose().left;
					auto rightSide = Node::as_assignment(currentInstruction)->expose().right;
					if(leftSide->type()==Node::Type_en::value&&leftSide->str() == "!"){
						leftSide = std::make_shared<Node::ValueNode>(Token::Token{Token::Type_en::number,std::to_string(SegmentId)});
					}
					if(leftSide->type()==Node::Type_en::value&&Node::as_value(leftSide)->expose().Type==Token::Type_en::identifier){
						leftSide=SegmentEnviroment->Get(Node::as_value(leftSide));
					}
					Eval_Equation(SegmentEnviroment,leftSide);
					if(rightSide->type()==Node::Type_en::value&&rightSide->str() == "@"){
						std::cout<<SegmentEnviroment->local_stack.back()->expose().Value<<std::endl;
						SegmentEnviroment->local_stack.pop_back();
						break;
					}
					else if(rightSide->type()==Node::Type_en::value&&rightSide->str() == "!"){
						InstructionPointer=0;
						SegmentId = std::stoll(SegmentEnviroment->local_stack.back()->expose().Value);
						SegmentEnviroment->local_stack.pop_back();
						break;
					}
					else if(rightSide->type()==Node::Type_en::value&&rightSide->str() == "..."){
						SegmentEnviroment->local_stack.push_back(SegmentEnviroment->local_stack.back());
						break;
					}
					else if(rightSide->type()==Node::Type_en::value&&rightSide->str() == ".."){
						global_stack.push_back(SegmentEnviroment->local_stack.back());
						break;
					}
					SegmentEnviroment->Set(Node::as_value(SegmentEnviroment->local_stack.back()),Node::as_value(rightSide));
				}break;
				//segment
				//block
				default:break;
			}
		}
		delete SegmentEnviroment;
	}
}
//{0=..}{..=a+1=..}{..=a?<10 -1=!}