#pragma once
#include<NeuralNetwork/SimpleNeuralNetwork.hpp>

namespace Fauxon{
    namespace NeuralNetwork{
        class TextNeuralNetwork_cl{
            SimpleNeuralNetwork_cl SimpleNeuralNetwork;
            std::deque<std::deque<std::string>> SentenceData;
            std::string ENDER="____END____";
            public:
            TextNeuralNetwork_cl(std::deque<uint32_t> Topology,double LearningRate=0.01);
            std::string Export(std::string FileName="Save.json");
            std::string Import(std::string FileName="Save.json");
            void Input(std::string Sentence);
            std::string Output();
        };
    };
};