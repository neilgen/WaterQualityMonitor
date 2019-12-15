#ifndef MEASUREMENTDATA_H
#define MEASUREMENTDATA_H

#include <QObject>
#include "measurementstruct.h"
#include "waterdb.h"

class MeasurementData : public QObject
{
    Q_OBJECT
private:
    explicit MeasurementData(QObject *parent = 0);

public:
    static MeasurementData * getIns();

    //添加数据，仪器生成数据后添加,对于新数据不用考虑ID初始化，该函数会自动添加ID
    void addMeasurement(const Measurement & m);
    void modifyMeasurement(int id, QDateTime dt, float consistence,
                           MEASUREMENT_MODE_TYPE mode, int sign);
    void deleteMeasurement(int id);

    //获取数据
    QList<Measurement> getMeasurement() const ;

    QList<Measurement> getMeasurement(
            int minRange, int maxRange,
            const QDateTime beginDt, const QDateTime endDt, MEASUREMENT_MODE_TYPE mode) const ;

private:
    //初始化存仪器数据sqlite表，没有就添加，
    void initMeasurementTable();

};

#endif // MEASUREMENTDATA_H
