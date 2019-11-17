#include "vardata.h"

VarData::VarData(QObject *parent) :
    QObject(parent)
{
    this->parse();
}

VarData *VarData::getIns()
{
    static VarData vd;
    return &vd;
}

void VarData::parse()
{
}

void VarData::save()
{
}

QList<Var> VarData::getVars() const
{
    return vars;
}

void VarData::setVars(const QList<Var> &vs)
{
    vars = vs;
}
