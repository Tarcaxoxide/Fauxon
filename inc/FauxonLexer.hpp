#pragma once
#include<deque>
#include<string>
#include<functional>
#ifdef DEBUG
    #include<iostream>
#endif
#include<typeinfo>

#include <FauxonToken.hpp>

namespace Fauxon{
    class Lexer_cl{
        std::string Text;
        char* current_char;
        int64_t index;
        public:
            Lexer_cl(std::string Text){
                #ifdef DEBUG
                    std::cout<<"?>.Lexer_cl"<<std::endl;
                #endif
                this->Text=Text;
                current_char=nullptr;
                index=-1;
                Lexer_cl::advance_s(this);
                #ifdef DEBUG
                    std::cout<<"<?.Lexer_cl"<<std::endl;
                #endif
            }
            static void advance_s(Lexer_cl* self){
                #ifdef DEBUG
                    std::cout<<"?>.advance_s"<<std::endl;
                #endif
                self->index++;
                if(self->index < self->Text.size() && self->index > -1){
                    self->current_char=&self->Text[self->index];
                }else{
                    self->current_char=nullptr;
                }
                #ifdef DEBUG
                    std::cout<<"<?.advance_s"<<check_type_AsString(self->current_char)<<std::endl;
                #endif
            }
            static std::deque<Token_st>* make_tokens_s(Lexer_cl* self){
                #ifdef DEBUG
                    std::cout<<"?>.make_tokens_s"<<std::endl;
                #endif
                bool ConvertToString=false;
                std::deque<Token_st>* tokens = new std::deque<Token_st>;
                while(self->current_char != nullptr){
                    if(*self->current_char == ' ' || *self->current_char == '\t' || *self->current_char == '\n'){
                        Lexer_cl::advance_s(self);
                        continue;
                    }
                    switch(*self->current_char){
                        case '+':{
                            tokens->push_back(Token_st(TokenType_en::__PLUS));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '-':{
                            tokens->push_back(Token_st(TokenType_en::__MINUS));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '*':{
                            tokens->push_back(Token_st(TokenType_en::__MULTIPLY));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '/':{
                            tokens->push_back(Token_st(TokenType_en::__DIVIDE));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '(':{
                            tokens->push_back(Token_st(TokenType_en::__LEFT_PARENTHESIS));
                            Lexer_cl::advance_s(self);
                        }break;
                        case ')':{
                            tokens->push_back(Token_st(TokenType_en::__RIGHT_PARENTHESIS));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '?':{
                            if(tokens->size()){
                                if(tokens->back().Type == TokenType_en::__QUESTION){
                                    tokens->back().Delete();
                                    tokens->pop_back();
                                    tokens->push_back(Token_st(TokenType_en::__VERBOSE_QUESTION));
                                }else{
                                    tokens->push_back(Token_st(TokenType_en::__QUESTION));
                                }
                            }else{
                                tokens->push_back(Token_st(TokenType_en::__QUESTION));
                            }
                            Lexer_cl::advance_s(self);
                        }break;
                        case ':':{
                            if(tokens->size()){
                                if(tokens->back().Type == TokenType_en::__LESS){
                                    tokens->back().Delete();
                                    tokens->pop_back();
                                    tokens->push_back(Token_st(TokenType_en::__SHIFT_LEFT));
                                }else{
                                    tokens->push_back(Token_st(TokenType_en::__COLON));
                                }
                            }else{
                                tokens->push_back(Token_st(TokenType_en::__COLON));
                            }
                            Lexer_cl::advance_s(self);
                        }break;
                        case ';':{
                            tokens->push_back(Token_st(TokenType_en::__SEMI_COLON));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '^':{
                            ConvertToString=true;
                            Lexer_cl::advance_s(self);
                        }break;
                        case '=':{
                            if(tokens->size()){
                                switch(tokens->back().Type){
                                    case TokenType_en::__EQUAL:{
                                        tokens->back().Delete();
                                        tokens->pop_back();
                                        tokens->push_back(Token_st(TokenType_en::__EQUAL_EQUAL));
                                    }break;
                                    case TokenType_en::__LESS:{
                                        tokens->back().Delete();
                                        tokens->pop_back();
                                        tokens->push_back(Token_st(TokenType_en::__LESS_EQUAL));
                                    }break;
                                    case TokenType_en::__MORE:{
                                        tokens->back().Delete();
                                        tokens->pop_back();
                                        tokens->push_back(Token_st(TokenType_en::__MORE_EQUAL));
                                    }break;
                                    default:{
                                        tokens->push_back(Token_st(TokenType_en::__EQUAL));
                                    }break;
                                }
                            }else{
                                tokens->push_back(Token_st(TokenType_en::__EQUAL));
                            }
                            Lexer_cl::advance_s(self);
                        }break;
                        case '<':{
                            tokens->push_back(Token_st(TokenType_en::__LESS));
                            Lexer_cl::advance_s(self);
                        }break;
                        case '>':{
                            if(tokens->size()){
                                if(tokens->back().Type == TokenType_en::__COLON){
                                    tokens->back().Delete();
                                    tokens->pop_back();
                                    tokens->push_back(Token_st(TokenType_en::__SHIFT_RIGHT));
                                }else{
                                    tokens->push_back(Token_st(TokenType_en::__MORE));
                                }
                            }else{
                                tokens->push_back(Token_st(TokenType_en::__MORE));
                            }
                            
                            Lexer_cl::advance_s(self);
                        }break;
                        default:{
                            std::string sType=check_type_AsString(self->current_char);
                            if(sType == "__SINGLE_NUMBER" || sType == "__PERIOD"){
                                if(ConvertToString){ConvertToString=false;
                                    tokens->push_back(Lexer_cl::make_word_s(self));
                                }else{
                                    tokens->push_back(Lexer_cl::make_number_s(self));
                                }
                                continue;
                            }
                            if(sType == "__SINGLE_LETTER"){
                                tokens->push_back(Lexer_cl::make_word_s(self));
                                continue;
                            }
                            std::string ErrorMessage="Lexer, Unidentifiable Token '";
                            ErrorMessage+=*self->current_char;
                            ErrorMessage+="'";
                            tokens->push_back(Token_st(TokenType_en::__ERROR,ErrorMessage));
                            Lexer_cl::advance_s(self);
                        }break;
                    }
                }
                tokens->push_back(Token_st(TokenType_en::__EOF));
                #ifdef DEBUG
                    std::cout<<"<?.make_tokens_s"<<std::endl;
                #endif
                return tokens;
            }
            static Token_st make_word_s(Lexer_cl* self){
                #ifdef DEBUG
                    std::cout<<"?>.make_word_s"<<std::endl;
                #endif
                std::string word_str="";
                std::string sType=check_type_AsString(self->current_char);
                while(sType == "__SINGLE_LETTER" || sType == "_" || sType == "__SINGLE_NUMBER" || sType == "__PERIOD"){
                    word_str+=*self->current_char;
                    Lexer_cl::advance_s(self);
                    sType=check_type_AsString(self->current_char);
                }
                #ifdef DEBUG
                     std::cout<<"<?.make_word_s"<<std::endl;
                #endif
                return Token_st(TokenType_en::__WORD,word_str);
            }
            static Token_st make_number_s(Lexer_cl* self){
                #ifdef DEBUG
                    std::cout<<"?>.make_number_s"<<std::endl;
                #endif
                std::string num_str="";
                int dot_count=0;
                std::string sType=check_type_AsString(self->current_char);
                while(sType == "__SINGLE_NUMBER" || sType == "__PERIOD"){
                    if(sType == "__PERIOD"){
                        dot_count++;
                        if(dot_count > 1)break;
                        if(!(num_str.size()))num_str+="0";//if the number given is like '.0' instead of '0.0' then we just make it '0.0'
                    }
                    num_str+=*self->current_char;
                    Lexer_cl::advance_s(self);
                    sType=check_type_AsString(self->current_char);
                }
                #ifdef DEBUG
                    std::cout<<"<?.make_number_s"<<std::endl;
                #endif
                if(dot_count == 0)return Token_st(TokenType_en::__INT,std::stol(num_str));
                if(dot_count == 1)return Token_st(TokenType_en::__FLOAT,std::stod(num_str));
                return Token_st(TokenType_en::__NULL);
            }
            std::deque<Token_st>* make_tokens(){
                #ifdef DEBUG
                    std::cout<<"<?>make_tokens"<<std::endl;
                #endif
                return Lexer_cl::make_tokens_s(this);
            }
    };
}

