#pragma once
#include<FauxonLexer.hpp>
#include<FauxonToken.hpp>
#include<fstream>
#include<iostream>
#include<deque>
#include<string>

namespace Fauxon{
    namespace _{
        struct Variable_st{
            std::string name;
            Token_st Value;
        };
        std::deque<Variable_st> Variables;
        Token_st& GetVariable(std::string name){
            if(!(Variables.size()))Variables.push_back({name,Token_st(TokenType_en::__NULL)});
            for(size_t i=0;i<Variables.size();i++){
                if(Variables[i].name == name){
                    return Variables[i].Value;
                }
            }
            return Variables.front().Value;
        }
        void SetVariable(std::string name,Token_st& value){
            for(size_t i=0;i<Variables.size();i++){
                if(Variables[i].name == name){
                    Variables[i].Value.Copy(value);
                    return;
                }
            }
            Variables.push_back({name,Token_st(value)});
        }
        Token_st& GetValue(Token_st& Vin){
            if(Vin.Type != TokenType_en::__WORD)return Vin;
            Token_st& Vout = GetVariable((*(Vin.asString(false))));
            if(Vout.Type == TokenType_en::__NULL)Vout=Vin;
            return Vout;
        }
    };
    namespace Math{
        Token_st ADD(Token_st& LeftToken,Token_st& RightToken){
            Token_st& LTok = _::GetValue(LeftToken);
            Token_st& RTok = _::GetValue(RightToken);
            Token_st ResultToken(TokenType_en::__MULTIPLY);
            switch(RTok.Type){
                case TokenType_en::__INT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asInt()))+(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asInt()))+(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                case TokenType_en::__FLOAT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asDouble()))+(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asDouble()))+(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                default:{}break;
            }
            return ResultToken;
        }
        Token_st SUBTRACT(Token_st& LeftToken,Token_st& RightToken){
            Token_st& LTok = _::GetValue(LeftToken);
            Token_st& RTok = _::GetValue(RightToken);
            Token_st ResultToken(TokenType_en::__MULTIPLY);
            switch(RTok.Type){
                case TokenType_en::__INT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asInt()))-(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asInt()))-(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                case TokenType_en::__FLOAT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asDouble()))-(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asDouble()))-(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                default:{}break;
            }
            return ResultToken;
        }
        Token_st MULTIPLY(Token_st& LeftToken,Token_st& RightToken){
            Token_st& LTok = _::GetValue(LeftToken);
            Token_st& RTok = _::GetValue(RightToken);
            Token_st ResultToken(TokenType_en::__MULTIPLY);
            switch(RTok.Type){
                case TokenType_en::__INT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asInt()))*(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asInt()))*(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                case TokenType_en::__FLOAT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asDouble()))*(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asDouble()))*(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                default:{}break;
            }
            return ResultToken;
        }
        Token_st DIVIDE(Token_st& LeftToken,Token_st& RightToken){
            Token_st& LTok = _::GetValue(LeftToken);
            Token_st& RTok = _::GetValue(RightToken);
            Token_st ResultToken(TokenType_en::__MULTIPLY);
            switch(RTok.Type){
                case TokenType_en::__INT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asInt()))/(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asInt()))/(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                case TokenType_en::__FLOAT:{
                    switch(LTok.Type){
                        case TokenType_en::__INT:{
                            ResultToken = (*(LTok.asDouble()))/(*(RTok.asInt()));
                        }break;
                        case TokenType_en::__FLOAT:{
                            ResultToken = (*(LTok.asDouble()))/(*(RTok.asDouble()));
                        }break;
                        default:{}break;
                    }
                }break;
                default:{}break;
            }
            return ResultToken;
        }
    };
    void Exec(std::deque<Token_st>* Toks){
        std::deque<Token_st>& Tokens=*Toks;
        for(size_t CurrentIndex=0;CurrentIndex<Tokens.size();){
            switch(Tokens[CurrentIndex].Type){
                case TokenType_en::__PLUS:{
                    Token_st& PTok = _::GetVariable("_RESULT");
                    Token_st& LTok = _::GetValue(Tokens[CurrentIndex-1]);
                    bool Q=false;
                    bool V=false;
                    if(LTok.Type == TokenType_en::__QUESTION ||LTok.Type == TokenType_en::__VERBOSE_QUESTION){
                        if(LTok.Type == TokenType_en::__VERBOSE_QUESTION)V=true;
                        Q=true;
                        LTok = _::GetValue(Tokens[CurrentIndex-2]);
                    }
                    Token_st& CTok = _::GetValue(Tokens[CurrentIndex]);
                    Token_st& RTok = _::GetValue(Tokens[CurrentIndex+1]);
                    if(PTok.Type == TokenType_en::__NULL){
                        CTok = Math::ADD(LTok,RTok);
                    }else if(PTok.Type == TokenType_en::__INT || PTok.Type == TokenType_en::__FLOAT || PTok.Type == TokenType_en::__WORD){
                        CTok = Math::ADD(PTok,RTok);
                    }else{
                        CTok = Math::ADD((*(PTok.GetSub().Center.Ptr)),RTok);
                    }
                    if(Q){std::cout<<(*(CTok.asString(V)))<<std::endl;}
                    _::SetVariable("_RESULT",CTok);
                    CurrentIndex++;
                }break;
                case TokenType_en::__MINUS:{
                    Token_st& PTok = _::GetVariable("_RESULT");
                    Token_st& LTok = _::GetValue(Tokens[CurrentIndex-1]);
                    bool Q=false;
                    bool V=false;
                    if(LTok.Type == TokenType_en::__QUESTION ||LTok.Type == TokenType_en::__VERBOSE_QUESTION){
                        if(LTok.Type == TokenType_en::__VERBOSE_QUESTION)V=true;
                        Q=true;
                        LTok = _::GetValue(Tokens[CurrentIndex-2]);
                    }
                    Token_st& CTok = _::GetValue(Tokens[CurrentIndex]);
                    Token_st& RTok = _::GetValue(Tokens[CurrentIndex+1]);
                    if(PTok.Type == TokenType_en::__NULL){
                        CTok = Math::SUBTRACT(LTok,RTok);
                    }else if(PTok.Type == TokenType_en::__INT || PTok.Type == TokenType_en::__FLOAT || PTok.Type == TokenType_en::__WORD){
                        CTok = Math::SUBTRACT(PTok,RTok);
                    }else{
                        CTok = Math::SUBTRACT((*(PTok.GetSub().Center.Ptr)),RTok);
                    }
                    if(Q){std::cout<<(*(CTok.asString(V)))<<std::endl;}
                    _::SetVariable("_RESULT",CTok);
                    CurrentIndex++;
                }break;
                case TokenType_en::__MULTIPLY:{
                    Token_st& PTok = _::GetVariable("_RESULT");
                    Token_st& LTok = _::GetValue(Tokens[CurrentIndex-1]);
                    bool Q=false;
                    bool V=false;
                    if(LTok.Type == TokenType_en::__QUESTION ||LTok.Type == TokenType_en::__VERBOSE_QUESTION){
                        if(LTok.Type == TokenType_en::__VERBOSE_QUESTION)V=true;
                        Q=true;
                        LTok = _::GetValue(Tokens[CurrentIndex-2]);
                    }
                    Token_st& CTok = _::GetValue(Tokens[CurrentIndex]);
                    Token_st& RTok = _::GetValue(Tokens[CurrentIndex+1]);
                    if(PTok.Type == TokenType_en::__NULL){
                        CTok = Math::MULTIPLY(LTok,RTok);
                    }else if(PTok.Type == TokenType_en::__INT || PTok.Type == TokenType_en::__FLOAT || PTok.Type == TokenType_en::__WORD){
                        CTok = Math::MULTIPLY(PTok,RTok);
                    }else{
                        CTok = Math::MULTIPLY((*(PTok.GetSub().Center.Ptr)),RTok);
                    }
                    if(Q){std::cout<<(*(CTok.asString(V)))<<std::endl;}
                    _::SetVariable("_RESULT",CTok);
                    CurrentIndex++;
                }break;
                case TokenType_en::__DIVIDE:{
                    Token_st& PTok = _::GetVariable("_RESULT");
                    Token_st& LTok = _::GetValue(Tokens[CurrentIndex-1]);
                    bool Q=false;
                    bool V=false;
                    if(LTok.Type == TokenType_en::__QUESTION ||LTok.Type == TokenType_en::__VERBOSE_QUESTION){
                        if(LTok.Type == TokenType_en::__VERBOSE_QUESTION)V=true;
                        Q=true;
                        LTok = _::GetValue(Tokens[CurrentIndex-2]);
                    }
                    Token_st& CTok = _::GetValue(Tokens[CurrentIndex]);
                    Token_st& RTok = _::GetValue(Tokens[CurrentIndex+1]);

                    if(PTok.Type == TokenType_en::__NULL){
                        CTok = Math::DIVIDE(LTok,RTok);
                    }else if(PTok.Type == TokenType_en::__INT || PTok.Type == TokenType_en::__FLOAT || PTok.Type == TokenType_en::__WORD){
                        CTok = Math::DIVIDE(PTok,RTok);
                    }else{
                        CTok = Math::DIVIDE((*(PTok.GetSub().Center.Ptr)),RTok);
                    }
                    if(Q){std::cout<<(*(CTok.asString(V)))<<std::endl;}
                    _::SetVariable("_RESULT",CTok);
                    CurrentIndex++;
                }break;
                //case TokenType_en::__INT:{Result="__INT";}break;
                //case TokenType_en::__FLOAT:{Result="__FLOAT";}break;
                //case TokenType_en::__WORD:{Result="__WORD";}break;
                //case TokenType_en::__PERIOD:{Result="__PERIOD";}break;
                case TokenType_en::__EQUAL:{
                    Token_st& PTok = _::GetVariable("_RESULT");
                    Token_st& LTok = _::GetValue(Tokens[CurrentIndex-1]);
                    bool Q=false;
                    bool V=false;
                    if(LTok.Type == TokenType_en::__QUESTION ||LTok.Type == TokenType_en::__VERBOSE_QUESTION){
                        if(LTok.Type == TokenType_en::__VERBOSE_QUESTION)V=true;
                        Q=true;
                        LTok = _::GetValue(Tokens[CurrentIndex-2]);
                    }
                    Token_st& CTok = _::GetValue(Tokens[CurrentIndex]);
                    Token_st& RTok = Tokens[CurrentIndex+1];

                    if(PTok.Type == TokenType_en::__NULL){
                        //CTok = Math::DIVIDE(LTok,RTok);
                        _::SetVariable(*(RTok.asString(false)),LTok);
                    }else if(PTok.Type == TokenType_en::__INT || PTok.Type == TokenType_en::__FLOAT || PTok.Type == TokenType_en::__WORD){
                        //CTok = Math::DIVIDE(PTok,RTok);
                         _::SetVariable(*(RTok.asString(false)),PTok);
                    }else{
                        //CTok = Math::DIVIDE((*(PTok.GetSub().Center.Ptr)),RTok);
                         _::SetVariable(*(RTok.asString(false)),(*(PTok.GetSub().Center.Ptr)));
                    }
                    if(Q){std::cout<<(*(CTok.asString(V)))<<std::endl;}
                    _::SetVariable("_RESULT",CTok);
                    CurrentIndex++;
                }break;
                //case TokenType_en::__LESS:{Result="__LESS";}break;
                //case TokenType_en::__MORE:{Result="__MORE";}break;
                //case TokenType_en::__LEFT_PARENTHESIS:{Result="__LEFT_PARENTHESIS";}break;
                //case TokenType_en::__RIGHT_PARENTHESIS:{Result="__RIGHT_PARENTHESIS";}break;
                //case TokenType_en::__EQUAL_EQUAL:{Result="__EQUAL_EQUAL";}break;
                //case TokenType_en::__LESS_EQUAL:{Result="__LESS_EQUAL";}break;
                //case TokenType_en::__MORE_EQUAL:{Result="__MORE_EQUAL";}break;
                case TokenType_en::__QUESTION:{
                    Token_st& RTok = _::GetValue(Tokens[CurrentIndex+1]);
                    if(RTok.Type == TokenType_en::__INT || RTok.Type == TokenType_en::__FLOAT || RTok.Type == TokenType_en::__WORD){
                        std::cout<<(*(RTok.asString(false)))<<std::endl;
                    }
                    CurrentIndex++;
                }break;
                case TokenType_en::__VERBOSE_QUESTION:{
                    Token_st& RTok = _::GetValue(Tokens[CurrentIndex+1]);
                    if(RTok.Type == TokenType_en::__INT || RTok.Type == TokenType_en::__FLOAT || RTok.Type == TokenType_en::__WORD){
                        std::cout<<(*(RTok.asString(true)))<<std::endl;
                    }
                    CurrentIndex++;
                }break;
                //case TokenType_en::__COLON:{Result="__COLON";}break;
                //case TokenType_en::__SEMI_COLON:{Result="__SEMI_COLON";}break;
                //case TokenType_en::__SHIFT_RIGHT:{Result="__SHIFT_RIGHT";}break;
                //case TokenType_en::__SHIFT_LEFT:{Result="__SHIFT_LEFT";}break;
                default:{CurrentIndex++;}break;
            }
        }
    }
};