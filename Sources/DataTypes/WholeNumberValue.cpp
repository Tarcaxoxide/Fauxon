#include<DataTypes/WholeNumberValue.hpp>

extern bool IsDigit(char Char);
namespace Fauxon{
    namespace DataTypes{
        //constructors!, constructors!, constructors!, construct!
        WholeNumberValue::WholeNumberValue(int64_t number){
            std::string xNumber = std::to_string(number);
            Add(xNumber);
        }
        WholeNumberValue::WholeNumberValue(std::string number){
            Add(number);
        }
        WholeNumberValue::WholeNumberValue(const WholeNumberValue& number){
            Add(number);
        }
        //To string for printing the number out (shshsh... it's already a string XD)
        std::string WholeNumberValue::ToString()const{
            std::string Result="";
            Result+=Sign;
            Result+=Number;
            return Result;
        }
        //Base math function
        void WholeNumberValue::Add(std::string number){
            switch(Sign){
                case '-':{
                    if(number[0]=='-'){
                        if(number[0]=='-')number.erase(0,1);
                        Subtract(number);
                        return;
                    }
                    if(number[0]=='+')number.erase(0,1);
                }break;
                case '+':{
                    if(number[0]=='-'){
                        number.erase(0,1);
                        Subtract(number);
                        return;
                    }
                    if(number[0]=='+')number.erase(0,1);
                }break;
            }
            std::string tmp=Number;
            std::reverse(tmp.begin(),tmp.end());
            while(Number.size()>number.size())number=std::string("0")+number;
            std::reverse(number.begin(),number.end());
            size_t Carry=0;
            for(size_t i=0;i<number.size();i++){
                if(i>=tmp.size())tmp+='0';
                int X = Carry+std::stoi(number.substr(i,1))+std::stoi(tmp.substr(i,1));
                //std::cout<<"ADD?["<<i<<"]=("<<Carry<<"+"<<number.substr(i,1)<<"+"<<tmp.substr(i,1)<<")="<<X<<std::endl;
                if(X>9){
                    Carry=(X/10);
                    X-=(10*Carry);
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
            Adjust();
        }
        void WholeNumberValue::Subtract(std::string number){
            switch(Sign){
                case '-':{
                    if(number[0]!='-'){
                        //number.erase(0,1);
                        Add(number);
                        return;
                    }
                    if(number[0]=='-')number.erase(0,1);
                }break;
                case '+':{
                    if(number[0]=='-'){
                        number.erase(0,1);
                        Add(number);
                        return;
                    }
                    if(number[0]=='+')number.erase(0,1);
                }break;
            }
            std::string tmp=Number;
            std::reverse(tmp.begin(),tmp.end());
            while(Number.size()>number.size())number=std::string("0")+number;
            std::reverse(number.begin(),number.end());
            size_t Carry=0;
            for(size_t i=0;i<number.size();i++){
                if(i>=tmp.size())tmp+='0';
                int X = std::stoi(tmp.substr(i,1))-std::stoi(number.substr(i,1))-Carry;
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
                WholeNumberValue T(number);
                T.Subtract(Number);
                tmp=T.Number;
                FlipSign();
            }else{
                std::reverse(tmp.begin(),tmp.end());
            }
            Number=tmp;
            Adjust();
        }
        void WholeNumberValue::Divide(std::string number){
            WholeNumberValue Counter("0");
            if((*this)<number){
                Number="0";
                return;
            }
            WholeNumberValue Result(Number);
            for(;Result>0;Counter.Add("1")){
                Result.Subtract(number);
            }
            Number=Counter.Number;
            Adjust();
        }
        void WholeNumberValue::Multiply(std::string number){
            WholeNumberValue Counter(number);
            WholeNumberValue Result("0");
            for(;Counter>0;Counter.Subtract("1")){
                Result.Add(Number);
            }
            Number=Result.Number;
            Adjust();
        }
        void WholeNumberValue::FlipSign(){
            if(Sign == '-'){Sign='+';oSign='-';}else{Sign='-';oSign='+';}
        }
        void WholeNumberValue::Adjust(){
            while(Number[0] == '0'&&Number.size()>MinimalDigits)Number.erase(0,1);
            while(Number.size()<MinimalDigits)Number+="0";
        }
        //Comparision operators
        bool WholeNumberValue::operator<(std::string number){//205<300
            WholeNumberValue Vnumber(number);
            switch(Sign){
                case '+':{
                    switch(Vnumber.Sign){
                        case '+':{
                            if(Number.size() > Vnumber.Number.size())return false;
                            if(Number.size() < Vnumber.Number.size())return true;
                        }break;
                        case '-':{
                            return false;
                        }break;
                    }
                }break;
                case '-':{
                    switch(Vnumber.Sign){
                        case '+':{
                            return true;
                        }break;
                        case '-':{
                            if(Number.size() > Vnumber.Number.size())return true;
                            if(Number.size() < Vnumber.Number.size())return false;
                        }break;
                    }
                }break;
            }
            for(int64_t i=Vnumber.Number.size()-1;i>=0;i--){
                switch(Sign){
                    case '+':{
                        switch(Vnumber.Sign){
                            case '+':{
                                if(Number[i] < Vnumber.Number[i])return true;
                            }break;
                            //case '-':{}break;
                        }
                    }break;
                    case '-':{
                        switch(Vnumber.Sign){
                            //case '+':{}break;
                            case '-':{
                                if(Number[i] > Vnumber.Number[i])return true;
                            }break;
                        }
                    }break;
                }
            }
            return false;
        }
        bool WholeNumberValue::operator>(std::string number){
            WholeNumberValue Vnumber(number);
            switch(Sign){
                case '+':{
                    switch(Vnumber.Sign){
                        case '+':{
                            if(Number.size() > Vnumber.Number.size())return true;
                            if(Number.size() < Vnumber.Number.size())return false;
                        }break;
                        case '-':{
                            return true;
                        }break;
                    }
                }break;
                case '-':{
                    switch(Vnumber.Sign){
                        case '+':{
                            return false;
                        }break;
                        case '-':{
                            if(Number.size() > Vnumber.Number.size())return false;
                            if(Number.size() < Vnumber.Number.size())return true;
                        }break;
                    }
                }break;
            }
            for(int64_t i=Vnumber.Number.size()-1;i>=0;i--){
                switch(Sign){
                    case '+':{
                        switch(Vnumber.Sign){
                            case '+':{
                                if(Number[i] > Vnumber.Number[i])return true;
                            }break;
                            //case '-':{}break;
                        }
                    }break;
                    case '-':{
                        switch(Vnumber.Sign){
                            //case '+':{}break;
                            case '-':{
                                if(Number[i] < Vnumber.Number[i])return true;
                            }break;
                        }
                    }break;
                }
            }
            return false;
        }
        bool WholeNumberValue::operator<=(std::string number){
            if((*this)<number)return true;
            if((*this)==number)return true;
            return false;
        }
        bool WholeNumberValue::operator>=(std::string number){
            if((*this)>number)return true;
            if((*this)==number)return true;
            return false;
        }
        bool WholeNumberValue::operator==(std::string number){
            if(Number.size() < number.size())return false;
            if(Number.size() > number.size())return false;
            for(int64_t i=number.size()-1;i>=0;i--){
                if(Number[i] != number[i])return false;
            }
            return true;
        }
        bool WholeNumberValue::operator!=(std::string number){
            return !((*this)==number);
        }
        //Math operator
        WholeNumberValue& WholeNumberValue::operator+=(std::string number){Add(number);return *this;}
        WholeNumberValue& WholeNumberValue::operator-=(std::string number){Subtract(number);return *this;}
        WholeNumberValue& WholeNumberValue::operator*=(std::string number){Multiply(number);return *this;}
        WholeNumberValue& WholeNumberValue::operator/=(std::string number){Divide(number);return *this;}
        WholeNumberValue& WholeNumberValue::operator=(std::string number){Number.clear();Add(number);return *this;}
        //Parse
        bool WholeNumberValue::TryParse(std::string number,WholeNumberValue& out){
            for(size_t i=0;i<number.size();i++){
                if(!IsDigit(number[i]))return false;
            }
            out = WholeNumberValue(number);
            return true;
        }
    };
};