#ifndef TESTTYPES_H
#define TESTTYPES_H

#include <QObject>
#include <QWidget>

#include "gmdata.h"
#include "initper.h"

class klapan;
class spi;
class spiDAC;
class objnorwork;
class setDatTim;
class objselgas;

class klapan : public QObject{
public:
    klapan(QObject *parent = nullptr);
    int setKlap(uint, uint);
};

class spi : public QObject{
public:
    spi(QObject *parent = nullptr, gmdata* gd = nullptr);
public:
    gmdata* gd;

};

class spiDAC : public QObject{
public:
    spiDAC(QObject *parent);

};

class objnorwork : public QObject{
public:
    objnorwork(QObject *parent = nullptr, gmdata *m=0,spi *d=0,spiDAC *w=0,klapan *s=0);

    void testPre(void);
    void stopDAC(void);
    void startDAC(void);
    void setKl3(unsigned char ve);
    void setPressure(void);

public:
    gmdata *gd;
    spi *datSpi;
    spiDAC *wDAC;
    klapan *setKL;
    unsigned char LstatusR;
    unsigned char statusR;
};

class setDatTim : public QObject{
public:
    setDatTim(QObject *parent = nullptr);
    void readTim(void);
    void setRasTD(void);
    void setRtcTD(void);
};

class objselgas : public QObject{
public:
    objselgas(QObject *parent = nullptr,spi *s = 0,spiDAC *di=0,klapan *kl=0,gmdata *d=0);

    void on_Can();
    void on_S();
    void on_C();
    void on_O();
    void on_P();
    void on_Up();
    void on_SA(int);
    void setkl4();
    void stopAUTO(void);
    void startMesu(void);


public:
    spi *datSpi;
    spiDAC *wDAC;
    klapan *setKL;
    gmdata *gd;


    float receiverP;
    float receiverPmin;
    float receiverPmax;
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

    float flowNitrogen;
    float flowAir;
    float flowDioxide;
    float uoutNitrogen;
    float uoutAir;
    float uoutDioxide;
    float PressureOUT;
    float ConsumptionOUT;

    float alarmPresInput;
    float deltaAlarmCO2;
    float deltaAlarmO2;


    float CO2_p;
    float CO2_Set;
    float O2_p;
    float O2_Set;

    float presN;
    float presA;
    float presC;

    float Vinit;
    float Vmes;
    float PresInit;
    float CO2_Cor;
    float O2_Cor;
    float full;

    float alarmPoint;
    QString A;
    float AA;
    QString fullText;//LineE1
    QString CO2setText;//LineE5
    QString PresInitText;//LineE4
    QString AirsetText;//LineE3
    QString O2setText;
    unsigned char trigSt;
    unsigned char trigStopAuto=0;
    unsigned char workOK;
    unsigned char reStart;

    unsigned char regStatusAuto=0;
    unsigned char startA=0;


    float ustP;
};

#endif // TESTTYPES_H

