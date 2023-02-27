#ifndef __Fauxon_DataType_Kinds
#define __Fauxon_DataType_Kinds
#include<stddef.h>
#include<stdint.h>
namespace Fauxon{
    namespace DataTypes{
        namespace Kinds{
            enum Kinds:size_t{
                Null=0,
                //ValueTypes
                Int64ValueType,
                //Tokens
                NumberToken
            };
        };
    };
};
#endif