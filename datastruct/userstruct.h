#ifndef USERSTRUCT_H
#define USERSTRUCT_H

#include <QString>
#include <QList>

//用户权限类型
enum USER_PERMISSION_TYPE
{
    USER_PERMISSION_NULL = 0,  //无权限,游客
    USER_PERMISSION_ACTOR = 1,     //操作员权限
    USER_PERMISSION_MANAGER = 2,   //管理员权限
    USER_PERMISSION_MAINTAIN = 3,  //仪器维护技术员
    USER_PERMISSION_SUPER = 4,  //超级管理员

    //在上方添加用户类型
    USER_PERMISSION_TYPE_COUNT      //用户权限类型上限
};

//用户加密方式，与用户权限相对应
enum USER_ENCRYPTION_TYPE
{
    USER_ENCRYPTION_NULL = 0,   //无，不需要密码,游客适用
    USER_ENCRYPTION_FIXED = 1,  //固定密码
    USER_ENCRYPTION_DATE = 2,   //根据当前日期计算密码
    USER_ENCRYPTION_RANDOM = 3,     //随机密码

    //
    USER_ENCRYPTION_TYPE_COUNT
};

struct User
{
    int id;     //用户ID
    QString name;   //用户名
    USER_PERMISSION_TYPE permission;    //用户权限
    USER_ENCRYPTION_TYPE encryption;    //用户加密方式
    QString passwd; //用户密码，当加密方式为USER_ENCRYPTION_FIXED时才可用
    User()
    {
        id = 0;
        name = "";
        permission = USER_PERMISSION_NULL;
        encryption = USER_ENCRYPTION_NULL;
        passwd = "";
    }
    User(const User & u)
    {
        id = u.id;
        name = u.name;
        permission = u.permission;
        encryption = u.encryption;
        passwd = u.passwd;
    }
    void operator =(const User &u){
        id = u.id;
        name = u.name;
        permission = u.permission;
        encryption = u.encryption;
        passwd = u.passwd;
    }

    bool operator ==(const User &u){
        return id == u.id;
    }
};

#endif // USERSTRUCT_H
