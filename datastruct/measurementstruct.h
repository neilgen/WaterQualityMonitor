#ifndef MEASUREMENTSTRUCT_H
#define MEASUREMENTSTRUCT_H

#include <QString>
#include <QDateTime>

enum MEASUREMENT_MODE_TYPE
{
    MEASUREMENT_MODE_ALL = 0, //手动自动
    MEASUREMENT_MODE_AUTO,    //自动
    MEASUREMENT_MODE_HAND    //手动
};

inline QString getStr_MEASUREMENT_MODE_TYPE(MEASUREMENT_MODE_TYPE t)
{
    switch(t){
    case MEASUREMENT_MODE_ALL:
        return QString::fromUtf8("手动自动");
    case MEASUREMENT_MODE_AUTO:
        return QString::fromUtf8("自动");
    case MEASUREMENT_MODE_HAND:
        return QString::fromUtf8("手动");
    }
    return QString::fromUtf8("手动自动");
}

inline  MEASUREMENT_MODE_TYPE get_MEASUREMENT_MODE_TYPE(QString str)
{
    if(str.contains(QString::fromUtf8("手动自动")))
    {
        return MEASUREMENT_MODE_ALL;
    }
    if(str.contains(QString::fromUtf8("自动")))
    {
        return MEASUREMENT_MODE_AUTO;
    }
    if(str.contains(QString::fromUtf8("手动")))
    {
        return MEASUREMENT_MODE_HAND;
    }
    return MEASUREMENT_MODE_ALL;
}

//仪器测量数据
struct Measurement
{
    int id;             //数据ID 唯一标示
    QDateTime datetime; //测量时间
    float consistence;  //浓度mg/L
    int range;          //量程
    float k;            //K值
    float b;            //B值
    MEASUREMENT_MODE_TYPE mode;           //模式
    int sign;           //数据标示
    float absorbance;   //吸光度 --管理员或仪器技术员
    float voltage;      //测量电压 --管理员或仪器技术员
    float voltage_ref;  //参比电压 --管理员或仪器技术员

    Measurement() {
        id = 0;
        datetime = QDateTime::fromTime_t(0);
        consistence = 0;
        range = 0;
        k = 0;
        b = 0;
        mode = MEASUREMENT_MODE_ALL;
        sign = 0;
        absorbance = 0;
        voltage = 0;
        voltage_ref = 0;
    }
    Measurement(const Measurement & m) {
        id = m.id;
        datetime = m.datetime;
        consistence = m.consistence;
        range = m.range;
        k = m.k;
        b = m.b;
        mode = m.mode;
        sign = m.sign;
        absorbance = m.absorbance;
        voltage = m.voltage;
        voltage_ref = m.voltage_ref;
    }
    void operator =(const Measurement &m){
        id = m.id;
        datetime = m.datetime;
        consistence = m.consistence;
        range = m.range;
        k = m.k;
        b = m.b;
        mode = m.mode;
        sign = m.sign;
        absorbance = m.absorbance;
        voltage = m.voltage;
        voltage_ref = m.voltage_ref;
    }
};

#endif // MEASUREMENTSTRUCT_H
