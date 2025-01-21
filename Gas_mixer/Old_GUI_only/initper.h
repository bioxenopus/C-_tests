#ifndef INITPER_H
#define INITPER_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include "gmdata.h"


class initPer : public QObject
{
    Q_OBJECT
public:
    explicit initPer(QObject *parent,gmdata *d);
    unsigned char initDatOk;
    float A1; float B1;
    float A2; float B2;
    float A3; float B3;
    float A4; float B4;
    float A5; float B5;
    float A6; float B6;
    float A7; float B7;
    float A8; float B8;
    float A9; float B9;
    float A10; float B10;
    float A11; float B11;

    float receiverPmin=5.0;
    float receiverPmax=7.5;

    float setpointFull;
//    float percentNitrogen;
    float percentDioxide;
    float percentAir;
    float deltaNitrogen;
    float deltaDioxide;
    float deltaAir;
    float UspeedNitrogen;
    float UspeedAir;
    float UspeedDioxide;
    float UspeedDioxide1;
    float UspeedDioxide2;
    float UspeedDioxide3;
    float NspeedNitrogen;
    float NspeedAir;
    float NspeedDioxide;

    float seveUNitrogen;
    float seveUAir;
    float seveUDioxide;
    float seveUDioxide1;
    float seveUDioxide2;
    float seveUDioxide3;

    float alarmPresInput;
    float deltaAlarmCO2;
    float deltaAlarmO2;

    float coefficientO2;
    float defaultO2;

    void writeDat(float,float,float);
    void readUsDat(void);

    QString filnam;

private:
    QString tS;
    void setData(void);
    gmdata *gd;

signals:

public slots:
};

#endif // INITPER_H
