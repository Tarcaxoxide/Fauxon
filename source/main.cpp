#include<deque>
#include<string>
#include<iostream>
#include<cstdlib>
#include<cpp_wrapper/CommonParem.hpp>
#include<NeuralNetwork/TextNeuralNetwork.hpp>
#include<iomanip>



// "I love pizza" -> [["I"],["love"],["pizza"]]
// "I hate pizza" -> [["I"],["love","hate"],["pizza"]]
// "I love cats" ->  [["I"],["love","hate"],["pizza","cats"]]

namespace Fauxon{
    void Main(CommonParem_cl& Args){
        Fauxon::NeuralNetwork::TextNeuralNetwork_cl TextNeuralNetwork(100);
        TextNeuralNetwork.Import();
        TextNeuralNetwork.Input("I love pizza");
        TextNeuralNetwork.Input("I love cats");
        TextNeuralNetwork.Input("I love cars");
        TextNeuralNetwork.Input("I hate politicians");
        TextNeuralNetwork.Input("Pizza is too expensive");

        std::deque<double> v = TextNeuralNetwork.WordToVector("hate");
        std::cout<<"?"<<TextNeuralNetwork.VectorToWord(v)<<std::endl;

        TextNeuralNetwork.Export();
    }
};
