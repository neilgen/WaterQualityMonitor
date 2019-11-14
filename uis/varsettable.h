#ifndef VARSETTABLE_H
#define VARSETTABLE_H

#include <QWidget>
#include "datastruct.h"

namespace Ui {
class VarSetTable;
}

class VarSetTable : public QWidget
{
    Q_OBJECT
    
public:
    explicit VarSetTable(QWidget *parent = 0);
    ~VarSetTable();
    
private slots:
    void onAdd();
    void onRemove();
    void onCancel();
    void onApply();

private:
    void readConf();
    void writeConf();

private:
    Ui::VarSetTable *ui;

    ListVar mListVar;
};

#endif // VARSETTABLE_H
