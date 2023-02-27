#ifndef __Fauxon_DataType_NumberValue
#define __Fauxon_DataType_NumberValue
#include<string>
#include<cassert>
#include<deque>
#include<iterator>
#include<algorithm>
#include<iostream>
#include<sstream>
namespace Fauxon{
    namespace DataTypes{
        struct NumberValue{
            uint8_t Sign='+';
            uint8_t oSign='-';
            std::string Number;
            NumberValue(int64_t number){
                std::string xNumber = std::to_string(number);
                std::cout<<"?int64_t?"<<xNumber<<std::endl;
                Add(xNumber);
            }
            NumberValue(std::string number){
                std::cout<<"?std::string?"<<number<<std::endl;
                Add(number);
            }
            inline std::string ToString(){
                std::string Result="";
                Result+=Number;
                Result+=Sign;
                return Result;
            }
            //
            inline void Add(std::string number){
                if(number[0] == oSign){
                    number.erase(0,1);
                    Subtract(number);
                    return;
                }else if(number[0] == Sign){
                    number.erase(0,1);
                }
                std::string tmp=Number;
                std::reverse(tmp.begin(),tmp.end());
                while(Number.size()>number.size())number=std::string("0")+number;
                std::reverse(number.begin(),number.end());
                size_t Carry=0;
                for(size_t i=0;i<number.size();i++){
                    if(i>=tmp.size())tmp+='0';
                    int X = Carry+std::stoi(number.substr(i,1))+std::stoi(tmp.substr(i,1));
                    std::cout<<"ADD?["<<i<<"]=("<<Carry<<"+"<<number.substr(i,1)<<"+"<<tmp.substr(i,1)<<")="<<X<<std::endl;
                    if(X>9){
                        X-=10;
                        Carry=1;
                        tmp[i]=(std::to_string(X)[0]);
                        X=0;
                    }else{
                        tmp[i]=(std::to_string(X)[0]);
                        Carry=0;
                    }
                }
                if(Carry!=0){
                    tmp+=std::to_string(Carry);
                }
                std::reverse(tmp.begin(),tmp.end());
                Number=tmp;
            }
            inline void Subtract(std::string number){
                if(number[0] == oSign){
                    number.erase(0,1);
                    Add(number);
                    return;
                }else if(number[0] == Sign){
                    number.erase(0,1);
                }
                std::string tmp=Number;
                std::reverse(tmp.begin(),tmp.end());
                while(Number.size()>number.size())number=std::string("0")+number;
                if(Number.size()<number.size()){
                    //Convert to "Negative"
                    NumberValue tmp(number);
                    tmp.Subtract(Number);
                    Number=tmp.Number;
                    if(Sign == '-'){Sign='+';oSign='-';}else{Sign='-';oSign='+';}
                }
                std::reverse(number.begin(),number.end());
                size_t Carry=0;
                for(size_t i=0;i<number.size();i++){
                    if(i>=tmp.size())tmp+='0';
                    int X = std::stoi(tmp.substr(i,1))-std::stoi(number.substr(i,1))-Carry;
                    std::cout<<"SUBTRACT?["<<i<<"]=("<<Carry<<"-"<<number.substr(i,1)<<"-"<<tmp.substr(i,1)<<")="<<X<<std::endl;
                    std::cout<<"SUBTRACT?["<<i<<"]=("<<tmp.substr(i,1)<<"-"<<number.substr(i,1)<<"-"<<Carry<<")="<<X<<std::endl;
                    if(X<0){
                        X+=10;
                        Carry=1;
                        tmp[i]=(std::to_string(X)[0]);
                        X=0;
                    }else{
                        tmp[i]=(std::to_string(X)[0]);
                        Carry=0;
                    }
                }
                if(Carry!=0){
                    std::reverse(number.begin(),number.end());
                    std::reverse(tmp.begin(),tmp.end());
                    std::cout<<"??"<<tmp<<std::endl;
                    NumberValue T(number);
                    T.Subtract(Number);
                    tmp=T.Number;
                    if(Sign == '-'){Sign='+';oSign='-';}else{Sign='-';oSign='+';}
                }else{
                    std::reverse(tmp.begin(),tmp.end());
                }
                Number=tmp;
            }
        };
    };
};

#endif