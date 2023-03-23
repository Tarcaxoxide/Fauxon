#pragma once
#include<string>
struct minifloat{
	uint8_t Sign:1;
	uint8_t Whole:3;
	uint8_t Decimal:4;
	inline std::string str(){return std::string(Sign?"+":"-")+std::to_string(Whole)+std::string(".")+std::to_string(Decimal);}
	inline float flo(){float r=Sign?1:-1;r*=Whole;r+=(((float)Decimal)*0.01);return r;}
}__attribute__((packed));
struct PixelStructure{
	minifloat Position_Scalar;
	uint8_t Position_X;
	uint8_t Position_Y;
	uint8_t Position_Z;
	uint8_t Color_Red;
	uint8_t Color_Green;
	uint8_t Color_Blue;
	uint8_t Color_Alpha;
	inline std::string str(){return std::string("{")+Position_Scalar.str()+std::string(":")+std::to_string(Position_X)+std::string(":")+std::to_string(Position_Y)+std::string(":")+std::to_string(Position_Z)+std::string(",")+std::to_string(Color_Red)+std::string(":")+std::to_string(Color_Green)+std::string(":")+std::to_string(Color_Blue)+std::string(":")+std::to_string(Color_Alpha)+std::string("}");}
}__attribute__((packed));
