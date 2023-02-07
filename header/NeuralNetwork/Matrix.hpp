#pragma once
#include<cstdint>
#include<deque>
#include<cmath>
#include<cassert>
#include<functional>

namespace Fauxon{
    namespace NeuralNetwork{
        class Matrix_cl{
            public:
                uint32_t _Columns,_Rows;
                std::deque<double> _Values;
            public:
                Matrix_cl(){}
                Matrix_cl(uint32_t Columns,uint32_t Rows);
                double& At(uint32_t Column,uint32_t Row);
                double& operator[](size_t index);
                size_t size();
                Matrix_cl Multiply(Matrix_cl& Target);
                Matrix_cl MultiplyElements(Matrix_cl& Target);
                Matrix_cl MultiplyScalar(double Scalar);
                Matrix_cl Add(Matrix_cl& Target);
                Matrix_cl AddScalar(double Scalar);
                Matrix_cl Negative();
                Matrix_cl Transpose();
                Matrix_cl ApplyFunction(std::function<double(const double& Vin)> Fun);
        };
    };
};