#include "processdata.h"

ProcessData::ProcessData(QObject *parent) :
    QObject(parent)
{
    this->parse();
}

ProcessData *ProcessData::getIns()
{
    static ProcessData pData;
    return &pData;
}

void ProcessData::parse()
{
    //添加解析代码
}

void ProcessData::save()
{
    //添加保存代码
}

QList<Action> ProcessData::getActions() const
{
    return actions;
}

void ProcessData::setActions(const QList<Action> &as)
{
    actions = as;
}

QList<ActionBag> ProcessData::getActionBags() const
{
    return actionBags;
}

void ProcessData::setActionBags(const QList<ActionBag> &abs)
{
    actionBags = abs;
}

QList<Process> ProcessData::getProcesses() const
{
    return processes;
}

void ProcessData::setProcesses(const QList<Process> &ps)
{
    processes = ps;
}
