#ifndef PROCESSSTRUCT_H
#define PROCESSSTRUCT_H

#include <QString>
#include <QList>

///----------------------------动作----------------------------///

//动作参数类型
enum ACTION_PARAM_TYPE
{
    ACTION_PARAM_NULL = 0,      //无参数，无效参数
    ACTION_PARAM_SWITCH = 1,    //开关
    ACTION_PARAM_PORT = 2,      //阀口
    ACTION_PARAM_TIME = 3,      //时间
    ACTION_PARAM_HAVE = 4,      //有无
    ACTION_PARAM_ROTATION_RATE = 5,     //转速
    ACTION_PARAM_DELAY = 6,     //延时

    //在上方添加动作参数
    ACTION_PARAM_COUNT      //参数上限
};

//动作参数
struct ActionParam
{
    ACTION_PARAM_TYPE type;    //参数类型
    int value;      //参数值
    bool editable;  //参数是否可编辑
    ActionParam(){
        type = ACTION_PARAM_NULL;
        value = 0;
        editable = false;
    }
    ActionParam(const ActionParam &p){
        this->type = p.type;
        this->value = p.value;
        this->editable = p.editable;
    }
    void operator =(const ActionParam &p){
        this->type = p.type;
        this->value = p.value;
        this->editable = p.editable;
    }
    bool operator ==(const ActionParam &p){
        return this->type == p.type;    //先这样判断
    }
};

//动作
struct Action
{
    int id ;    //动作ID
    QString code;   //代号
    QString name;   //名称
    QList<ActionParam> params;     //参数，一般有两个
    Action(){
        id = 0;
        code = "";
        name = "";
    }
    Action(const Action & a){
        this->id = a.id;
        this->code = a.code;
        this->params = a.params;
    }
    void operator =(const Action & a){
        this->id = a.id;
        this->code = a.code;
        this->params = a.params;
    }
    bool operator ==(const Action & a){
        return this->code == a.code;//先这样判断
    }
};

///----------------------------动作包----------------------------///

//动作包参数类型
enum ACTIONBAG_PARAM_TYPE
{
    ACTIONBAG_PARAM_NULL = 0,   //无参数，无效参数
    ACTIONBAG_PARAM_PORT = 1,   //阀口
    ACTIONBAG_PARAM_TEMP = 2,   //温度
    ACTIONBAG_PARAM_LIGHT = 3,  //光通道
    ACTIONBAG_PARAM_TIME = 4,   //时间

    //在上方添加动作包参数类型
    ACTIONBAG_PARAM_COUNT
};

//动作包参数
struct ActionBagParam
{
    ACTIONBAG_PARAM_TYPE type;  //类型

    //可能会添加动作包参数需要的其他项（）比如说值

    ActionBagParam(){
        type = ACTIONBAG_PARAM_NULL;
    }
    ActionBagParam(const ActionBagParam & a){
        this->type = a.type;
    }
    void operator =(const ActionBagParam & a){
        this->type = a.type;
    }
    bool operator ==(const ActionBagParam & a){
        return this->type == a.type;//先这样判断
    }
};

//动作包
struct ActionBag
{
    int id;     //ID
    QString code;   //代号
    QString name;   //名称
    QString desc;   //描述
    int param_num;  //参数量（参数的数量）可以不要，后面考虑
    QList<ActionBagParam> params; //参数

    ActionBag(){
        id = 0;
        code = "";
        name = "";
        desc = "";
        param_num = 0;
    }
    ActionBag(const ActionBag &a){
        this->id = a.id;
        this->code = a.code;
        this->name = a.name;
        this->desc = a.desc;
        this->param_num = a.param_num;
        this->params = a.params;
    }
    void operator =(const ActionBag & a){
        this->id = a.id;
        this->code = a.code;
        this->name = a.name;
        this->desc = a.desc;
        this->param_num = a.param_num;
        this->params = a.params;
    }
    bool operator ==(const ActionBag & a){
        return this->code == a.code; //先这样判断
    }
};

///----------------------------量程动作流程----------------------------///

//量程动作流程 参数类型
enum PRPCESS_PARAM_TYPE
{
    PRPCESS_PARAM_NULL = 0,     //无效参数
    PRPCESS_PARAM_PORT = 1,     //阀口
    PRPCESS_PARAM_NUM = 2,    //次数
    PRPCESS_PARAM_TEMP = 3,     //温度
    PRPCESS_PARAM_TIME = 4,     //时间
    PRPCESS_PARAM_LIGHT = 5,    //光通道
    //在上方添加
    PRPCESS_PARAM_COUNT
};

//量程动作流程 参数
struct ProcessParam
{
    PRPCESS_PARAM_TYPE type;    //类型
    int value;  //参数值
    ProcessParam(){
        type = PRPCESS_PARAM_NULL;
        value = 0;
    }
    ProcessParam(const ProcessParam & p){
        this->type = p.type;
        this->value = p.value;
    }
    void operator =(const ProcessParam & p){
        this->type = p.type;
        this->value = p.value;
    }
    bool operator ==(const ProcessParam & p){
        return this->type == p.type;    //先这样
    }
};

//量程动作流程
struct Process
{
    int id;     //id
    QString code;   //代号
    QString name;   //名称
    QString return_value;   //返回值，不确定值的类型
    QList<ProcessParam> params; //参数
    Process(){
        id = 0;
        code = "";
        name = "";
        return_value = "";
    }
    Process(const Process & p){
        this->id = p.id;
        this->code = p.code;
        this->name = p.name;
        this->return_value = p.return_value;
        this->params = p.params;
    }
    void operator =(const Process & p){
        this->id = p.id;
        this->code = p.code;
        this->name = p.name;
        this->return_value = p.return_value;
        this->params = p.params;
    }
    bool operator ==(const Process & p){
        return this->code == p.code;
    }
};


#endif // PROCESSSTRUCT_H
