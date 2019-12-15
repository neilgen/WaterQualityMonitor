#ifndef VARDATA_H
#define VARDATA_H

#include <QObject>
#include <QList>
#include "varstruct.h"

class VarData : public QObject
{
    Q_OBJECT
private:
    explicit VarData(QObject *parent = 0);
    
public:
    static VarData * getIns();

    //解析数据
    void parse();
    //保存配置
    void save();

    QList<Var> getVars() const;
    void setVars(const QList<Var> & vs);

private:
    QList<Var> vars;
};

#endif // VARDATA_H
