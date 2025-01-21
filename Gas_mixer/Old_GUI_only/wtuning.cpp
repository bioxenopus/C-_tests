#include "wtuning.h"
//#include "mdef.h"

#define FSCALE 0.6
//==================================================================================================================
wtuning::wtuning(QWidget *parent, gmdata *d,objselgas *o, klapan *k) : QWidget(parent)
{
    obsg=o; gd=d; setKL=k; trigW=0;
    //setWindowModality(Qt::ApplicationModal);
    //QWidget::showFullScreen();


#ifdef RASPBERRY
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//+++ Disable TITLE Win ++++++
            this->setWindowState(Qt::WindowFullScreen);
            QDesktopWidget *scr = QApplication::desktop();
            scrWidth = 1024; //scr->width(); // ширина Экрана
            scrHeight = 600; //scr->height(); // высота экрана
            this->setGeometry(0,0,scrWidth,scrHeight);
 //       this->setStyleSheet("background-color: lightGray");
//           this->setStyleSheet("background-color: darkGray");
          this->setStyleSheet("background-color: gray");


#else
    //this->setGeometry(1280,50,16,9);

        //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//+++ Disable TITLE Win ++++++
        //this->setWindowState(Qt::WindowFullScreen);
        rect=this->geometry();
        // qDebug() << desktop->screenGeometry(0);
        // qDebug() << desktop->screenGeometry(1);
        // qDebug() << desktop->screenGeometry(2);
        scrWidth = rect.width(); // ширина Экрана
        scrHeight =rect.height(); // высота экрана
        // qDebug() << scrWidth;
        // qDebug() << scrHeight;
        //this->setGeometry(1280,50,scrWidth,scrHeight);
        //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//+++ Disable TITLE Win ++++++
        this->setStyleSheet("background-color: gray");
#endif
winRegim=0;
statText[0]="Установите значения %CO2 или %O2 и запустите режим настройки по соответствующему газу \n или режим калибровки O2        ";
statText[1]=" ПОДОЖДИТЕ Пожалуйста !!!!!!!";
statText[2]="Запустите режим настройки по соответствующему газу или вернитесь в первый экран";
statText[3]="Пожалуйста подождите. Идет настройка состава газовой смеси в соответствии с установленными параметрами.";
statText[4]="Настройка по соответствующему газу ЗАВЕРШЕНА. Вернитесь в первый экран.";
statText[5]="Запустите режим калибровки кислородного датчика или вернитесь в первый экран.";
statText[6]="Пожалуйста подождите около трех минут.";
statText[7]="Калибровка завершена. Вернитесь в первый экран.";

            prBX=this->height()/3*4/2-(this->width()/7/2);
            prBY=this->height()/7;
            leftX=this->width()/100;
    bo = new border(this,2,this->width(),this->height());
    bo->show();
    bo->setParent(this);
    connect(bo,SIGNAL(workEND(void)),this,SLOT(winExit(void)),Qt::DirectConnection);
    //connect(bo,SIGNAL(test(void)),this,SLOT(winTest(void)));
    //connect(bo,SIGNAL(startA(void)),this,SLOT(winStartA(void)));
    connect(bo,SIGNAL(settunCO2(int)),this,SLOT(winTunCO2(int)));
    connect(bo,SIGNAL(settunO2(int)),this,SLOT(winTunO2(int)));
    connect(bo,SIGNAL(calibrO2(int)),this,SLOT(winCalibrO2(int)));
    connect(bo,SIGNAL(opclKl4(int)),this,SLOT(winKl4(int)));


    // qDebug() << desktop->screenGeometry(1);

//    void calibrO2(int);

//-------------------------------------------------
           winInit();
//-------------------------------------------------

           setKL->setKlap(0,1);

           coefficientO2=gd->u_d.coefficientO2;
           defaultO2=gd->u_d.defaultO2;
           ptimer = new QTimer(this);
           ptimer->stop();
           connect(ptimer, SIGNAL(timeout()),this,SLOT(slotPtim()));
           aa=QString::number(gd->u_d.percentDioxide,'f',2);
           linECO2D->setValue(gd->u_d.percentDioxide);
           aa=QString::number(gd->u_d.percentAir,'f',2);
           linEO2D->setValue(gd->u_d.percentAir);
           aa=QString::number(gd->u_d.setpointFull,'f',2);

           ptimer->start(300);


}
//========================================================================================================================
void  wtuning::winStartA(void)
{
    // qDebug() <<"+++++++ START wtuning_clicked +++++++++";


}
//========================================================================================================================
void wtuning::winCalibrO2(int arg)
{
  winKl4(1);  // qDebug() <<"+++++++ START winCalibrO2 +++++++++";
 if(arg==1)
    {
     setKL->setKlap(0,0);

     bo->pb4->hide();
    trigW=1;winRegim=31;
    coefficientO2=gd->u_d.coefficientO2;
    defaultO2=gd->u_d.defaultO2;

    linECO2D->hide();
    linEO2D->hide();
    labCO2->hide();
    labO2->hide();
    aa="Коэффициент O2     ";
    labNF->setText(aa);

    labNFR->hide();labNFDR->hide();
    labCo2F->hide(); labCo2FD->hide(); labCo2FR->hide();labCo2FDR->hide();
    labO2F->hide();; labO2FD->hide();; labO2FR->hide(); labO2FDR->hide();
    obsg->startMesu();
    labStatD->setText(statText[5]);
    }
 else if(arg==0)
    {
     bo->pb5->hide();
    trigW=1;winRegim=32;
    coefficientO2=gd->u_d.coefficientO2;
    defaultO2=gd->u_d.defaultO2;

    linECO2D->hide();
    linEO2D->hide();
    labCO2->hide();
    labO2->hide();
    aa="Коэффициент O2     ";
    labNF->setText(aa);

    labNFR->hide();labNFDR->hide();
    labCo2F->hide(); labCo2FD->hide(); labCo2FR->hide();labCo2FDR->hide();
    labO2F->hide();; labO2FD->hide();; labO2FR->hide(); labO2FDR->hide();
    obsg->startMesu();
    labStatD->setText(statText[6]);
    }
}
//========================================================================================================================
void wtuning::winTunCO2(int a)
{
    linECO2D->setDisabled(true);
    linEO2D->setDisabled(true);
    ;
    float dum;
if(a==1)
    {
    trigW=1; winRegim=11;//pptim()
    obsg->fullText=QString::number(gd->u_d.setpointFull,'f',2);
    dum=linECO2D->value();
    obsg->CO2setText=QString::number(dum);
    dum=linEO2D->value();
    obsg->AirsetText=QString::number(dum);
    obsg->O2setText=QString::number(dum);
    obsg->trigSt=1;obsg->trigStopAuto=0;
    obsg->on_SA(1);
    }
else if(a==0)
    {
    trigW=1; winRegim=12;//pptim()
    obsg->fullText=QString::number(gd->u_d.setpointFull,'f',2);
    dum=linECO2D->value();
    obsg->CO2setText=QString::number(dum);
    dum=linEO2D->value();
    obsg->AirsetText=QString::number(dum);
    obsg->O2setText=QString::number(dum);
    obsg->trigSt=0;obsg->trigStopAuto=0;
    obsg->on_SA(1);
    labStatD->setText(statText[3]);

    }
}
//========================================================================================================================
void wtuning::winTunO2(int a)
{
    linECO2D->setDisabled(true);
    linEO2D->setDisabled(true);
    float dum;
if(a==1)
    {
    trigW=1;winRegim=21;
    obsg->fullText=QString::number(gd->u_d.setpointFull,'f',2);
    dum=linECO2D->value();
    obsg->CO2setText=QString::number(dum);
    dum=linEO2D->value();
    obsg->AirsetText=QString::number(dum);
    obsg->O2setText=QString::number(dum);
    obsg->trigSt=1;obsg->trigStopAuto=0;
    obsg->on_SA(2);
    }
else if(a==0)
    {
    trigW=1;winRegim=22;
    obsg->fullText=QString::number(gd->u_d.setpointFull,'f',2);
    dum=linECO2D->value();
    obsg->CO2setText=QString::number(dum);
    dum=linEO2D->value();
    obsg->AirsetText=QString::number(dum);
    obsg->O2setText=QString::number(dum);
    obsg->trigSt=0;obsg->trigStopAuto=0;
    obsg->on_SA(2);
    labStatD->setText(statText[3]);
    }

}
//========================================================================================================================
void wtuning::slotPtim()
{
ptimer->stop();
if(winRegim==0)
 {
    aa=QString::number(obsg->receiverP,'f',2);
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    aa=QString::number(gd->u_d.setpointNitrogen,'f',2);
    labNFD->setText(aa);
    aa=QString::number(gd->u_d.setpointDioxide,'f',2);
    labCo2FD->setText(aa);
    aa=QString::number(gd->u_d.setpointAir,'f',2);
    labO2FD->setText(aa);
 }
else if(winRegim==11)
 {
    aa=QString::number(obsg->receiverP,'f',2);/// Дублирование
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    aa=QString::number(obsg->setpointNitrogen,'f',2);
    labNFD->setText(aa);
    aa=QString::number(obsg->setpointDioxide,'f',2);
    labCo2FD->setText(aa);
    aa=QString::number(obsg->setpointAir,'f',2);
    labO2FD->setText(aa);///// Конец дублирования
    if(obsg->regStatusAuto != 0){labStatD->setText(statText[1]);}
    else
    {
        labStatD->setText(statText[2]);bo->pb2->show();
        labCO2R->show();
        labCO2RD->show();

        labPT->show();
        labPTD->show();
        aa=QString::number(obsg->setpointDioxide,'f',2);
        labCo2FD->setText(aa);
        aa=QString::number(obsg->setpointAir,'f',2);
        labO2FD->setText(aa);

        aa=QString::number(obsg->receiverP,'f',2);
        labRePD->setText(aa);
        if(obsg->flowNitrogen > 5.0)
        {
        aa=QString::number(obsg->flowNitrogen,'f',2);
        labNFDR->setText(aa);
        }
        else
        {
            aa="0.00";
            labNFDR->setText(aa);
        }
        if(obsg->flowDioxide > 5.0)
        {
        aa=QString::number(obsg->flowDioxide,'f',2);
        labCo2FDR->setText(aa);
        }
        else
        {
            aa="0.00";
            labCo2FDR->setText(aa);
        }
        if(obsg->flowAir > 5.0)
        {
        aa=QString::number(obsg->flowAir,'f',2);
        labO2FDR->setText(aa);
        }
        else
        {
            aa="0.00";
            labO2FDR->setText(aa);
        }
        aa=QString::number(obsg->O2_p,'f',2);
       labO2MD->setText(aa);
       aa=QString::number(obsg->CO2_p,'f',2);
       labCO2MD->setText(aa);
       aa=QString::number(obsg->CO2_Cor,'f',2);
       labCO2RD->setText(aa);
       aa=QString::number(obsg->PresInit,'f',2);
       labPTD->setText(aa);

    }
}

else if(winRegim==12)
 {
    aa=QString::number(obsg->receiverP,'f',2);
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    if(obsg->flowNitrogen > 5.0)
    {
    aa=QString::number(obsg->flowNitrogen,'f',2);
    labNFDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labNFDR->setText(aa);
    }
    if(obsg->flowDioxide > 5.0)
    {
    aa=QString::number(obsg->flowDioxide,'f',2);
    labCo2FDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labCo2FDR->setText(aa);
    }
    if(obsg->flowAir > 5.0)
    {
    aa=QString::number(obsg->flowAir,'f',2);
    labO2FDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labO2FDR->setText(aa);
    }
    aa=QString::number(obsg->O2_p,'f',2);
   labO2MD->setText(aa);
   aa=QString::number(obsg->CO2_p,'f',2);
   labCO2MD->setText(aa);
   aa=QString::number(obsg->CO2_Cor,'f',2);
   labCO2RD->setText(aa);
   aa=QString::number(obsg->PresInit,'f',2);
   labPTD->setText(aa);

   if((obsg->regStatusAuto==0) && (obsg->workOK==0) && (obsg->regStatusAuto==0) && (obsg->startA==0))
   {labStatD->setText(statText[4]);}
 }
else if(winRegim==21)
 {
    aa=QString::number(obsg->receiverP,'f',2);
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    if(obsg->flowNitrogen > 5.0)
    {
    aa=QString::number(obsg->flowNitrogen,'f',2);
    labNFDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labNFDR->setText(aa);
    }
    if(obsg->flowDioxide > 5.0)
    {
    aa=QString::number(obsg->flowDioxide,'f',2);
    labCo2FDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labCo2FDR->setText(aa);
    }
    if(obsg->flowAir > 5.0)
    {
    aa=QString::number(obsg->flowAir,'f',2);
    labO2FDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labO2FDR->setText(aa);
    }
    if(obsg->regStatusAuto != 0){labStatD->setText(statText[1]);}
    else
    {
        labStatD->setText(statText[2]);bo->pb3->show();
        labO2R->show();
        labO2RD->show();

        labPT->show();
        labPTD->show();
        aa=QString::number(obsg->setpointDioxide,'f',2);
        labCo2FD->setText(aa);
        aa=QString::number(obsg->setpointAir,'f',2);
        labO2FD->setText(aa);
        aa=QString::number(obsg->setpointNitrogen,'f',2);
        labNFD->setText(aa);

        aa=QString::number(obsg->receiverP,'f',2);
        labRePD->setText(aa);

        if(obsg->flowNitrogen > 5.0)
        {
        aa=QString::number(obsg->flowNitrogen,'f',2);
        labNFDR->setText(aa);
        }
        else
        {
            aa="0.00";
            labNFDR->setText(aa);
        }
        if(obsg->flowDioxide > 5.0)
        {
        aa=QString::number(obsg->flowDioxide,'f',2);
        labCo2FDR->setText(aa);
        }
        else
        {
            aa="0.00";
            labCo2FDR->setText(aa);
        }
        if(obsg->flowAir > 5.0)
        {
        aa=QString::number(obsg->flowAir,'f',2);
        labO2FDR->setText(aa);
        }
        else
        {
            aa="0.00";
            labO2FDR->setText(aa);
        }
        aa=QString::number(obsg->O2_p,'f',2);
       labO2MD->setText(aa);
       aa=QString::number(obsg->CO2_p,'f',2);
       labCO2MD->setText(aa);
       aa=QString::number(obsg->O2_Cor,'f',2);
       labO2RD->setText(aa);
       aa=QString::number(obsg->PresInit,'f',2);
       labPTD->setText(aa);
    }
}
else if(winRegim==22)
 {
    aa=QString::number(obsg->receiverP,'f',2);
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    aa=QString::number(obsg->flowNitrogen,'f',2);
    if(obsg->flowNitrogen > 5.0)
    {
    aa=QString::number(obsg->flowNitrogen,'f',2);
    labNFDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labNFDR->setText(aa);
    }
    if(obsg->flowDioxide > 5.0)
    {
    aa=QString::number(obsg->flowDioxide,'f',2);
    labCo2FDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labCo2FDR->setText(aa);
    }
    if(obsg->flowAir > 5.0)
    {
    aa=QString::number(obsg->flowAir,'f',2);
    labO2FDR->setText(aa);
    }
    else
    {
        aa="0.00";
        labO2FDR->setText(aa);
    }
    aa=QString::number(obsg->O2_p,'f',2);
   labO2MD->setText(aa);
   aa=QString::number(obsg->CO2_p,'f',2);
   labCO2MD->setText(aa);
   aa=QString::number(obsg->O2_Cor,'f',2);
   labO2RD->setText(aa);
   aa=QString::number(obsg->PresInit,'f',2);
   labPTD->setText(aa);
   if((obsg->regStatusAuto==0) && (obsg->workOK==0) && (obsg->regStatusAuto==0) && (obsg->startA==0))
   {labStatD->setText(statText[4]);}

 }
else if(winRegim==31)
 {
    obsg->startMesu();
    aa=QString::number(obsg->receiverP,'f',2);
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    aa=QString::number(obsg->O2_p,'f',2);
   labO2MD->setText(aa);
   aa=QString::number(obsg->CO2_p,'f',2);
   labCO2MD->setText(aa);
   aa=QString::number(coefficientO2,'f',3);
   labNFD->setText(aa);
countColibr=0;

 }
else if(winRegim==32)
 {
    countColibr++;
    if(countColibr<600)
    {
    coefficientO2=defaultO2/obsg->O2_p;
    obsg->startMesu();
    aa=QString::number(obsg->receiverP,'f',2);
    labRePD->setStyleSheet("color: rgb(255,255,255)");
    labRePD->setText(aa);
    aa=QString::number(obsg->O2_p,'f',2);
   labO2MD->setText(aa);
   aa=QString::number(obsg->CO2_p,'f',2);
   labCO2MD->setText(aa);
   aa=QString::number(coefficientO2,'f',3);
   labNFD->setText(aa);
    }
    else
    {
        {labStatD->setText(statText[7]);}

    }

 }
ptimer->start(300);

}
//========================================================================================================================
void wtuning::winKl4(int ve)
{
    // qDebug() << "winKl4___1="<<ve;
    if(ve){setKL->setKlap(4,1);}
    else {setKL->setKlap(4,0);};
    // qDebug() << "winKl4="<<ve;

}
//========================================================================================================================
void wtuning::winInit()
{

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    labCO2 = new QLabel(this);
    labCO2->setWordWrap(true);
    labCO2->setAlignment(Qt::AlignCenter);
    labCO2->setText("<FONT COLOR=#ffffff>%CO2</FONT>");
    font = labCO2->font();
    font.setPointSize(50*FSCALE);
    font.setBold(true);
    labCO2->setFont(font);
    labCO2->adjustSize();
    labCO2->setGeometry(this->height()/3*4/4-labCO2->width()/2,this->height()/100,
                        labCO2->width(),labCO2->height());
    labCO2->show();

    linECO2D = new QDoubleSpinBox(this);
    linECO2D->setDecimals(1);
    linECO2D->setRange(0,12);
    linECO2D->setSingleStep(0.1);
    linECO2D->setStyleSheet("QDoubleSpinBox::down-button { width: 140px; height: 50px;} "
             "QDoubleSpinBox::up-button { width: 140px; height: 50px;}"
             "QDoubleSpinBox {color: black; background-color: yellow; border-style: inset; border: 3px solid darkGray;}");
    linECO2D->setAlignment(Qt::AlignLeft);
    font = linECO2D->font();
    font.setPointSize(100*FSCALE);
    font.setBold(true);
    linECO2D->setFont(font);
    linECO2D->adjustSize();
    linECO2D->setValue(12.0);

    linECO2D->setGeometry(this->height()/3*4/4-(linECO2D->width()-linECO2D->width()/10)/2,this->height()/100+labCO2->height(),
                          linECO2D->width()-linECO2D->width()/10,linECO2D->height());
    linECO2D->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        labO2 = new QLabel(this);
        labO2->setWordWrap(true);
        labO2->setAlignment(Qt::AlignCenter);
        labO2->setText("<FONT COLOR=#ffffff>%O2</FONT>");
        font = labO2->font();
        font.setPointSize(50*FSCALE);
        font.setBold(true);
        labO2->setFont(font);
        labO2->adjustSize();
        //lw=labCO2->width();
        labO2->setGeometry(this->height()/3*4/4*3-labO2->width()/2,this->height()/100,
                            labO2->width(),labO2->height());
        labO2->show();

        linEO2D = new QDoubleSpinBox(this);
        linEO2D->setDecimals(1);
        linEO2D->setRange(0,12);
        linEO2D->setSingleStep(0.1);
        linEO2D->setStyleSheet("QDoubleSpinBox::down-button {width: 140px; height: 50px;} "
                "QDoubleSpinBox::up-button {width: 140px; height: 50px;}"
                "QDoubleSpinBox {color: black; background-color: yellow; border-style: inset; border: 3px solid darkGray;}");
        linEO2D->setAlignment(Qt::AlignLeft);
        font = linEO2D->font();
        font.setPointSize(100*FSCALE);
        font.setBold(true);
        linEO2D->setFont(font);
        linEO2D->adjustSize();
        linEO2D->setGeometry(this->height()/3*4/4*3-(linEO2D->width()-linEO2D->width()/10)/2,
                             this->height()/100+labO2->height(),
                             linEO2D->width()-linEO2D->width()/10,linEO2D->height());
        linEO2D->setValue(12.0);
        linEO2D->show();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                     labStat = new QLabel(this);
                     labStat->setWordWrap(true);
                     labStat->setAlignment(Qt::AlignCenter);
                     labStat->setText("<FONT COLOR=#ffffff>Статус программы </FONT>");
                     font = labStat->font();
                     font.setPointSize(20*FSCALE);
                     font.setBold(true);
                     labStat->setFont(font);
                     labStat->adjustSize();
                     labStat->setGeometry(leftX,
                                         this->height()/100+labO2->height()+linEO2D->height()+prBY/2,
                                         labStat->width(),labStat->height());
                     labStat->show();

                     labStatD = new QLabel(this);
                     labStatD->setStyleSheet("background-color: green");
                     labStatD->setWordWrap(true);
                     labStatD->setAlignment(Qt::AlignLeft);
                     labStatD->setText(statText[0]);
                     font = labStatD->font();
                     font.setPointSize(20*FSCALE);
                     font.setBold(true);
                     labStatD->setFont(font);
                     labStatD->adjustSize();
                     labStatD->setGeometry(leftX+labStat->width(),
                                        this->height()/100+labO2->height()+linEO2D->height()+prBY/2,
                                         labStatD->width(),labStatD->height());
                     labStatD->show();




//!!!!!!!!!!!!!!!!!!!!!!!!!!!   ПОТОКИ  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            aa="N2-Расчетный поток     ";
            labNF = new QLabel(this);
            labNF->setStyleSheet("color: rgb(255,255,255);");
            labNF->setAlignment(Qt::AlignRight);
            labNF->setText(aa);
            font = labNF->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labNF->setFont(font);
            //lw=labCO2->width();
            labNF->adjustSize();
            labNF->setGeometry(leftX,
                               prBY+this->height()/2,labNF->width(),labNF->height());
            labNF->show();


            labNFD = new QLabel(this);
            labNFD->setAlignment(Qt::AlignLeft);
            labNFD->setStyleSheet("background-color: rgb(255,255,255);");
            labNFD->setText("<FONT COLOR=#000000>0000.00</FONT>");
            font = labNFD->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labNFD->setFont(font);
            labNFD->adjustSize();
            labNFD->setGeometry(leftX+labNF->width(),
                                prBY+this->height()/2,
                                labNFD->width(),labNFD->height());
            labNFD->show();
//================
            aa="N2-Измеренный поток     ";
            labNFR = new QLabel(this);
            labNFR->setStyleSheet("color: rgb(255,255,255);");
            labNFR->setAlignment(Qt::AlignRight);
            labNFR->setText(aa);
            font = labNFR->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labNFR->setFont(font);
            labNFR->adjustSize();
            labNFR->setGeometry(leftX/2+leftX+labNF->width()+labNFD->width(),
                                prBY+this->height()/2,
                                labNFR->width(),labNFR->height());
            labNFR->show();


            labNFDR = new QLabel(this);
            labNFDR->setAlignment(Qt::AlignLeft);
            labNFDR->setStyleSheet("background-color: rgb(255,255,255);");
            labNFDR->setText("<FONT COLOR=#000000>0000.00</FONT>");
            font = labNFDR->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labNFDR->setFont(font);
            labNFDR->adjustSize();
            labNFDR->setGeometry(leftX/2+leftX+labNFR->width()+labNFD->width()+labNF->width(),
                                 prBY+this->height()/2,
                                labNFDR->width(),labNFDR->height());
            labNFDR->show();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            aa="CO2-Расчетный поток  ";
            labCo2F = new QLabel(this);
            labCo2F->setStyleSheet("color: rgb(255,255,255);");
            labCo2F->setAlignment(Qt::AlignRight);
            labCo2F->setText(aa);
            font = labCo2F->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labCo2F->setFont(font);
            labCo2F->adjustSize();
            labCo2F->setGeometry(leftX,
                                 prBY+this->height()/2+labNF->height(),
                                 labCo2F->width(),labCo2F->height());
            labCo2F->show();

            labCo2FD = new QLabel(this);
            labCo2FD->setAlignment(Qt::AlignLeft);
            labCo2FD->setStyleSheet("background-color: rgb(255,255,255);");
            labCo2FD->setText("<FONT COLOR=#000000>0000.00</FONT>");
            font = labCo2FD->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labCo2FD->setFont(font);
            labCo2FD->adjustSize();
            labCo2FD->setGeometry(leftX+labNF->width(),
                                  prBY+this->height()/2+labNF->height(),
                                  labCo2FD->width(),labCo2FD->height());
            labCo2FD->show();

            aa="CO2-Измеренный поток  ";
            labCo2FR = new QLabel(this);
            labCo2FR->setStyleSheet("color: rgb(255,255,255);");
            labCo2FR->setAlignment(Qt::AlignRight);
            labCo2FR->setText(aa);
            font = labCo2FR->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labCo2FR->setFont(font);
            labCo2FR->adjustSize();
            labCo2FR->setGeometry(leftX/2+leftX+labNF->width()+labNFD->width(),
                                  prBY+this->height()/2+labNF->height(),
                                 labCo2FR->width(),labCo2FR->height());
            labCo2FR->show();

            labCo2FDR = new QLabel(this);
            labCo2FDR->setAlignment(Qt::AlignLeft);
            labCo2FDR->setStyleSheet("background-color: rgb(255,255,255);");
            labCo2FDR->setText("<FONT COLOR=#000000>0000.00</FONT>");
            font = labCo2FDR->font();
            font.setPointSize(18*FSCALE);
            font.setBold(true);
            labCo2FDR->setFont(font);
            labCo2FDR->adjustSize();
            labCo2FDR->setGeometry(leftX/2+leftX+labNFR->width()+labNFD->width()+labNF->width(),
                                  prBY+this->height()/2+labNF->height(),
                                  labCo2FDR->width(),labCo2FDR->height());
            labCo2FDR->show();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!QLabel!!!!
            aa="O2-Расчетный поток     ";
             labO2F = new QLabel(this);
             labO2F->setStyleSheet("color: rgb(255,255,255);");
             labO2F->setAlignment(Qt::AlignRight);
             labO2F->setText(aa);
             font = labO2F->font();
             font.setPointSize(18*FSCALE);
             font.setBold(true);
             labO2F->setFont(font);
             labO2F->adjustSize();
             labO2F->setGeometry(leftX,
                                 prBY+this->height()/2+labNF->height()+labCo2FD->height(),
                                 labO2F->width(),labO2F->height());
             labO2F->show();


             labO2FD = new QLabel(this);
             labO2FD->setAlignment(Qt::AlignLeft);
             labO2FD->setStyleSheet("background-color: rgb(255,255,255);");
             labO2FD->setText("<FONT COLOR=#000000>0000.00</FONT>");
             font = labO2FD->font();
             font.setPointSize(18*FSCALE);
             font.setBold(true);
             labO2FD->setFont(font);
             labO2FD->adjustSize();
             labO2FD->setGeometry(leftX+labNF->width(),
                                  prBY+this->height()/2+labNF->height()+labCo2FD->height(),
                                 labO2FD->width(),labO2FD->height());
             labO2FD->show();

             aa="O2-Измеренный поток     ";
              labO2FR = new QLabel(this);
              labO2FR->setStyleSheet("color: rgb(255,255,255);");
              labO2FR->setAlignment(Qt::AlignRight);
              labO2FR->setText(aa);
              font = labO2FR->font();
              font.setPointSize(18*FSCALE);
              font.setBold(true);
              labO2FR->setFont(font);
              labO2FR->adjustSize();
              labO2FR->setGeometry(leftX/2+leftX+labO2F->width()+labO2FD->width(),
                                   prBY+this->height()/2+labNF->height()+labCo2FD->height(),
                                  labO2FR->width(),labO2FR->height());
              labO2FR->show();


              labO2FDR = new QLabel(this);
              labO2FDR->setStyleSheet("background-color: rgb(255,255,255);");
              labO2FDR->setAlignment(Qt::AlignLeft);
              labO2FDR->setText("<FONT COLOR=#000000>0000.00</FONT>");
              font = labO2FDR->font();
              font.setPointSize(18*FSCALE);
              font.setBold(true);
              labO2FDR->setFont(font);
              labO2FDR->adjustSize();
              labO2FDR->setGeometry(leftX/2+leftX+labNFR->width()+labNFD->width()+labNF->width(),
                                   prBY+this->height()/2+labNF->height()+labCo2FD->height(),
                                  labO2FDR->width(),labO2FDR->height());
              labO2FDR->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
              aa="O2-Измеренное значение ";
               labO2M = new QLabel(this);
               labO2M->setStyleSheet("color: rgb(255,255,255);");
               labO2M->setAlignment(Qt::AlignLeft);
               labO2M->setText(aa);
               font = labO2M->font();
               font.setPointSize(18*FSCALE);
               font.setBold(true);
               labO2M->setFont(font);
               labO2M->adjustSize();
               labO2M->setGeometry(leftX,
                                   prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2,
                                   labO2M->width(),labO2M->height());
               labO2M->show();


               labO2MD = new QLabel(this);
               labO2MD->setStyleSheet("background-color: rgb(255,255,255);");
               labO2MD->setAlignment(Qt::AlignLeft);
               labO2MD->setText("<FONT COLOR=#000000>00.00</FONT>");
               font = labO2MD->font();
               font.setPointSize(18*FSCALE);
               font.setBold(true);
               labO2MD->setFont(font);
               labO2MD->adjustSize();
               labO2MD->setGeometry(leftX+labO2M->width(),
                                    prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2MD->height()*2,
                                   labO2MD->width(),labO2MD->height());
               labO2MD->show();


               aa="CO2-Измеренное значение ";
                labCO2M = new QLabel(this);
                labCO2M->setStyleSheet("color: rgb(255,255,255);");
                labCO2M->setAlignment(Qt::AlignLeft);
               labCO2M->setText(aa);
                font = labCO2M->font();
                font.setPointSize(18*FSCALE);
                font.setBold(true);
                labCO2M->setFont(font);
                labCO2M->adjustSize();
                labCO2M->setGeometry(2*leftX+labO2MD->width()+labO2M->width(),
                                    prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2,
                                    labCO2M->width(),labCO2M->height());
                labCO2M->show();


                labCO2MD = new QLabel(this);
                labCO2MD->setStyleSheet("background-color: rgb(255,255,255);");
                labCO2MD->setAlignment(Qt::AlignLeft);
                labCO2MD->setText("<FONT COLOR=#000000>00.00</FONT>");
                font = labCO2MD->font();
                font.setPointSize(18*FSCALE);
                font.setBold(true);
                labCO2MD->setFont(font);
                labCO2MD->adjustSize();
                labCO2MD->setGeometry(2*leftX+labO2MD->width()+labO2M->width()+labCO2M->width(),
                                     prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2MD->height()*2,
                                    labCO2MD->width(),labCO2MD->height());
                labCO2MD->show();

//_____________________________________________________________
                aa="CO2-Скорректированное значение ";
                 labCO2R = new QLabel(this);
                 labCO2R->setStyleSheet("color: rgb(255,255,255);");
                 labCO2R->setAlignment(Qt::AlignLeft);
                labCO2R->setText(aa);
                 font = labCO2R->font();
                 font.setPointSize(18*FSCALE);
                 font.setBold(true);
                 labCO2R->setFont(font);
                 labCO2R->adjustSize();
                 labCO2R->setGeometry(leftX,
                 prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2+labCO2R->height(),
                                     labCO2R->width(),labCO2R->height());
                 labCO2R->hide();


                 labCO2RD = new QLabel(this);
                 labCO2RD->setStyleSheet("background-color: rgb(255,255,255);");
                 labCO2RD->setAlignment(Qt::AlignLeft);
                 labCO2RD->setText("<FONT COLOR=#000000>00.00</FONT>");
                 font = labCO2RD->font();
                 font.setPointSize(18*FSCALE);
                 font.setBold(true);
                 labCO2RD->setFont(font);
                 labCO2RD->adjustSize();
                 labCO2RD->setGeometry(2*leftX+labCO2R->width(),
                 prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2+labCO2R->height(),
                                     labCO2RD->width(),labCO2RD->height());
                 labCO2RD->hide();
//_____________________________________________________________
                 aa="O2-Скорректированное значение ";
                  labO2R = new QLabel(this);
                  labO2R->setStyleSheet("color: rgb(255,255,255);");
                  labO2R->setAlignment(Qt::AlignLeft);
                  labO2R->setText(aa);
                  font = labO2R->font();
                  font.setPointSize(18*FSCALE);
                  font.setBold(true);
                  labO2R->setFont(font);
                  labO2R->adjustSize();
                  labO2R->setGeometry(leftX,
                  prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2+labCO2R->height(),
                                      labO2R->width(),labO2R->height());
                  labO2R->hide();


                  labO2RD = new QLabel(this);
                  labO2RD->setStyleSheet("background-color: rgb(255,255,255);");
                  labO2RD->setAlignment(Qt::AlignLeft);
                  labO2RD->setText("<FONT COLOR=#000000>00.00</FONT>");
                  font = labO2RD->font();
                  font.setPointSize(18*FSCALE);
                  font.setBold(true);
                  labO2RD->setFont(font);
                  labO2RD->adjustSize();
                  labO2RD->setGeometry(2*leftX+labCO2R->width(),
                  prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2+labCO2R->height(),
                                      labO2RD->width(),labO2RD->height());
                  labO2RD->hide();
//_____________________________________________________________
        aa="Уменьшить давление до ";
        labPT = new QLabel(this);
        labPT->setStyleSheet("color: rgb(255,255,255);");
        labPT->setAlignment(Qt::AlignLeft);
        labPT->setText(aa);
        font = labPT->font();
        font.setPointSize(18*FSCALE);
        font.setBold(true);
        labPT->setFont(font);
        labPT->adjustSize();
        labPT->setGeometry(leftX,
        prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2+labCO2R->height()+labPT->height(),
                         labPT->width(),labPT->height());
                 labPT->hide();


         labPTD = new QLabel(this);
         labPTD->setStyleSheet("background-color: rgb(255,255,255);");
         labPTD->setAlignment(Qt::AlignLeft);
         labPTD->setText("<FONT COLOR=#000000>00.00</FONT>");
         font = labPTD->font();
         font.setPointSize(18*FSCALE);
         font.setBold(true);
         labPTD->setFont(font);
         labPTD->adjustSize();
         labPTD->setGeometry(2*leftX+labCO2R->width(),
         prBY+this->height()/2+labNF->height()+labCo2FD->height()+labO2M->height()*2+labCO2R->height()+labPTD->height(),
                           labPTD->width(),labPTD->height());
                 labPTD->hide();
//_____________________________________________________________
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
             labReP = new QLabel(this);
             labReP->setAlignment(Qt::AlignCenter);
             labReP->setText("<FONT COLOR=#ffffff>Давление в РЕСИВЕРЕ </FONT>");
             font = labReP->font();
             font.setPointSize(20*FSCALE);
             font.setBold(true);
             labReP->setFont(font);
             labReP->adjustSize();
             labReP->setGeometry(this->height()/3*4/2-labReP->width(),
                                 prBY+this->height()/2-labReP->height(),
                                 labReP->width(),labReP->height());
             labReP->show();

             labRePD = new QLabel(this);
             labRePD->setWordWrap(true);
             labRePD->setAlignment(Qt::AlignCenter);
             labRePD->setText("<FONT COLOR=#ffffff>000000.00</FONT>");
             font = labRePD->font();
             font.setPointSize(20*FSCALE);
             font.setBold(true);
             labRePD->setFont(font);
             labRePD->adjustSize();
             labRePD->setGeometry(this->height()/3*4/2-labReP->width()+labReP->width(),
                                 prBY+this->height()/2-labRePD->height(),
                                 labRePD->width(),labRePD->height());
             labRePD->show();



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


}

//========================================================================================================================

void wtuning::winTe()
{
     // qDebug() <<"+++++++ Function WINTEST +++++++++";

}

//========================================================================================================================
void wtuning::winExit()
{
if(ptimer->isActive()) {ptimer->stop();}
obsg->on_Can();
    // qDebug() <<"+++++++ wtuning_clicked +++++++++";
    winKl4(0);
//____________________________
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("ПРЕДУПРЕЖДЕНИЕ");
            msgBox->setStyleSheet("background-color: white");
            font = msgBox->font();
            font.setPointSize(40*FSCALE);
            font.setBold(true);
            msgBox->setFont(font);
            msgBox->setText("Внимание!");
            msgBox->setInformativeText("Ок - ЗАПИСАТЬ ДАННЫЕ\nCancel - ВЫЙТИ БЕЗ ЗАПИСИ");
            msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox->button(QMessageBox::Ok)->setStyleSheet("padding: 40px;background-color: rgb(255,255, 0)");
            msgBox->button(QMessageBox::Cancel)->setStyleSheet("padding: 40px; background-color: rgb(255,255, 0)");
            msgBox->setIcon(QMessageBox::Information);
            msgBox->setDefaultButton(QMessageBox::Ok);
            msgBox->setGeometry(msgBox->width()/2,
                               msgBox->height()/2,
                                msgBox->width(),msgBox->height());

            int res = msgBox->exec();
//_______________________________

            if (res == QMessageBox::Ok)
            {
                float dum1;float dum2;float full;

                full=gd->u_d.setpointFull;

                dum1=linECO2D->value();
                dum2=linEO2D->value();


                gd->u_d.coefficientO2=coefficientO2;

                inper = new initPer(this,gd);
                inper->writeDat(full,dum1,dum2);
                delete inper;
            }


    delete ptimer;
    emit workRestart(7);

    this->close();
    this->deleteLater();
}
//========================================================================================================================
void wtuning::on_checkBox_cb1(int arg1)

{
// qDebug() << "44444444444444444444444444="<<arg1;
//cb2->setCheckState(Qt::Checked);
if(arg1==0)
 {
  cb2->setCheckState(Qt::Checked);
  cb1->setCheckState(Qt::Unchecked);
  linEO2D->setSingleStep(0.1);
  linECO2D->setSingleStep(0.1);

 }
else if(arg1==2)
 {
    cb2->setCheckState(Qt::Unchecked);
    cb1->setCheckState(Qt::Checked);
    linEO2D->setSingleStep(1.0);
    linECO2D->setSingleStep(1.0);

 }

}
//========================================================================================================================
void wtuning::on_checkBox_cb2(int arg2)

{
// qDebug() << "55555555555555555555555555555="<<arg2;
//cb2->setCheckState(Qt::Checked);
if(arg2==0)
 {
  cb2->setCheckState(Qt::Unchecked);
  cb1->setCheckState(Qt::Checked);
  linEO2D->setSingleStep(1.0);
  linECO2D->setSingleStep(1.0);
 }
else if(arg2==2)
 {
    cb2->setCheckState(Qt::Checked);
    cb1->setCheckState(Qt::Unchecked);
    linEO2D->setSingleStep(0.1);
    linECO2D->setSingleStep(0.1);

 }
}
//========================================================================================================================
void wtuning::winTest(void)
{
/*
    prBO->setValue(300);
    prB->setValue(1500);
    prIN->setValue(0);
    prIC->setValue(0);
    prIO->setValue(0);
    aa="ДАВЛЕНИЕ\nN=7.00";
    labNP->setText(aa);
    aa="ДАВЛЕНИЕ O2=9.0";
    labOP->setText(aa);

*/
}
//========================================================================================================================
