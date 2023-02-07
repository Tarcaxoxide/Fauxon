#pragma once
#include<deque>
#include<string>

enum State_en:size_t {
    STATE_BAD=0,
    STATE_GOOD,
    STATE_LOOPBACK_REQUEST,
    STATE_LOOPBACK_REPLY
};

class CommonParem_cl{
    State_en State{State_en::STATE_BAD};
    std::deque<std::string> Values;
    std::deque<std::string> Labels;
    public:
    void clear(){
        Values.clear();
        Labels.clear();
    }
    void set(std::string Label,std::string Value){
        for(size_t i=0;i<Labels.size();i++){
            if(Labels[i] == Label){
                Values[i] = Value;
                return;
            }
        }
        Labels.push_back(Label);
        Values.push_back(Value);
    }
    std::string get(std::string Label){
        for(size_t i=0;i<Labels.size();i++){
            if(Labels[i] == Label){
                return Values[i];
            }
        }
        return "";
    }
    State_en GetState(){
        return State;
    }
    void SetState(State_en newState){
        State=newState;
    }
    void FlipState(){
        if(State == State_en::STATE_BAD)State=State_en::STATE_GOOD;
        else if(State == State_en::STATE_GOOD)State=State_en::STATE_BAD;
        else if(State == State_en::STATE_LOOPBACK_REPLY)State=State_en::STATE_LOOPBACK_REQUEST;
        else if(State == State_en::STATE_LOOPBACK_REQUEST)State=State_en::STATE_LOOPBACK_REPLY;
    }
};