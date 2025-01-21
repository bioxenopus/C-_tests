#include <QErrorMessage>
#include "wnormwork.h"
//#include "mdef.h"

#define FSCALE 0.6

extern uint32_t adcD[20];
extern float adcU[20];
extern float adcR[20];

wnormwork::wnormwork(QWidget *parent,gmdata *d, klapan *k) : QWidget(parent)
{
  //  this->QWidget::showFullScreen();

setKL=k;
gd=d;
    trigErr=1;
    setWindowModality(Qt::ApplicationModal);
//this->showMaximized();
#ifdef RASPBERRY

        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//+++ Disable TITLE Win ++++++
            QDesktopWidget *scr = QApplication::desktop();
            scrWidth = 1024;//scr->width(); // ширина Экрана
            scrHeight = 600; //scr->height(); // высота экрана
            this->setGeometry(0,0,scrWidth,scrHeight);
        this->setStyleSheet("background-color: blue");

#else
        //QScreen* desktop = QApplication::screens().at(0);
        //this->setWindowState(Qt::WindowFullScreen);
        /*
        rect = desktop->geometry();
        move(rect.topLeft());


        // qDebug() << desktop->screenGeometry(0);
        // qDebug() << desktop->screenGeometry(1);
        // qDebug() << desktop->screenGeometry(2);
        scrWidth = rect.width(); // ширина Экрана
        scrHeight =rect.height(); // высота экрана
        // qDebug() << scrWidth;
        // qDebug() << scrHeight;
        this->setGeometry(1280,50,scrWidth,scrHeight+20);*/
        //this->showFullScreen();
        //this->QWidget::showFullScreen();
        //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//+++ Disable TITLE Win ++++++
        this->setStyleSheet("background-color: blue");
#endif

        setKL->setKlap(0,1);
        //qDebug() << "wnormwork : setKlap 0 1";



    bo = new border(this,1,this->width(),this->height());
    bo->show();
    connect(bo,SIGNAL(workEND(void)),this,SLOT(winExit(void)),Qt::DirectConnection);
    connect(bo,SIGNAL(test(void)),this,SLOT(winTest(void)));
    connect(bo,SIGNAL(opclKl3(int)),this,SLOT(winKl3(int)));

    //-------------------------------------------------

    prB = new QProgressBar(this);
    prB->setTextVisible(false);
    prB->setAlignment(Qt::AlignCenter);
    prB->setMinimum(0);
    prB->setMaximum(300);
    prB->setValue(0);


//    prB->setStyleSheet("QProgressBar {background-color: black; border: 2px solid grey; "
//                                   "border-radius: 5px;} QProgressBar::chunk {background-color: green;}");


//    prB->setStyleSheet("QProgressBar::chunk { background-color: green;}");
    prB->setStyleSheet("QProgressBar {background-color: black; border: 10px solid grey; border-radius: 50px;}"
                       "QProgressBar::chunk { background-color: "
                       "green;border-bottom-left-radius: 33px; border-bottom-right-radius: 33px;}");



    //                       "QProgressBar::chunk { background-color: green;border-top-left-radius: 23px; border-bottom-left-radius: 23px;}");

    palette = prB->palette();
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::HighlightedText, Qt::white);
    prB->setPalette(palette);

    prB->setOrientation(Qt::Vertical);
    prBX=this->height()/3*4/2-(this->width()/7/2);
    prBY=this->height()/12*5;
//    prB->setGeometry(this->height()/3*4/2-(this->width()/7/2),this->height()/3,
//                                     this->width()/7,this->height()/3*1.7);
    prB->setGeometry(prBX,prBY,this->width()/7,this->height()/3*1.7);
    prB->setValue(00);


//-------------------------------------------------

leftX=prB->width()+prB->width()/5;

//-------------------------------------------------

    prBO = new QProgressBar(this);
    prBO->setTextVisible(false);

    prBO->setAlignment(Qt::AlignCenter);
    prBO->setMinimum(0);
    prBO->setMaximum(2000);
    prBO->setValue(0);

    prBO->setStyleSheet("QProgressBar {background-color: black; border: 1px solid grey;}"
                        "QProgressBar::chunk {background-color: green;}");

   palette = prBO->palette();
   palette.setColor(QPalette::Text, Qt::white);
   palette.setColor(QPalette::HighlightedText, Qt::white);
   prBO->setPalette(palette);

   prBO->setOrientation(Qt::Vertical);
   prBO->setGeometry(prBX+prB->width(),prBY+prB->height()-prB->height()/8-prB->height()/10,
                     leftX,prB->height()/10);
//                     prB->width()*2,prB->height()/10);
    prBO->setValue(00);

//-------------------------------------------------

        prIN = new QProgressBar(this);
        prIN->setTextVisible(false);

        prIN->setAlignment(Qt::AlignCenter);
        prIN->setMinimum(0);
        prIN->setMaximum(2000);
        prIN->setValue(0);

        prIN->setStyleSheet("QProgressBar {background-color: black; border: 1px solid grey;}"
                            " QProgressBar::chunk {background-color: yellow;}");

       palette = prIN->palette();
       palette.setColor(QPalette::Text, Qt::white);
       palette.setColor(QPalette::HighlightedText, Qt::white);
       prIN->setPalette(palette);

       prIN->setOrientation(Qt::Vertical);
//       prIN->setGeometry(prBX-prB->width(),prBY+prB->height()/8,prB->width(),prB->height()/10);
       prIN->setGeometry(prBX-leftX,prBY+prB->height()/8,leftX,prB->height()/10);
       prIN->setValue(00);

//-------------------------------------------------

       prIC = new QProgressBar(this);
       prIC->setTextVisible(false);
       prIC->setAlignment(Qt::AlignCenter);
       prIC->setMinimum(0);
       prIC->setMaximum(200);
       prIC->setValue(0);

       prIC->setStyleSheet("QProgressBar {background-color: black;  border: 1px solid grey;}"
                           " QProgressBar::chunk {background-color: darkRed;}");

       palette = prIC->palette();
       palette.setColor(QPalette::Text, Qt::white);
       palette.setColor(QPalette::HighlightedText, Qt::white);
       prIC->setPalette(palette);

       prIC->setOrientation(Qt::Vertical);
       prIC->setGeometry(prBX-leftX,prBY+prB->height()/2-prB->height()/10/2,leftX,prB->height()/10);
       prIC->setValue(300);

//-------------------------------------------------

       prIO = new QProgressBar(this);
       prIO->setTextVisible(false);
       prIO->setAlignment(Qt::AlignCenter);
       prIO->setMinimum(0);
       prIO->setMaximum(1000);
       prIO->setValue(0);

       prIO->setStyleSheet("QProgressBar {background-color: black;  border: 1px solid grey;}"
                           " QProgressBar::chunk {background-color:  cyan;}");

       palette = prIO->palette();
       palette.setColor(QPalette::Text, Qt::white);
       palette.setColor(QPalette::HighlightedText, Qt::white);
       prIO->setPalette(palette);

       prIO->setOrientation(Qt::Vertical);
//       prIO->setGeometry(prBX-leftX,prBY+prB->height()-prB->height()/8-prB->height()/10,
       prIO->setGeometry(prBX-leftX,prBY+prB->height()-prB->height()/8-prB->height()/10,
                         leftX,prB->height()/10);
       prIO->setValue(00);
//-------------------------------------------------
       winInit();
//-------------------------------------------------
       timerMesB = new QTimer(this);
       timerMesB->stop();
       connect(timerMesB, SIGNAL(timeout()),this,SLOT(timMesB()));

       //____________________________

//       (new QErrorMessage(this))->showMessage("Write Error");
//       QErrorMessage errorMessage(this);
//       errorMessage.showMessage("Testing Error message");
//       errorMessage.exec();

//        errorMessage.show();


       //_______________________________

//       pptpTim = new QTimer(this);
//        connect(pptpTim, SIGNAL(timeout()),this,SLOT(slotpptpTim()));
//        pptpTim->start(30000);

       ptimer = new QTimer(this);
        connect(ptimer, SIGNAL(timeout()),this,SLOT(slotPtim()));
        ptimer->start(300);


}
//=============================================================================================
/*
void wnormwork::slotpptpTim(void)
{
 pptpTim->stop();
 pptpCoun++;
 if(pptpCoun >= 10)
  {
     pptpCoun=0;
     if((gd->statusR != SETPRESU) && (adcR[0] >= 2.5))
     {
         QNetworkAccessManager nam;
         QNetworkRequest req(QUrl("http://www.google.com"));
         QNetworkReply *reply = nam.get(req);
         QEventLoop loop;
         connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
         loop.exec();
         if(reply->bytesAvailable())
         {
             // qDebug() <<"+++++++ Internet YES +++++++++";
             int exitCode = QProcess::execute("ping", QStringList()
              << "-c" << "1"
              << "192.168.100.1");
             if (exitCode==0)
             {
                 // qDebug() <<"+++++++ VPN YES +++++++++";

             }
             else
             {
                 QProcess process1;
                  process1.startDetached("sudo poff vpn");
                  process1.startDetached("sudo pon vpn");
                  // qDebug() <<"+++++++ VPN NO +++++++++";

             }

         }
          else
         {
         // qDebug() <<"+++++++ Internet NO +++++++++";
         QProcess process;
          process.startDetached("sudo poff vpn");
         }
     }

 }



 pptpTim->start(30000);

}
*/
//=============================================================================================
void wnormwork::winKl3(int ve)
{
    if(ve){
        setKL->setKlap(1,1);
        //qDebug() << "wnormwork::winKl3 : setKlap(1,1)";
    }
    else {
        setKL->setKlap(1,0);
        //qDebug() << "wnormwork::winKl3 : setKlap(1,0)";
    }

}
//=============================================================================================
void wnormwork::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::white, 5));
//        painter.setPen(QPen(Qt::white, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(20,5,this->height()/3*4-20, 5);
    painter.drawLine(20,this->height()/4 ,this->height()/3*4-20 , this->height()/4);
    painter.drawLine(15,5,15, this->height()/4);
    painter.drawLine(this->height()/3*4-20,5,this->height()/3*4-20, this->height()/4);
    painter.drawLine(this->height()/3*4/2,5,this->height()/3*4/2, this->height()/4);
}
//==================================================================================================
void wnormwork::slotPtim()
{
ptimer->stop();



aa=QString::number(gd->CO2_p,'f',1);
labCO2D->setStyleSheet("color: rgb(255,255,255)");
labCO2D->setText(aa);
aa=QString::number(gd->O2_p,'f',1);
labO2D->setStyleSheet("color: rgb(255,255,255)");
labO2D->setText(aa);
aa=QString::number(gd->receiverP,'f',1);
labRePD->setStyleSheet("color: rgb(255,255,255)");
labRePD->setText(aa);
aa=QString::number(gd->u_d.percentDioxide,'f',1);
labSCO2D->setStyleSheet("color: rgb(255,255,255)");
labSCO2D->setText(aa);
aa=QString::number(gd->u_d.percentAir,'f',1);
labSO2D->setStyleSheet("color: rgb(255,255,255)");
labSO2D->setText(aa);
if(gd->flowNitrogen>5)
{

        aa=QString::number(gd->flowNitrogen,'f',1);
        labNFD->setStyleSheet("color: rgb(255,255,255)");
        labNFD->setText(aa);
}
else
{
    labNFD->setStyleSheet("color: rgb(255,255,255)");
    labNFD->setText("0.0");

}
if(gd->flowDioxide>5)
{

        aa=QString::number(gd->flowDioxide,'f',1);
        labCo2FD->setStyleSheet("color: rgb(255,255,255)");
        labCo2FD->setText(aa);
}
else
{
    labCo2FD->setStyleSheet("color: rgb(255,255,255)");
    labCo2FD->setText("0.0");

}
if(gd->flowAir>5)
{
        aa=QString::number(gd->flowAir,'f',1);
        labO2FD->setStyleSheet("color: rgb(255,255,255)");
        labO2FD->setText(aa);
//        prBO->setValue(gd->receiverP);
}
else {
    labO2FD->setStyleSheet("color: rgb(255,255,255)");
    labO2FD->setText("0.0");
    }

if(gd->ConsumptionOUT>5)
     {
      aa=QString::number(gd->ConsumptionOUT,'f',1);
      labGASD->setStyleSheet("color: rgb(255,255,255)");
      labGASD->setText(aa);
        //        prBO->setValue(gd->receiverP);
       }
else {
       labGASD->setStyleSheet("color: rgb(255,255,255)");
       labGASD->setText("0.0");
      }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    aa="N2\n  ";
    aa=aa+QString::number(gd->presN,'f',1);
 //   aa="N2\n3.0";
 //   labNP->setStyleSheet("background-color: lightGray");
//    labNP->setWordWrap(true);
//    labNP->setAlignment(Qt::AlignLeft);
    labNP->setText(aa);

    aa="CO2\n";
    aa=aa+" "+QString::number(gd->presC,'f',1);
//    aa="CO2\n4.0";
//    labCP->setStyleSheet("background-color:  lightGray");
    labCP->setWordWrap(true);
//    labCP->setAlignment(Qt::AlignLeft);
    labCP->setText(aa);

    aa="Воздух\n  ";
    aa=aa+QString::number(gd->presA,'f',1);
//    aa=aa+aa.sprintf("f.3f", gd->presA);
//    aa="Воздух\n5.0";
//    labOP->setStyleSheet("background-color: lightGray");
//    labNP->setWordWrap(true);
//    labOP->setAlignment(Qt::AlignLeft);
    labOP->setText(aa);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    aa="Смесь\n";
    aa=aa+QString::number(adcR[7],'f',1);
//         adcR[7]
 //   aa="Смесь\n1.8";
    labOutP->setText(aa);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//prB->setValue(gd->receiverP*100);
int set;
set=gd->receiverP*100;
//set=201;
if(set == 300)
{
prB->setStyleSheet("QProgressBar {background-color: black; border: 10px solid grey; border-radius: 50px;}"
                   "QProgressBar::chunk { background-color: "
                   "green;"
"border-bottom-left-radius: 33px; border-bottom-right-radius: 33px;"
"border-top-right-radius: 33px; border-top-left-radius: 33px;"
                   "}");
prB->setValue(set);
}
else if(set >= 275)
{
    prB->setStyleSheet("QProgressBar {background-color: black; border: 10px solid grey; border-radius: 50px;}"
                       "QProgressBar::chunk { background-color: "
                       "green;border-bottom-left-radius: 33px; border-bottom-right-radius: 33px;}");
    prB->setValue(275);

}
else if((set < 275) && (set >= 200))
{
    prB->setStyleSheet("QProgressBar {background-color: black; border: 10px solid grey; border-radius: 50px;}"
                       "QProgressBar::chunk { background-color: "
                       "green;border-bottom-left-radius: 33px; border-bottom-right-radius: 33px;}");
    prB->setValue(set);
}
else if((set < 200))
{
    prB->setStyleSheet("QProgressBar {background-color: black; border: 10px solid grey; border-radius: 50px;}"
                       "QProgressBar::chunk { background-color: "
                       "red;border-bottom-left-radius: 33px; border-bottom-right-radius: 33px;}");
    prB->setValue(set);
}

if(gd->flowNitrogen>10)
{
prIN->setValue(gd->flowNitrogen);
}
else
{
    prIN->setValue(0);
}

if(gd->flowDioxide>10)
{
prIC->setValue(gd->flowDioxide);
}
else
{
prIC->setValue(0);
}

if(gd->flowAir>5)
{
prIO->setValue(gd->flowAir);
}
else
{
 prIO->setValue(0);
}
if(gd->ConsumptionOUT>10)
{
prBO->setValue(gd->ConsumptionOUT);
}
else
{
    prBO->setValue(0);
}
/*
if(trigErr)
{
QMessageBox::about(this, "Title", "Text");
*/
/*
QErrorMessage errorMessage(this);
    errorMessage.showMessage("Testing Error message");

    QMessageBox msgBox(QMessageBox::Warning,
                       QString::fromUtf8("Предупреждение"),
                       QString::fromUtf8("Будьте осторожны..."),
                       0, this);
*/
/*
trigErr=0;
}
*/
ifErrr();
ptimer->start(300);
}
//========================================================================================================================
void wnormwork::ifErrr()
{
//    // qDebug() << "wnormwork::ifErrr"<<gd->errpresN<<gd->errpresA<<gd->errpresC;
trigAllErr=0;
    if(gd->errpresN==1)
    {
        labNP->setStyleSheet("background-color: red");
        trigAllErr=1;
    }
    else
    {
        labNP->setStyleSheet("background-color: lightGray");
    }
    if(gd->errpresC==1)
    {
        labCP->setStyleSheet("background-color: red");
        trigAllErr=1;
    }
    else
    {
        labCP->setStyleSheet("background-color: lightGray");
    }
    if(gd->errpresA==1)
    {
        labOP->setStyleSheet("background-color: red");
        trigAllErr=1;
    }
    else
    {
        labOP->setStyleSheet("background-color: lightGray");
    }
//    gd->errpO2=1;
    if(gd->errpCO2==1)
    {
        labCO2->setStyleSheet("color: red");
        aa="%CO2 ";
        labCO2->setText(aa);
    }
    else
    {
        labCO2->setStyleSheet("color: yellow");
        aa="%CO2 ";
        labCO2->setText(aa);
    }
    if(gd->errpO2==1)
    {
        labO2->setStyleSheet("color: red");
        aa="%O2 ";
        labO2->setText(aa);
    }
    else
    {
        labO2->setStyleSheet("color: yellow");
        aa="%O2 ";
        labO2->setText(aa);
    }
    if(trigAllErr==1){
        //qDebug() <<"+++++++ wnormwork.cpp : VO ALARM +++++++++";
        //system("aplay /home/pi/Gdata/Tada.mp3");
    }
}
//========================================================================================================================
void wnormwork::winInit()
{
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    labNFD = new QLabel(this);
    labNFD->setWordWrap(true);
    labNFD->setAlignment(Qt::AlignCenter);
    labNFD->setText("<FONT COLOR=#ffffff>14070.00</FONT>");
    font = labNFD->font();
    font.setPointSize(25*FSCALE);
    font.setBold(true);
    labNFD->setFont(font);
    labNFD->adjustSize();
    labNFD->setGeometry(prBX-leftX+leftX/2-labNFD->width()/2,
                        prBY+prB->height()/8-labNFD->height(),
                        labNFD->width(),labNFD->height());
    labNFD->show();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!QLabel!!!!
    labCo2FD = new QLabel(this);
    labCo2FD->setWordWrap(true);
    labCo2FD->setAlignment(Qt::AlignCenter);
    labCo2FD->setText("<FONT COLOR=#ffffff>12517.89</FONT>");
    font = labCo2FD->font();
    font.setPointSize(25*FSCALE);
    font.setBold(true);
    labCo2FD->setFont(font);
    labCo2FD->adjustSize();
    labCo2FD->setGeometry(prBX-leftX+leftX/2-labCo2FD->width()/2,
                          prBY+prB->height()/2-prB->height()/10/2-labCo2FD->height(),
                          labCo2FD->width(),labCo2FD->height());
    labCo2FD->show();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!QLabel!!!!

     labO2FD = new QLabel(this);
     labO2FD->setWordWrap(true);
     labO2FD->setAlignment(Qt::AlignCenter);
     labO2FD->setText("<FONT COLOR=#ffffff>1125.67</FONT>");
     font = labO2FD->font();
     font.setPointSize(25*FSCALE);
     font.setBold(true);
     labO2FD->setFont(font);
     labO2FD->adjustSize();
     labO2FD->setGeometry(prBX-leftX+leftX/2-labO2FD->width()/2,
                          prBY+prB->height()-prB->height()/8-prB->height()/10-labO2FD->height(),
                         labO2FD->width(),labO2FD->height());
     labO2FD->show();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!QLabel!!!!

     labGASD = new QLabel(this);
     labGASD->setAlignment(Qt::AlignCenter);
     labGASD->setText("<FONT COLOR=#ffffff>12598.08</FONT>");
     font = labGASD->font();
     font.setPointSize(25*FSCALE);
     font.setBold(true);
     labGASD->setFont(font);
     labGASD->adjustSize();
     labGASD->setGeometry(prBX+prB->width()+leftX/2-labGASD->width()/2,
                          prBY+prB->height()-prB->height()/8-prB->height()/10-labGASD->height(),
//                       prBY+prB->height()-prB->height()/8-prB->height()/10-labGAS->height()+labGAS->height()/2,
               labGASD->width(),labGASD->height());
     labGASD->show();


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
              aa="Воздух\n5.0";
               labOP = new QLabel(this);
               labOP->setStyleSheet("background-color: lightGray");
               labOP->setWordWrap(true);
               labOP->setAlignment(Qt::AlignCenter);
               labOP->setText(aa);
               font = labOP->font();
               font.setPointSize(20*FSCALE);
               font.setBold(true);
               labOP->setFont(font);
               labOP->adjustSize();
               labOP->setGeometry(prBX-leftX-labOP->width(),
                                  prBY+prB->height()-prB->height()/8-prB->height()/10-labOP->height()+prB->height()/10,
                                  labOP->width(),labOP->height());
               labOP->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     aa="N2\n0.0";
         labNP = new QLabel(this);
 //        labNP->setStyleSheet("background-color: yellow");
         labNP->setStyleSheet("background-color: lightGray");
         labNP->setWordWrap(true);
         labNP->setAlignment(Qt::AlignCenter);
         labNP->setText(aa);
         font = labNP->font();
         font.setPointSize(20*FSCALE);
         font.setBold(true);

         labNP->setFont(font);
         labNP->adjustSize();
         labNP->setGeometry(prBX-leftX-labOP->width(),
                            prBY+prB->height()/8-labOP->height()+prB->height()/10,
                            labOP->width(),labOP->height());
         labNP->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         aa="CO2\n0.0";
         labCP = new QLabel(this);
         labCP->setStyleSheet("background-color: lightGray");
         labCP->setWordWrap(true);
         labCP->setAlignment(Qt::AlignCenter);
//         labCP->setText("<FONT COLOR=#000000>ДАВЛЕНИЕ CO2=4.00</FONT>");
         labCP->setText(aa);
         font = labCP->font();
         font.setPointSize(20*FSCALE);
         font.setBold(true);
         labCP->setFont(font);
         labCP->adjustSize();
         labCP->setGeometry(prBX-leftX-labOP->width(),
                            prBY+prB->height()/2-prB->height()/10/2-labOP->height()+prB->height()/10,
                            labOP->width(),labOP->height());
         labCP->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        aa="Смесь\n0.0";
        labOutP = new QLabel(this);
        labOutP->setStyleSheet("background-color: lightGray");
        labOutP->setWordWrap(true);
        labOutP->setAlignment(Qt::AlignCenter);
        labOutP->setText(aa);
        font = labOutP->font();
        font.setPointSize(20*FSCALE);
        font.setBold(true);
        labOutP->setFont(font);
        labOutP->adjustSize();
        labOutP->setGeometry(prBX+prB->width()+leftX,
                    prBY+prB->height()-prB->height()/8-prB->height()/10-labOP->height()+prB->height()/10,
                    labOP->width(),labOP->height());
        labOutP->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    labCO2 = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labCO2->setWordWrap(true);
    labCO2->setAlignment(Qt::AlignCenter);
    labCO2->setText("<FONT COLOR=#ffff00>%CO2 </FONT>");
    font = labCO2->font();
    font.setPointSize(40*FSCALE);
    font.setBold(true);
    labCO2->setFont(font);
    labCO2->adjustSize();
    //lw=labCO2->width();
    labCO2->setGeometry(this->width()/100,this->height()/100,labCO2->width(),labCO2->height());
    labCO2->hide();

    labCO2D = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labCO2D->setWordWrap(true);
    labCO2D->setAlignment(Qt::AlignCenter);
    labCO2D->setText("<FONT COLOR=#ffffff>00.0%</FONT>");
    font = labCO2D->font();
    font.setPointSize(40*FSCALE);
    font.setBold(true);
    labCO2D->setFont(font);
    labCO2D->adjustSize();
    //lw=labCO2->width();
//    labCO2D->setGeometry(this->height()/4*3/4-labCO2->width()/2+labCO2->width(),this->height()/100,labCO2D->width(),labCO2D->height());
    labCO2D->setGeometry(this->width()/100+labCO2->width(),this->height()/100,labCO2D->width(),labCO2D->height());
    labCO2D->hide();

    int dopX; int dopY;
    dopX=this->height()/3*4/2/2-(labCO2->width()+labCO2D->width())/2;
    labCO2->setGeometry(dopX,this->height()/100,labCO2->width(),labCO2->height());
    labCO2D->setGeometry(dopX+labCO2->width(),this->height()/100,labCO2D->width(),labCO2D->height());
    labCO2->show();
    labCO2D->show();

    labSCO2 = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labSCO2->setWordWrap(true);
    labSCO2->setAlignment(Qt::AlignCenter);
    labSCO2->setText("<FONT COLOR=#ffffff>%CO2</FONT>");
    font = labSCO2->font();
    font.setPointSize(30*FSCALE);
    font.setBold(true);
    labSCO2->setFont(font);
    labSCO2->adjustSize();
    //lw=labCO2->width();
    labSCO2->setGeometry(dopX,this->height()/100+labCO2->height(),
                         labSCO2->width(),labSCO2->height());
    labSCO2->show();

    labSCO2Ust = new QLabel(this);
    aa="уст            ";
    //labCO2->setStyleSheet("background-color: yellow");
//    labSCO2Ust->setWordWrap(true);
    labSCO2Ust->setAlignment(Qt::AlignLeft);
    labSCO2Ust->setText("<FONT COLOR=#ffffff>уст</FONT>");
//    labSCO2Ust->setText(aa);
    font = labSCO2Ust->font();
    font.setPointSize(20*FSCALE);
//    font.setBold(true);
    labSCO2Ust->setFont(font);
//    labSCO2Ust->adjustSize();
    //lw=labCO2->width();
    labSCO2Ust->setGeometry(dopX+labSCO2->width(),this->height()/100+labCO2->height()+labSCO2->height()/4,
                         labSCO2Ust->width(),labSCO2Ust->height());
//    labSCO2->show();


    labSCO2D = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labSCO2D->setWordWrap(true);
    labSCO2D->setAlignment(Qt::AlignLeft);
    labSCO2D->setText("<FONT COLOR=#ffffff>00.00</FONT>");
    font = labSCO2D->font();
    font.setPointSize(30*FSCALE);
    font.setBold(true);
    labSCO2D->setFont(font);
    labSCO2D->adjustSize();
    //lw=labCO2->width();
//    dopX=this->height()/3*4/2/2-(labCO2->width()+labCO2D->width()+labSCO2Ust->width()/2);

    labSCO2D->setGeometry(dopX+labCO2->width(),this->height()/100+labCO2->height(),
                        labSCO2D->width(),labSCO2D->height());
    labSCO2D->show();

    dopY=this->height()/4/2-(labCO2D->height()+labCO2->height())/2;

    labCO2->setGeometry(dopX,dopY,labCO2->width(),labCO2->height());
    labCO2D->setGeometry(dopX+labCO2->width(),dopY,labCO2D->width(),labCO2D->height());

    labSCO2->setGeometry(dopX,dopY+labCO2->height(),
                         labSCO2->width(),labSCO2->height());
    labSCO2Ust->setGeometry(dopX+labSCO2->width(),this->height()/100+labCO2->height()+labSCO2->height()/4+dopY,
                                               labSCO2Ust->width(),labSCO2Ust->height());
    labSCO2D->setGeometry(dopX+labSCO2->width()+labSCO2Ust->width(),dopY+labCO2->height(),
                          labSCO2D->width(),labSCO2D->height());

//------------------------------------------------------------------------
    labO2 = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labO2->setWordWrap(true);
    labO2->setAlignment(Qt::AlignCenter);
    labO2->setText("<FONT COLOR=#ffff00>%O2 </FONT>");
    font = labO2->font();
    font.setPointSize(40*FSCALE);
    font.setBold(true);
    labO2->setFont(font);
    labO2->adjustSize();
    //lw=labCO2->width();
    labO2->setGeometry(this->height()/3*4/2,this->height()/100,labO2->width(),labO2->height());

    labO2D = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labO2D->setWordWrap(true);
    labO2D->setAlignment(Qt::AlignCenter);
    labO2D->setText("<FONT COLOR=#ffffff>0.00%</FONT>");
    font = labO2D->font();
    font.setBold(true);
    font.setPointSize(40*FSCALE);
    labO2D->setFont(font);
    labO2D->adjustSize();
    //lw=labCO2->width();
    labO2D->setGeometry(this->height()/3*4/2+labO2->width(),this->height()/100,
                        labO2D->width(),labO2D->height());

    dopX=this->height()/3*4/4*3-(labO2->width()+labO2D->width())/2;

    labO2->setGeometry(dopX,this->height()/100,labO2->width(),labO2->height());
    labO2D->setGeometry(dopX+labO2->width(),this->height()/100,
                        labO2D->width(),labO2D->height());

    labSO2 = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
    labSO2->setWordWrap(true);
    labSO2->setAlignment(Qt::AlignCenter);
    labSO2->setText("<FONT COLOR=#ffffff>%O2</FONT>");
    font = labSO2->font();
    font.setPointSize(30*FSCALE);
    font.setBold(true);
    labSO2->setFont(font);
    labSO2->adjustSize();
    //lw=labCO2->width();
    labSO2->setGeometry(dopX,this->height()/100+labCO2->height(),
                         labSO2->width(),labSO2->height());


    labSO2Ust = new QLabel(this);
    aa="уст            ";
    //labCO2->setStyleSheet("background-color: yellow");
//    labSCO2Ust->setWordWrap(true);
    labSO2Ust->setAlignment(Qt::AlignLeft);
    labSO2Ust->setText("<FONT COLOR=#ffffff>уст</FONT>");
//    labSCO2Ust->setText(aa);
    font = labSO2Ust->font();
    font.setPointSize(20*FSCALE);
//    font.setBold(true);
    labSO2Ust->setFont(font);
//    labSCO2Ust->adjustSize();
    //lw=labCO2->width();
    labSO2Ust->setGeometry(dopX+labSO2->width(),this->height()/100+labO2->height()+labSO2->height()/4,
                         labSO2Ust->width(),labSO2Ust->height());


//this->height()/100+labCO2->height()+labSCO2->height()/4

    labSO2D = new QLabel(this);
    //labCO2->setStyleSheet("background-color: yellow");
//    labSO2D->setWordWrap(true);
    labSO2D->setAlignment(Qt::AlignLeft);
    labSO2D->setText("<FONT COLOR=#ffffff>0.00</FONT>");
    font = labSO2D->font();
    font.setPointSize(30*FSCALE);
    font.setBold(true);
    labSO2D->setFont(font);
    labSO2D->adjustSize();
    //lw=labCO2->width();
    labSO2D->setGeometry(dopX+labO2->width()+labSO2Ust->width(),this->height()/100+labCO2->height(),
                        labSO2D->width(),labSO2D->height());
    labSO2D->show();

    labO2->setGeometry(dopX,dopY,labO2->width(),labO2->height());
    labO2D->setGeometry(dopX+labO2->width(),dopY,
                        labO2D->width(),labO2D->height());
    labSO2->setGeometry(dopX,dopY+labO2->height(),
                         labSO2->width(),labSO2->height());
    labSO2Ust->setGeometry(dopX+labSO2->width(),dopY+this->height()/100+labO2->height()+labSO2->height()/4,
                         labSO2Ust->width(),labSO2Ust->height());
    labSO2D->setGeometry(dopX+labSO2->width()+labSO2Ust->width(),dopY+labO2->height(),
                        labSO2D->width(),labSO2D->height());

   labSO2->show();
    labSO2D->show();
    labO2D->show();
    labO2->show();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    labRePD = new QLabel(this);
    labRePD->setWordWrap(true);
    labRePD->setAlignment(Qt::AlignCenter);
    labRePD->setText("<FONT COLOR=#ffffff>0.00</FONT>");
    font = labRePD->font();
    font.setPointSize(18*FSCALE);
    font.setBold(true);
    labRePD->setFont(font);
    labRePD->adjustSize();
    labRePD->setGeometry(prBX+this->width()/7/2-labRePD->width()/2,prBY-labRePD->height(),
                         labRePD->width(),labRePD->height());
//    labRePD->setGeometry(prBX+prB->width()+prB->width()/4+labReP->width(),prBY+prB->height()/3+labReP->height()/2,
//                        labRePD->width(),labRePD->height());
    labRePD->show();

    labReP = new QLabel(this);
    labReP->setWordWrap(true);
    labReP->setAlignment(Qt::AlignCenter);
    labReP->setText("<FONT COLOR=#ffffff>Давление</FONT>");
    font = labReP->font();
    font.setPointSize(18*FSCALE);
    font.setBold(true);
    labReP->setFont(font);
    labReP->adjustSize();
    labReP->setGeometry(prBX+this->width()/7/2-labReP->width()/2,prBY-labRePD->height()-labReP->height(),
                        labReP->width(),labReP->height());
    labReP->show();


    labReP1 = new QLabel(this);
    labReP1->setWordWrap(true);
    labReP1->setAlignment(Qt::AlignCenter);
    labReP1->setText("<FONT COLOR=#ffffff>Давление</FONT>");
    font = labReP1->font();
    font.setPointSize(18*FSCALE);
    font.setBold(true);
    labReP1->setFont(font);
    labReP1->adjustSize();
    labReP1->setGeometry(prBX-leftX-labNP->width()+labNP->width()/2-labReP1->width()/2,
                         prBY-labRePD->height()-labReP->height(),
                        labReP1->width(),labReP1->height());
    labReP1->show();

         aa="Поток";
              labGAS = new QLabel(this);
              labGAS->setStyleSheet("color: white; background-color: blue;");
              labGAS->setWordWrap(true);
              labGAS->setAlignment(Qt::AlignRight);
              labGAS->setText(aa);
              font = labGAS->font();
              font.setPointSize(18*FSCALE);
              font.setBold(true);
              labGAS->setFont(font);
              labGAS->adjustSize();
              labGAS->setGeometry(prBX-leftX+leftX/2-labGAS->width()/2,prBY-labRePD->height()-labReP->height(),
                                  labGAS->width(),labGAS->height());
              labGAS->show();
    //          prBX-leftX,prBY+prB->height()/8
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    aa="Поток";
    labGAS1 = new QLabel(this);
    labGAS1->setStyleSheet("color: white; background-color: blue;");
    labGAS1->setWordWrap(true);
    labGAS1->setAlignment(Qt::AlignRight);
    labGAS1->setText(aa);
     font = labGAS1->font();
     font.setPointSize(18*FSCALE);
     font.setBold(true);
    labGAS1->setFont(font);
    labGAS1->adjustSize();
    labGAS1->setGeometry(prBX+prB->width()+leftX/2-labGAS1->width()/2,prBY-labRePD->height()-labReP->height(),
                         labGAS1->width(),labGAS1->height());
    labGAS1->show();
             //          prBX-leftX,prBY+prB->height()/8



    labReP2 = new QLabel(this);
    labReP2->setWordWrap(true);
    labReP2->setAlignment(Qt::AlignCenter);
    labReP2->setText("<FONT COLOR=#ffffff>Давление</FONT>");
    font = labReP2->font();
    font.setPointSize(18*FSCALE);
    font.setBold(true);
    labReP2->setFont(font);
    labReP2->adjustSize();
//    labReP2->setGeometry(prBX+prB->width()+leftX,prBY-labRePD->height()-labReP->height(),
//                        labReP2->width(),labReP2->height());
    labReP2->setGeometry(prBX+prB->width()+leftX+labOP->width()/2-labReP2->width()/2,prBY-labRePD->height()-labReP->height(),
                        labReP2->width(),labReP2->height());
    labReP2->show();

 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        labLE = new QLabel(this);
        //labCO2->setStyleSheet("background-color: yellow");
        labLE->setWordWrap(true);
        labLE->setAlignment(Qt::AlignCenter);
        labLE->setText("<FONT COLOR=#ffff00>ВХОД</FONT>");
        font = labLE->font();
        font.setPointSize(30*FSCALE);
        font.setBold(true);
        labLE->setFont(font);
        labLE->adjustSize();
        //lw=labCO2->width();
//        labLE->setGeometry(this->width()/10,this->height()/5,labLE->width(),labLE->height());

//        labLE->setGeometry(prBX-(leftX+labOP->width())/2-labLE->width()/2,this->height()/4,
                           labLE->setGeometry(prBX-(leftX+labOP->width())/2-labLE->width()/2,this->height()/4+5,
                           labLE->width(),labLE->height());
        labLE->show();
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        labRE = new QLabel(this);
        //labCO2->setStyleSheet("background-color: yellow");
        labRE->setWordWrap(true);
        labRE->setAlignment(Qt::AlignCenter);
        labRE->setText("<FONT COLOR=#ffff00>РЕСИВЕР</FONT>");
        font = labRE->font();
        font.setPointSize(30*FSCALE);
        font.setBold(true);
        labRE->setFont(font);
        labRE->adjustSize();
        //lw=labCO2->width();
        labRE->setGeometry(prBX+prB->width()/2-labRE->width()/2,this->height()/4+5,
                           labRE->width(),labRE->height());
        labRE->show();
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        labRI = new QLabel(this);
        //labCO2->setStyleSheet("background-color: yellow");QLabel
        labRI->setWordWrap(true);
        labRI->setAlignment(Qt::AlignCenter);
        labRI->setText("<FONT COLOR=#ffff00>ВЫХОД</FONT>");
        font = labRI->font();
        font.setPointSize(30*FSCALE);
        font.setBold(true);
        labRI->setFont(font);
        labRI->adjustSize();
        //lw=labCO2->width();
        labRI->setGeometry(prBX+prB->width()+(leftX+labOP->width())/2-labRI->width()/2,this->height()/4+5,
                           labRI->width(),labRI->height());
    //    labRI->setGeometry(this->width()/10*3,this->height()/4,labRI->width(),labRI->height());
        labRI->show();
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        aa="Внимание!!\nДавление газов\nна входе ниже нормы.";
        labErGasInp = new QLabel(this);
        labErGasInp->setStyleSheet("color: #ffffff; background-color: red;border: 5px solid grey;");
//        labErGasInp->setStyleSheet("color: yellow");
        labErGasInp->setWordWrap(true);
        labErGasInp->setAlignment(Qt::AlignCenter);
        labErGasInp->setText(aa);
        font = labErGasInp->font();
        font.setPointSize(20*FSCALE);
        font.setBold(true);
        labErGasInp->setFont(font);
        labErGasInp->adjustSize();
        //lw=labCO2->width();
//        labErGasInp->setGeometry(prBX+prB->width()/2-labRE->width()/2,this->height()/4+5,
//                           labRE->width(),labRE->height());
        labErGasInp->setGeometry(prBX+prB->width()+10,prBY,
                                 labErGasInp->width(),labErGasInp->height());
//        labErGasInp->show();
        labErGasInp->hide();
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        aa="Внимание!!\nСостав газовой смеси\nне соответстует\nзаявленному значению.";
        labErGasOut = new QLabel(this);
        labErGasOut->setStyleSheet("color: #ffffff; background-color: red;border: 5px solid grey;");
//        labErGasInp->setStyleSheet("color: yellow");
        labErGasOut->setWordWrap(true);
        labErGasOut->setAlignment(Qt::AlignCenter);
        labErGasOut->setText(aa);
        font = labErGasOut->font();
        font.setPointSize(20*FSCALE);
        font.setBold(true);
        labErGasOut->setFont(font);
        labErGasOut->adjustSize();
        //lw=labCO2->width();
//        labErGasInp->setGeometry(prBX+prB->width()/2-labRE->width()/2,this->height()/4+5,
//                           labRE->width(),labRE->height());
        labErGasOut->setGeometry(prBX+prB->width()+10,prBY,
                                 labErGasOut->width(),labErGasOut->height());
//        labErGasOut->show();
        labErGasOut->hide();
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
//========================================================================================================================
void wnormwork::winExit()
{


                delete ptimer;
            //    delete bo;


                emit workRestart(7);

                this->close();
                this->deleteLater();


}
//========================================================================================================================
void wnormwork::timMesB(void)
{
    timerMesB->stop();
    msgBox->close();
//    ui->progressBar->setValue(0);
//    ptimer->start(3000);


}
//========================================================================================================================
//========================================================================================================================
void wnormwork::winTest(void)
{
    prBO->setValue(300);
    prB->setValue(1500);
    prIN->setValue(0);
    prIC->setValue(0);
    prIO->setValue(0);
    aa="ДАВЛЕНИЕ\nN=7.00";
    labNP->setText(aa);
    aa="ДАВЛЕНИЕ O2=9.0";
    labOP->setText(aa);


}
//========================================================================================================================
