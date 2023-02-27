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
            //
            NumberValue(int64_t number);
            NumberValue(std::string number);
            NumberValue(const NumberValue& number);
            //
            std::string ToString();
            //
            void Add(std::string number);inline void Add(NumberValue number){Add(number.Number);}
            void Subtract(std::string number);inline void Subtract(NumberValue number){Subtract(number.ToString());}
            void Multiply(std::string number);inline void Multiply(NumberValue number){Multiply(number.ToString());}
            void Divide(std::string number);inline void Divide(NumberValue number){Divide(number.ToString());}
            //
            bool operator<(std::string number);bool inline operator<(NumberValue number){return (*this)<number.ToString();}
            bool operator>(std::string number);bool inline operator>(NumberValue number){return (*this)>number.ToString();}
            bool operator<=(std::string number);bool inline operator<=(NumberValue number){return (*this)<=number.ToString();}
            bool operator>=(std::string number);bool inline operator>=(NumberValue number){return (*this)>=number.ToString();}
            bool operator==(std::string number);bool inline operator==(NumberValue number){return (*this)==number.ToString();}
            bool operator!=(std::string number);bool inline operator!=(NumberValue number){return (*this)!=number.ToString();}
        };
    };
};

#endif