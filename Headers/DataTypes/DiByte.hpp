#ifndef __Fauxon_DataType_DiByte
#define __Fauxon_DataType_DiByte
namespace Fauxon{
    namespace DataTypes{
        struct DiByte{
            uint8_t A:4;
            uint8_t B:4;
            inline void SetA(const char v){
                switch(v){
                    case '\0':{A=0b0000;}break;
                    case 'E':{A=0b0001;}break;
                    case 'F':{A=0b0010;}break;
                    case '0':{A=0b0011;}break;
                    case '1':{A=0b0100;}break;
                    case '2':{A=0b0101;}break;
                    case '3':{A=0b0110;}break;
                    case '4':{A=0b0111;}break;
                    case '5':{A=0b1000;}break;
                    case '6':{A=0b1001;}break;
                    case '7':{A=0b1011;}break;
                    case '8':{A=0b1100;}break;
                    case '9':{A=0b1101;}break;
                    case 'T':{A=0b1110;}break;
                    case '?':{A=0b1111;}break;
                }
            }
            inline char GetA()const{
                switch(A){
                    case 0b0000:return '\0';
                    case 0b0001:return 'E';
                    case 0b0010:return 'F';
                    case 0b0011:return '0';
                    case 0b0100:return '1';
                    case 0b0101:return '2';
                    case 0b0110:return '3';
                    case 0b0111:return '4';
                    case 0b1000:return '5';
                    case 0b1001:return '6';
                    case 0b1011:return '7';
                    case 0b1100:return '8';
                    case 0b1101:return '9';
                    case 0b1110:return 'T';
                    case 0b1111:return '?';
                }
                return '?';
            }
            inline void SetB(const char v){
                switch(v){
                    case '\0':{B=0b0000;}break;
                    case 'E':{B=0b0001;}break;
                    case 'F':{B=0b0010;}break;
                    case '0':{B=0b0011;}break;
                    case '1':{B=0b0100;}break;
                    case '2':{B=0b0101;}break;
                    case '3':{B=0b0110;}break;
                    case '4':{B=0b0111;}break;
                    case '5':{B=0b1000;}break;
                    case '6':{B=0b1001;}break;
                    case '7':{B=0b1011;}break;
                    case '8':{B=0b1100;}break;
                    case '9':{B=0b1101;}break;
                    case 'T':{B=0b1110;}break;
                    case '?':{B=0b1111;}break;
                }
            }
            inline char GetB()const{
                switch(B){
                    case 0b0000:return '\0';
                    case 0b0001:return 'E';
                    case 0b0010:return 'F';
                    case 0b0011:return '0';
                    case 0b0100:return '1';
                    case 0b0101:return '2';
                    case 0b0110:return '3';
                    case 0b0111:return '4';
                    case 0b1000:return '5';
                    case 0b1001:return '6';
                    case 0b1011:return '7';
                    case 0b1100:return '8';
                    case 0b1101:return '9';
                    case 0b1110:return 'T';
                    case 0b1111:return '?';
                }
                return '?';
            }
        };
    };
};
#endif

/*
 Null   =>  0000    =>  '\0'
Error   =>  0001    =>  'E'
False   =>  0010    =>  'F'
    0   =>  0011    =>  '0'
    1   =>  0100    =>  '1'
    2   =>  0101    =>  '2'
    3   =>  0110    =>  '3'
    4   =>  0111    =>  '4'
    5   =>  1000    =>  '5'
    6   =>  1001    =>  '6'
    7   =>  1011    =>  '7'
    8   =>  1100    =>  '8'
    9   =>  1101    =>  '9'
 True   =>  1110    =>  'T'
    ?   =>  1111    =>  '?'
*/