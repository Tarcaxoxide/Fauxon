#pragma once
#include<fstream>
#include<string>

struct File_st{
    std::fstream File;
    std::string Line;
    size_t current_line=0;
    File_st(std::string FileName){
        File.open(FileName.c_str(),std::ios::in|std::ios::out);
    }
    ~File_st(){
        File.close();
    }
    File_st& operator[](size_t index){
        File.seekp(index);
        File.seekg(index);
        return *this;
    }
    File_st& operator<<(char c){
        File.clear();
        File<<c;
        return *this;
    }
    File_st& operator>>(char& c){
        File.clear();
        File>>c;
        return *this;
    }
};

struct Filestream_st{
    File_st File;
    Filestream_st(std::string FileName):File(FileName){}
};