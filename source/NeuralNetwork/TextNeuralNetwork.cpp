#include<NeuralNetwork/TextNeuralNetwork.hpp>
#include<fstream>
#include<json/value.h>
#include<json/json.h>
#include<json/writer.h>
#include<json/reader.h>

namespace Fauxon{
    namespace NeuralNetwork{
        TextNeuralNetwork_cl::TextNeuralNetwork_cl(std::deque<uint32_t> Topology,double LearningRate):SimpleNeuralNetwork(Topology,LearningRate){}
        std::string TextNeuralNetwork_cl::Export(std::string FileName){
            Json::FastWriter fastWriter;
            Json::Value DataToExport;
            SimpleNeuralNetwork.Export(FileName);
            std::ifstream iFile(FileName.c_str());
            iFile>>DataToExport;
            iFile.close();
            for(int iPosition=0;iPosition<SentenceData.size();iPosition++){
                for(int iWord=0;iWord<SentenceData[iPosition].size();iWord++){
                    DataToExport["SentenceData"][iPosition][iWord] = SentenceData[iPosition][iWord];
                }
            }
            std::ofstream oFile(FileName.c_str());
            oFile << fastWriter.write(DataToExport);
            oFile.close();
            return fastWriter.write(DataToExport);
        }
        std::string TextNeuralNetwork_cl::Import(std::string FileName){
            Json::FastWriter fastWriter;
            Json::Value DataToImport;
            SimpleNeuralNetwork.Import(FileName);
            std::ifstream File(FileName.c_str());
            File>>DataToImport;
            File.close();
            SentenceData.clear();
            SentenceData.resize(DataToImport["SentenceData"].size());
            for(int iPosition=0;iPosition<DataToImport["SentenceData"].size();iPosition++){
                SentenceData[iPosition].resize(DataToImport["SentenceData"][iPosition].size());
                for(int iWord=0;iWord<DataToImport["SentenceData"][iPosition].size();iWord++){
                    SentenceData[iPosition][iWord] = DataToImport["SentenceData"][iPosition][iWord].asString();
                }
            }
            return "";
        }
        void TextNeuralNetwork_cl::Input(std::string Sentence){
            std::deque<std::string> Words;
            std::string s;
            std::istringstream f(Sentence);
            while (std::getline(f, s, ' ')) {
                if(s[s.size()-1] == '\n')s[s.size()-1]=0;
                Words.push_back(s);
            }
            Words.push_back(ENDER);
            for(size_t iPosition=0;iPosition<Words.size();iPosition++){
                if(iPosition >= SentenceData.size()){
                    SentenceData.push_back({Words[iPosition]});
                }else{
                    bool New=true;
                    for(size_t iWord=0;iWord<SentenceData[iPosition].size();iWord++){
                        if(SentenceData[iPosition][iWord] == Words[iPosition])New=false;
                    }
                    if(New)SentenceData[iPosition].push_back(Words[iPosition]);
                }
            }
        }
        std::string TextNeuralNetwork_cl::Output(){
            std::string Result="";
            for(size_t iPosition=0;iPosition<SentenceData.size();iPosition++){
                size_t WordIndex = rand()%SentenceData[iPosition].size();
                std::string subResult=SentenceData[iPosition][WordIndex];
                if(subResult == ENDER)break;
                Result+=subResult+std::string(" ");
            }
            return Result;
        }
    };
};