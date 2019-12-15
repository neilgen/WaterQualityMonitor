#ifndef VARSTRUCT_H
#define VARSTRUCT_H

#include <QString>

//变量设计
struct Var
{
    QString var_name;    //变量名
    QString var_desc;      //变量的描述
    double var_value;     //变量的值

    Var(){
        var_value = 0;      //变量初始值，默认值
    }

    Var(const Var &v){
        var_name = v.var_name;
        var_desc = v.var_desc;
        var_value = v.var_value;
    }

   void operator =(const Var &v){
        var_name = v.var_name;
        var_desc = v.var_desc;
        var_value = v.var_value;
    }

    bool operator ==(const Var &v){
        return var_name == v.var_name;
    }
};

#endif // VARSTRUCT_H
