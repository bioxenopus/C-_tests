#ifndef GMDATA_H
#define GMDATA_H

#include <QObject>

class gmdata : public QObject
{
    Q_OBJECT
public:
    explicit gmdata(QObject *parent = nullptr);
    struct ust_dat
    {
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
        float setpointFull;
        float percentDioxide;
        float percentAir;
        float setpointNitrogen;
        float setpointAir;
        float setpointDioxide;
        float deltaNitrogen;
        float deltaAir;
        float deltaDioxide;
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
        float receiverPmax;
        float receiverPmin;
        float coefficientO2;
        float defaultO2;
        float setpointFullO2;
        float vNull;
        float opKl2;


    }u_d;
//    ust_dat u_d;
    float flowNitrogen;
    float flowAir;
    float flowDioxide;
    float uoutNitrogen;
    float uoutAir;
    float uoutDioxide;
    float PressureOUT;
    float ConsumptionOUT;
    float receiverP;

    float opora;
    float dacLSB;
    float coefficient;

    float CO2_p;
    float O2_p;

    float presN;
    float presA;
    float presC;
    unsigned char  errpresN;
    unsigned char  errpresA;
    unsigned char  errpresC;
    unsigned char  errpCO2;
    unsigned char  errpO2;
private:

signals:

public slots:
};

#endif // GMDATA_H
