#ifndef PROCESSDATA_H
#define PROCESSDATA_H

#include <QObject>
#include "processstruct.h"

//流程配置数据类
class ProcessData : public QObject
{
    Q_OBJECT
private:
    explicit ProcessData(QObject *parent = 0);
    
public:
    static ProcessData * getIns();

    //解析数据
    void parse();
    //保存配置
    void save();

    //获取设置动作
    QList<Action> getActions() const;
    void setActions(const QList<Action> &as);

    //获取设置动作包
    QList<ActionBag> getActionBags() const;
    void setActionBags(const QList<ActionBag> & abs);

    //保存设置流程
    QList<Process> getProcesses() const;
    void setProcesses(const QList<Process> & ps);

private:
    QList<Action> actions;
    QList<ActionBag> actionBags;
    QList<Process> processes;
};

#endif // PROCESSDATA_H
