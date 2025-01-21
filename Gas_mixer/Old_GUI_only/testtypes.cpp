#include "testtypes.h"

//////// klapan
klapan::klapan(QObject *parent) : QObject(parent)
{}

int klapan::setKlap(uint, uint)
{

}
//////// spi

spi::spi(QObject *parent, gmdata* gd): QObject(parent), gd(gd){

}

//////// spiDAC

spiDAC::spiDAC(QObject *parent) : QObject(parent)
{}


//////// objnorwork

objnorwork::objnorwork(QObject *parent, gmdata *gd, spi *datSpi, spiDAC *wDAC, klapan *setKL) : QObject(parent),
    gd(gd),
    datSpi(datSpi),
    wDAC(wDAC),
    setKL(setKL)
{}

void objnorwork::testPre(void){qDebug()<<"objnorwork::testPre"<<'\n';}
void objnorwork::stopDAC(void){qDebug()<<"objnorwork::stopDACe"<<'\n';}
void objnorwork::startDAC(void){qDebug()<<"objnorwork::startDAC"<<'\n';}
void objnorwork::setKl3(unsigned char ve){qDebug()<<"objnorwork::setKl3"<<'\n';}
void objnorwork::setPressure(void){qDebug()<<"objnorwork::setPressure"<<'\n';}

//////// setDatTim

setDatTim::setDatTim(QObject *parent) : QObject(parent)
{}

void setDatTim::readTim(void){qDebug()<<"setDatTim::readTim"<<'\n';}
void setDatTim::setRasTD(void){qDebug()<<"setDatTim::setRasTD"<<'\n';}
void setDatTim::setRtcTD(void){qDebug()<<"setDatTim::setRtcTD"<<'\n';}

////////
objselgas::objselgas(QObject *parent, spi *datSpi, spiDAC *wDAC, klapan *setKL, gmdata *gd) : QObject(parent),
    datSpi(datSpi),
    wDAC(wDAC),
    setKL(setKL),
    gd(gd)
{}

void objselgas::on_Can(){qDebug()<<"objselgas::on_Can"<<'\n';}
void objselgas::on_S(){qDebug()<<"objselgas::on_S"<<'\n';}
void objselgas::on_C(){qDebug()<<"objselgas::on_C"<<'\n';}
void objselgas::on_O(){qDebug()<<"objselgas::on_O"<<'\n';}
void objselgas::on_P(){qDebug()<<"objselgas::on_P"<<'\n';}
void objselgas::on_Up(){qDebug()<<"objselgas::on_Up"<<'\n';}
void objselgas::on_SA(int){qDebug()<<"objselgas::on_SA"<<'\n';}
void objselgas::setkl4(){qDebug()<<"objselgas::setkl4"<<'\n';}
void objselgas::stopAUTO(void){qDebug()<<"objselgas::stopAUTO"<<'\n';}
void objselgas::startMesu(void){qDebug()<<"objselgas::startMesu"<<'\n';}
