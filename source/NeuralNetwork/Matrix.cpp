#include<NeuralNetwork/Matrix.hpp>

namespace Fauxon{
    namespace NeuralNetwork{
        Matrix_cl::Matrix_cl(uint32_t Columns,uint32_t Rows):_Columns(Columns),_Rows(Rows),_Values({}){
            _Values.resize(Columns*Rows,0.0f);
        }
        double& Matrix_cl::At(uint32_t Column,uint32_t Row){
            return _Values[Row*_Columns+Column];
        }
        double& Matrix_cl::operator[](size_t index){
            return _Values[index];
        }
        size_t Matrix_cl::size(){
            return _Values.size();
        }
        Matrix_cl Matrix_cl::Multiply(Matrix_cl& Target){
            assert(_Columns == Target._Rows);
            Matrix_cl Result(Target._Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    double subResult = 0.0;
                    for(uint32_t k=0;k<_Columns;k++){
                        subResult+=At(k,y)*Target.At(x,k);
                    }
                    Result.At(x,y)=subResult;
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::MultiplyElements(Matrix_cl& Target){
            assert(Target._Rows == _Rows);
            assert(Target._Columns == _Columns);
            Matrix_cl Result(_Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=At(x,y)*Target.At(x,y);
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::MultiplyScalar(double Scalar){
            Matrix_cl Result(_Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=At(x,y)*Scalar;
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::Add(Matrix_cl& Target){
            assert(_Rows == Target._Rows);
            assert(_Columns == Target._Columns);
            Matrix_cl Result(_Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=At(x,y)+Target.At(x,y);
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::AddScalar(double Scalar){
            Matrix_cl Result(_Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=At(x,y)+Scalar;
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::Negative(){
            Matrix_cl Result(_Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=-At(x,y);
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::Transpose(){
            Matrix_cl Result(_Rows,_Columns);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=At(y,x);
                }
            }
            return Result;
        }
        Matrix_cl Matrix_cl::ApplyFunction(std::function<double(const double& Vin)> Fun){
            Matrix_cl Result(_Columns,_Rows);
            for(uint32_t y=0;y<Result._Rows;y++){
                for(uint32_t x=0;x<Result._Columns;x++){
                    Result.At(x,y)=Fun(At(x,y));
                }
            }
            return Result;
        }
    };
};