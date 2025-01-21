#include "initper.h"
#include <QDebug>
#include "mdef.h"

initPer::initPer(QObject *parent, gmdata *d) : QObject(parent)
{
    gd=d;
initDatOk=0;
A1=0.5; B1=2000;
A2=0.5; B2=200;
A3=0.5; B3=1000;


A4=0.5; B4=2000; //?????????
A5=0.5; B5=2000; //?????????
A6=0.5; B6=1000; //?????????

A7=1; B7=0.4;
A8=0.5; B8=2000;
A9=0.5; B9=1000; //?????????

A8=0.4; B10=0.2;
A11=0.5; B11=1000; //?????????


receiverPmin=5.0;
receiverPmax=7.5;

setpointFull = 2000.0;
percentDioxide = 6.0;
percentAir = 4.99;
deltaNitrogen = 87.5;
deltaDioxide = 8.75;
deltaAir = 43.7;
UspeedNitrogen = 0.2;
UspeedAir = 0.2;
UspeedDioxide = 0.2;
UspeedDioxide1 = 0.2;
UspeedDioxide2 = 0.2;
UspeedDioxide3 = 0.2;

NspeedNitrogen = 0.2;
NspeedAir = 0.2;
NspeedDioxide = 0.2;

seveUNitrogen=2.9;
seveUAir=2.9;
seveUDioxide=2.9;
seveUDioxide1=2.9;
seveUDioxide2=2.9;
seveUDioxide3=2.9;

alarmPresInput=3.4;

deltaAlarmCO2 = 0.30;
deltaAlarmO2 = 0.50;

tS="";
#ifdef RASPBERRY
tS="/home/pi/Gdata/user_data.conf";
#else
tS=QDir::homePath() + QDir::separator()+"/Gdata/user_data.conf";
#endif
    setData();


}
//================================================================================
void initPer::readUsDat(void)
{
    QSettings settings( tS, QSettings::IniFormat );


    settings.beginGroup( "Chan1" );
    gd->u_d.A1= settings.value( "A1").toFloat();
    gd->u_d.B1= settings.value( "B1").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan2" );
    gd->u_d.A2= settings.value( "A2").toFloat();
    gd->u_d.B2= settings.value( "B2").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan3" );
    gd->u_d.A3= settings.value( "A3").toFloat();
    gd->u_d.B3= settings.value( "B3").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan4" );
    gd->u_d.A4= settings.value( "A4").toFloat();
    gd->u_d.B4= settings.value( "B4").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan5" );
    gd->u_d.A5= settings.value( "A5").toFloat();
    gd->u_d.B5= settings.value( "B5").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan6" );
    gd->u_d.A6= settings.value( "A6").toFloat();
    gd->u_d.B6= settings.value( "B6").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan7" );
    gd->u_d.A7= settings.value( "A7").toFloat();
    gd->u_d.B7= settings.value( "B7").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan8" );
    gd->u_d.A8= settings.value( "A8").toFloat();
    gd->u_d.B8= settings.value( "B8").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan9" );
    gd->u_d.A9= settings.value( "A9").toFloat();
    gd->u_d.B9= settings.value( "B9").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan10" );
    gd->u_d.A10= settings.value( "A10").toFloat();
    gd->u_d.B10= settings.value( "B10").toFloat();
    settings.endGroup();
    settings.beginGroup( "Chan11" );
    gd->u_d.A11= settings.value( "A11").toFloat();
    gd->u_d.B11= settings.value( "B11").toFloat();
    settings.endGroup();

    settings.beginGroup( "DacDat" );
    gd->u_d.receiverPmin=settings.value( "receiverPmin").toFloat();
    gd->u_d.receiverPmax=settings.value( "receiverPmax").toFloat();

    gd->u_d.setpointFull = settings.value( "setpointFull").toFloat();
    gd->u_d.percentDioxide = settings.value( "percentDioxide").toFloat();
    gd->u_d.percentAir = settings.value( "percentAir").toFloat();
    gd->u_d.deltaNitrogen = settings.value( "deltaNitrogen").toFloat();
    gd->u_d.deltaDioxide = settings.value( "deltaDioxide").toFloat();
    gd->u_d.deltaAir = settings.value( "deltaAir").toFloat();
    gd->u_d.UspeedNitrogen = settings.value( "UspeedNitrogen").toFloat();
    gd->u_d.UspeedAir = settings.value( "UspeedAir").toFloat();
    gd->u_d.UspeedDioxide = settings.value( "UspeedDioxide").toFloat();
    gd->u_d.UspeedDioxide1 = settings.value( "UspeedDioxide1").toFloat();
    gd->u_d.UspeedDioxide2 = settings.value( "UspeedDioxide2").toFloat();
    gd->u_d.UspeedDioxide3 = settings.value( "UspeedDioxide3").toFloat();
    gd->u_d.NspeedNitrogen = settings.value( "NspeedNitrogen").toFloat();
    gd->u_d.NspeedAir = settings.value( "NspeedAir").toFloat();
    gd->u_d.NspeedDioxide = settings.value( "NspeedDioxide").toFloat();
    gd->u_d.seveUNitrogen = settings.value( "seveUNitrogen").toFloat();
    gd->u_d.seveUAir = settings.value( "seveUAir").toFloat();
    gd->u_d.seveUDioxide = settings.value( "seveUDioxide").toFloat();
    gd->u_d.seveUDioxide1 = settings.value( "seveUDioxide1").toFloat();
    gd->u_d.seveUDioxide2 = settings.value( "seveUDioxide2").toFloat();
    gd->u_d.seveUDioxide3 = settings.value( "seveUDioxide3").toFloat();

    gd->u_d.alarmPresInput = settings.value( "alarmPresInput").toFloat();

    gd->u_d.deltaAlarmCO2 = settings.value( "deltaAlarmCO2").toFloat();
    gd->u_d.deltaAlarmO2 = settings.value( "deltaAlarmO2").toFloat();


    gd->u_d.coefficientO2 = settings.value( "coefficientO2").toFloat();
    gd->u_d.defaultO2 = settings.value( "defaultO2").toFloat();
    settings.endGroup();

    settings.beginGroup( "AdditionSet" );
    gd->u_d.vNull = settings.value( "vNull").toFloat();
    gd->u_d.setpointFullO2 = settings.value( "setpointFullO2").toFloat();
    gd->u_d.opKl2 = settings.value( "opKl2").toFloat();
    settings.endGroup();

// qDebug() << "A1=" << A1;

}
//================================================================================
void initPer::writeDat(float f,float d,float a)
{
    QSettings settings( tS, QSettings::IniFormat );
    settings.beginGroup( "DacDat" );
    settings.setValue("setpointFull",QString::number(f,'f',2));
    settings.setValue("percentDioxide",QString::number(d,'f',2));
    settings.setValue("percentAir",QString::number(a,'f',2));
    settings.setValue("coefficientO2",QString::number(gd->u_d.coefficientO2,'f',3));
    settings.endGroup();

}
//================================================================================
void initPer::setData(void)
{
if (QFile::exists(tS))
 {

 }
else
 {
    QSettings settings( tS, QSettings::IniFormat );

    settings.beginGroup( "Chan1" );
    settings.setValue( "A1",QString::number(A1,'f',2));
    settings.setValue("B1",QString::number(B1,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan2" );
    settings.setValue( "A2",QString::number(A2,'f',2));
    settings.setValue("B2",QString::number(B2,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan3" );
    settings.setValue("A3",QString::number(A3,'f',2));
    settings.setValue("B3",QString::number(B3,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan4" );
    settings.setValue("A4",QString::number(A4,'f',2));
    settings.setValue("B4",QString::number(B4,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan5" );
    settings.setValue("A5",QString::number(A5,'f',2));
    settings.setValue("B5",QString::number(B5,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan6" );
    settings.setValue("A6",QString::number(A6,'f',2));
    settings.setValue("B6",QString::number(B6,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan7" );
    settings.setValue("A7",QString::number(A7,'f',2));
    settings.setValue("B7",QString::number(B7,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan8" );
    settings.setValue("A8",QString::number(A8,'f',2));
    settings.setValue("B8",QString::number(B8,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan9" );
    settings.setValue("A9",QString::number(A9,'f',2));
    settings.setValue("B9",QString::number(B9,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan10" );
    settings.setValue("A10",QString::number(A10,'f',2));
    settings.setValue("B10",QString::number(B10,'f',2));
    settings.endGroup();
    settings.beginGroup( "Chan11" );
    settings.setValue("A11",QString::number(A11,'f',2));
    settings.setValue("B11",QString::number(B11,'f',2));
    settings.endGroup();

    settings.beginGroup( "DacDat" );
    settings.setValue("receiverPmin",QString::number(receiverPmin,'f',2));
    settings.setValue("receiverPmax",QString::number(receiverPmax,'f',2));

    settings.setValue("setpointFull",QString::number(setpointFull,'f',2));
    settings.setValue("percentDioxide",QString::number(percentDioxide,'f',2));
    settings.setValue("percentAir",QString::number(percentAir,'f',2));
    settings.setValue("deltaNitrogen",QString::number(deltaNitrogen,'f',2));
    settings.setValue("deltaDioxide",QString::number(deltaDioxide,'f',2));
    settings.setValue("deltaAir",QString::number(deltaAir,'f',2));
    settings.setValue("UspeedNitrogen",QString::number(UspeedNitrogen,'f',3));
    settings.setValue("UspeedAir",QString::number(UspeedAir,'f',3));
    settings.setValue("UspeedDioxide",QString::number(UspeedDioxide,'f',3));
    settings.setValue("UspeedDioxide1",QString::number(UspeedDioxide1,'f',3));
    settings.setValue("UspeedDioxide2",QString::number(UspeedDioxide2,'f',3));
    settings.setValue("UspeedDioxide3",QString::number(UspeedDioxide3,'f',3));
    settings.setValue("NspeedNitrogen",QString::number(NspeedNitrogen,'f',3));
    settings.setValue("NspeedAir",QString::number(NspeedAir,'f',3));
    settings.setValue("NspeedDioxide",QString::number(NspeedDioxide,'f',3));

    settings.setValue("seveUNitrogen",QString::number(seveUNitrogen,'f',3));
    settings.setValue("seveUAir",QString::number(seveUAir,'f',3));
    settings.setValue("seveUDioxide",QString::number(seveUDioxide,'f',3));
    settings.setValue("seveUDioxide1",QString::number(seveUDioxide1,'f',3));
    settings.setValue("seveUDioxide2",QString::number(seveUDioxide2,'f',3));
    settings.setValue("seveUDioxide3",QString::number(seveUDioxide3,'f',3));

    settings.setValue("alarmPresInput",QString::number(alarmPresInput,'f',3));

    settings.setValue("deltaAlarmCO2",QString::number(deltaAlarmCO2,'f',3));
    settings.setValue("deltaAlarmO2",QString::number(deltaAlarmO2,'f',3));

    settings.setValue("coefficientO2",QString::number(coefficientO2,'f',3));
    settings.setValue("defaultO2",QString::number(defaultO2,'f',3));

    settings.endGroup();

 }


initDatOk=1;
}
//================================================================================
