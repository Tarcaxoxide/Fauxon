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
            //constructors!, constructors!, constructors!, construct!
            NumberValue(int64_t number);
            NumberValue(std::string number);
            NumberValue(const NumberValue& number);
            //To string for printing the number out (shshsh... it's already a string XD)
            std::string ToString();
            //Base math function
            void Add(std::string number);inline void Add(NumberValue number){Add(number.Number);}
            void Subtract(std::string number);inline void Subtract(NumberValue number){Subtract(number.ToString());}
            void Multiply(std::string number);inline void Multiply(NumberValue number){Multiply(number.ToString());}
            void Divide(std::string number);inline void Divide(NumberValue number){Divide(number.ToString());}
            //Comparision operators
            bool operator<(std::string number);
            inline bool operator<(NumberValue number){return (*this)<number.ToString();}
            inline bool operator<(int64_t number){return (*this)<std::to_string(number);}
            bool operator>(std::string number);
            inline bool operator>(NumberValue number){return (*this)>number.ToString();}
            inline bool operator>(int64_t number){return (*this)>std::to_string(number);}
            bool operator<=(std::string number);
            inline bool operator<=(NumberValue number){return (*this)<=number.ToString();}
            inline bool operator<=(int64_t number){return (*this)<=std::to_string(number);}
            bool operator>=(std::string number);
            inline bool operator>=(NumberValue number){return (*this)>=number.ToString();}
            inline bool operator>=(int64_t number){return (*this)>=std::to_string(number);}
            bool operator==(std::string number);
            inline bool operator==(NumberValue number){return (*this)==number.ToString();}
            inline bool operator==(int64_t number){return (*this)==std::to_string(number);}
            bool operator!=(std::string number);
            inline bool operator!=(NumberValue number){return (*this)!=number.ToString();}
            inline bool operator!=(int64_t number){return (*this)!=std::to_string(number);}
            //Math operator
            NumberValue& operator+=(std::string number);
            inline NumberValue& operator+=(NumberValue number){return (*this)+=number.ToString();}
            inline NumberValue& operator+=(int64_t number){return (*this)+=std::to_string(number);}
            NumberValue& operator-=(std::string number);
            inline NumberValue& operator-=(NumberValue number){return (*this)-=number.ToString();}
            inline NumberValue& operator-=(int64_t number){return (*this)-=std::to_string(number);}
            NumberValue& operator*=(std::string number);
            inline NumberValue& operator*=(NumberValue number){return (*this)*=number.ToString();}
            inline NumberValue& operator*=(int64_t number){return (*this)*=std::to_string(number);}
            NumberValue& operator/=(std::string number);
            inline NumberValue& operator/=(NumberValue number){return (*this)/=number.ToString();}
            inline NumberValue& operator/=(int64_t number){return (*this)/=std::to_string(number);}
            NumberValue& operator=(std::string number);
            inline NumberValue& operator=(NumberValue number){return (*this)=number.ToString();}
            inline NumberValue& operator=(int64_t number){return (*this)=std::to_string(number);}
        };
    };
};
#endif