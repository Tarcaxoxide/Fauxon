#include<deque>
#include<string>
#include<iostream>
#include<cstdlib>
#include<cpp_wrapper/CommonParem.hpp>
#include<NeuralNetwork/TextNeuralNetwork.hpp>
#include<iomanip>
#include<fstream>



// "I love pizza" -> [["I"],["love"],["pizza"]]
// "I hate pizza" -> [["I"],["love","hate"],["pizza"]]
// "I love cats" ->  [["I"],["love","hate"],["pizza","cats"]]

namespace Fauxon{
    void Main(CommonParem_cl& Args){
        Fauxon::NeuralNetwork::TextNeuralNetwork_cl TextNeuralNetwork(100);
        TextNeuralNetwork.Import();
        
        std::deque<std::string> TrainingData;
        std::ifstream File("Sentences.txt");
        std::string Line="";
        while(std::getline(File,Line)){
            std::cout<<"?0:"<<Line<<std::endl;
            TrainingData.push_back(Line);
        }
        File.close();
        TextNeuralNetwork.Train(TrainingData,9000);
        TextNeuralNetwork.Export();

        std::string word="";
        while(std::getline(std::cin,Line,' ')){
            if(word.size()){word = TextNeuralNetwork.GetNextWord(word,Line);}else{word=Line;}
        }
    }
};
