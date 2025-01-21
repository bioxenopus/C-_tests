#include <QFont>
#include "widget.h"
#include "ui_widget.h"
//#include "mdef.h"
uint32_t adcD[20];
float adcU[20];
float adcR[20];
unsigned char trigEx;
unsigned char errSPI_GPIO;
#define FSCALE 0.6

//========================================================================================================================
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
 //   QWidget::showFullScreen();


#ifdef RASPBERRY
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//+++ Disable TITLE Win ++++++
    QScreen *scr = QApplication::screens().at(0);

    scrWidth = scr->geometry().width(); // ширина Экрана
    scrHeight = scr->geometry().height(); // высота экрана
    //this->setGeometry(0,0,scrWidth,scrHeight);
    this->setGeometry(0,0,scrWidth,scrHeight);
    this->resize(1024,600);
    this->setStyleSheet("background-color: blue");

#else

    //setWindowFlags(Qt::Window | Qt::MSWindowsOwnDC);//+++ Disable TITLE Win ++++++
    //this->setWindowState(Qt::WindowFullScreen);
    /*QDesktopWidget *desktop = QApplication::desktop();
    if (1==desktop->screenCount() )
    {
        // single monitor - use built in
        //       showFullScreen();
    }
    else
    {
        rect = desktop->screenGeometry(1);
        move(rect.topLeft());
        //       setWindowState(Qt::WindowFullScreen);
    }
*/
    // qDebug() << desktop->screenGeometry(0);
    // qDebug() << desktop->screenGeometry(1);
    // qDebug() << desktop->screenGeometry(2);
    scrWidth = rect.width(); // ширина Экрана
    scrHeight =rect.height(); // высота экрана
    // qDebug() << scrWidth;
    // qDebug() << scrHeight;
    //this->setGeometry(1280,50,scrWidth,scrHeight);
    this->setStyleSheet("background-color: blue");  
#endif

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    QFont newFont("fonts.dtd", 16, QFont::Bold, true);
    //    QFont newFont("Courier", 8, QFont::Bold, true);
    QApplication::setFont(newFont);
    //fc-list :lang=ru
    //    fonts.dtd
    //    /etc/fonts/fonts.conf
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //-------------------------------------------------
    errSPI_GPIO=0; errGdatFile=0;
    //-------------------------------------------------
    gd = new gmdata(this);

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ind = new initPer(this,gd);  /// считывает из настроек параметры в свежесозданную структуру gmdata
    ind->readUsDat();
    delete ind;

    float full; /// Получение процентных значений из долевых значений
    full=gd->u_d.setpointFull;
    gd->u_d.setpointDioxide=gd->u_d.percentDioxide*full/100;
    gd->u_d.setpointAir=gd->u_d.percentAir/0.21*full/100;
    gd->u_d.setpointNitrogen=gd->u_d.setpointFull-gd->u_d.setpointDioxide-gd->u_d.setpointAir;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++



    // qDebug() << "gd->u_d.A7"<<gd->u_d.A7;


    datSpi = new spi(this,gd); // Управление шиной SPI?
    wDAC = new spiDAC(this); // Управление подключаемым девайсом
    setKL = new klapan(this); // Управление подключаемым девайсом
    obnw = new objnorwork(this,gd,datSpi,wDAC,setKL); // объект управления устройствами

    // qDebug() << "widget : call objnormwork = " << obnw;

    obsg = new objselgas(this,datSpi,wDAC,setKL,gd);

    // qDebug() << "widget : call objselgas = " << obsg;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // qDebug() << "widget : setDatim(): " ;
    tset = new setDatTim(this);
    // qDebug() << "widget : setDatim(): passed" ;
    tset->readTim();
    tset->setRasTD();
    //-------------------------------------------------
    // qDebug() << "widget : winInit(): " ;
    winInit();
    // qDebug() << "widget : winInit(): passed" ;
    //____________________________________________________

    aa=QString::number(gd->u_d.percentDioxide,'f',1);
    labCO2D->setText(aa);
    aa=QString::number(gd->u_d.setpointDioxide,'f',1);
    labCO2F->setText(aa);
    aa=QString::number(gd->u_d.percentAir,'f',1);
    labO2D->setText(aa);
    aa=QString::number(gd->u_d.setpointAir,'f',1);
    labO2F->setText(aa);
    aa=QString::number(gd->u_d.setpointFull,'f',1);
    labFN2D->setText(aa);
    aa=QString::number(gd->u_d.setpointNitrogen,'f',1);
    labFN2F->setText(aa);
    aa=QString::number(gd->u_d.receiverPmax,'f',1);
    labMAXPD->setText(aa);
    //____________________________________________________

    bo = new border(this,0,this->width(),this->height());
    bo->show();


    connect(bo,SIGNAL(workEND(void)),this,SLOT(winExit(void)));
    connect(bo,SIGNAL(workRestart(int)),this,SLOT(winRestart(int)));
    connect(bo,SIGNAL(workFactorySet(int)),this,SLOT(winFactorySet(int)));

    ui->progressBar->setStyleSheet("QProgressBar {background-color: white; border: 2px solid grey; "
                                   "border-radius: 5px;} QProgressBar::chunk {background-color: yellow;}");
    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(30);
    ui->progressBar->setValue(0);

    ui->progressBar->setGeometry(((this->height()/3*4)-lw)/2+labMAXP->width(),this->height()/2+labO2->height()*4.5,
                                 this->width()/3,this->height()/25);
    //-------------------------------------------------
    setKL->setKlap(0,1);

    //-------------------------------------------------
    //vo->on_alarm();
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    QApplication::setOverrideCursor(Qt::BlankCursor);
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    timerMesB = new QTimer(this);
    timerMesB->stop();
    connect(timerMesB, SIGNAL(timeout()),this,SLOT(timMesB()));

    pptpTim = new QTimer(this);
    connect(pptpTim, SIGNAL(timeout()),this,SLOT(slotpptpTim()));
    pptpTim->start(30000);

    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()),this,SLOT(slotPtim()));
    ptimer->start(3000);

}
//========================================================================================================================
void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        setKL->setKlap(0,0);
        setKL->setKlap(1,0);
        setKL->setKlap(2,0);
        setKL->setKlap(3,0);
        setKL->setKlap(4,0);
        this->close();
    }
}
//========================================================================================================================
void Widget::winFactorySet(int arg)
{
    ptimer->stop(); countTim=0;
    // qDebug() <<"+++++++ winFactorySet +++++++++"<<arg;
    // qDebug() <<"+++++++ on_pushPB2_clicked numW==0 +++++++++";
    //____________________________
    msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("ПРЕДУПРЕЖДЕНИЕ");
    msgBox->setStyleSheet("background-color: white");
    font = msgBox->font();
    font.setPointSize(40*FSCALE); //40
    font.setBold(true);
    msgBox->setFont(font);
    msgBox->setText("Внимание ");
    msgBox->setInformativeText("\n"
                               "Ок - продолжить\nCancel - отменить");
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->button(QMessageBox::Ok)->setStyleSheet("padding: 40px;background-color: rgb(255,255, 0)");
    msgBox->button(QMessageBox::Cancel)->setStyleSheet("padding: 40px; background-color: rgb(255,255, 0)");
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setDefaultButton(QMessageBox::Ok);
    msgBox->setGeometry(msgBox->width()/2,
                        msgBox->height()/2,
                        msgBox->width(),msgBox->height());
    timerMesB->start(10000);
    int res = msgBox->exec();
    //_______________________________

    if (res == QMessageBox::Ok)
    {
        timerMesB->stop();
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if (QFile::exists("/home/pi/Gdata/gdata.conf"))
        {
            QFile("/home/pi/Gdata/user_data.bak").remove();
            res=QFile::rename ("/home/pi/Gdata/user_data.conf",
                                "/home/pi/Gdata/user_data.bak" );
            res1=QFile::copy("/home/pi/Gdata/gdata.conf",
                               "/home/pi/Gdata/user_data.conf");

            QFile File("/home/pi/Gdata/user_data.conf");
            File.setPermissions((((File.permissions() |= QFile::WriteOwner) |= QFile::WriteUser) |=
                                 QFile::WriteGroup) |= QFile::WriteOther);
            errGdatFile=0;
        }
    }
    else
    {
        timerMesB->stop();
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        errGdatFile=1;
    }
    // qDebug() <<"+++++ errGdatFile="<<errGdatFile;
    // qDebug() <<"+++++ errGdatFile="<<QDir::homePath()<<QDir::separator();
    // qDebug() <<"+++++ errGdatFile="<<res<<res1;

    winRestart(7);
}
//========================================================================================================================
Widget::~Widget()
{
    delete ui;
}
//=============================================================================================
void Widget::slotpptpTim(void)
{
    pptpTim->stop();
    pptpCoun++;
    if(pptpCoun >= 10)
    {
        pptpCoun=0;
        if((obnw->statusR != SETPRESU) && (adcR[0] >= 2.5))
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
                                                             << "192.168.3.1");
                //             << "192.168.100.1");
                //              << "95.165.140.47");
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
//========================================================================================================================
void Widget::slotPtim()
{
    ptimer->stop();
    countTim++;
    if(countTim < 11)
    {
        ui->progressBar->setValue(ui->progressBar->value()+3);
        ptimer->start(3000);

    }
    else
    {
        /*
    ptimer->stop();
    wn = new wnormwork(this,gd);
    connect(wn,SIGNAL(workRestart(int)),this,SLOT(winRestart(int)));
    wn->show();
    this->hide();
    obnw->startDAC();
*/

        ptimer->stop(); countTim=0;
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        tset->setRtcTD();
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ind = new initPer(this,gd);
        ind->readUsDat();
        delete ind;
        float full;
        full=gd->u_d.setpointFull;
        gd->u_d.setpointDioxide=gd->u_d.percentDioxide*full/100;
        gd->u_d.setpointAir=gd->u_d.percentAir/0.21*full/100;
        gd->u_d.setpointNitrogen=gd->u_d.setpointFull-gd->u_d.setpointDioxide-gd->u_d.setpointAir;
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        wn = new wnormwork(nullptr,gd,setKL);
        connect(wn,SIGNAL(workRestart(int)),this,SLOT(winRestart(int)), Qt::DirectConnection);
        wn->show();
        this->hide();
        obnw->startDAC();

    }
}
//========================================================================================================================
void Widget::winRestart(int a)
{
    // qDebug() <<"+++++++ winRestart +++++++++"<<a;
    if(a==1)
    {
        ptimer->stop(); countTim=0;
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        tset->setRtcTD();
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ind = new initPer(this,gd);
        ind->readUsDat();
        delete ind;
        float full;
        full=gd->u_d.setpointFull;
        gd->u_d.setpointDioxide=gd->u_d.percentDioxide*full/100;
        gd->u_d.setpointAir=gd->u_d.percentAir/0.21*full/100;
        gd->u_d.setpointNitrogen=gd->u_d.setpointFull-gd->u_d.setpointDioxide-gd->u_d.setpointAir;
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        wn = new wnormwork(nullptr,gd,setKL);
        connect(wn,SIGNAL(workRestart(int)),this,SLOT(winRestart(int)), Qt::DirectConnection);
        wn->show();
        this->hide();
        obnw->startDAC();
    }
    else if(a==2)
    {
        ptimer->stop(); countTim=0;

        //____________________________
        msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("ПРЕДУПРЕЖДЕНИЕ");
        msgBox->setStyleSheet("background-color: white");
        font = msgBox->font();
        font.setPointSize(40*FSCALE);
        font.setBold(true);
        msgBox->setFont(font);
        msgBox->setText("Внимание!");
        msgBox->setInformativeText("После проведения настроек состав газовой смеси будет изменен\nОк - продолжить\nCancel - отменить");
        msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox->button(QMessageBox::Ok)->setStyleSheet("padding: 40px;background-color: rgb(255,255, 0)");
        msgBox->button(QMessageBox::Cancel)->setStyleSheet("padding: 40px; background-color: rgb(255,255, 0)");
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setDefaultButton(QMessageBox::Ok);
        msgBox->setGeometry(msgBox->width()/2,
                            msgBox->height()/2,
                            msgBox->width(),msgBox->height());
        timerMesB->start(10000);
        int res = msgBox->exec();
        //_______________________________

        if (res == QMessageBox::Ok)
        {
            timerMesB->stop();
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
            ind = new initPer(this,gd);
            ind->readUsDat();
            delete ind;
            float full;
            full=gd->u_d.setpointFull;
            gd->u_d.setpointDioxide=gd->u_d.percentDioxide*full/100;
            gd->u_d.setpointAir=gd->u_d.percentAir/0.21*full/100;
            gd->u_d.setpointNitrogen=gd->u_d.setpointFull-gd->u_d.setpointDioxide-gd->u_d.setpointAir;
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
            wt = new wtuning(nullptr,gd,obsg,setKL);
            connect(wt,SIGNAL(workRestart(int)),this,SLOT(winRestart(int)), Qt::DirectConnection);
            wt->show();
            this->hide();
        }
        else
        {

             //qDebug() <<"+++++++ widget.cpp : VO ALARM +++++++++";
             //system("aplay /home/pi/Gdata/Tada.mp3");
             vo->on_alarm();

            timerMesB->stop();
            ui->progressBar->setValue(0);
            ptimer->start(5000);

        }

    }
    else if(a==7)
    {
        ptimer->stop(); countTim=0;
        // qDebug() <<"+++++++ bbbbbbb +++++++++"<<a;
        obnw->stopDAC();
        // qDebug() <<"+++++++ aaaaaa +++++++++"<<a;
        //-------------------------------------------------
        setKL->setKlap(0,1);
        //-------------------------------------------------

        //____________________________________________________

        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ind = new initPer(this,gd);
        ind->readUsDat();
        delete ind;
        float full;
        full=gd->u_d.setpointFull;
        gd->u_d.setpointDioxide=gd->u_d.percentDioxide*full/100;
        gd->u_d.setpointAir=gd->u_d.percentAir/0.21*full/100;
        gd->u_d.setpointNitrogen=gd->u_d.setpointFull-gd->u_d.setpointDioxide-gd->u_d.setpointAir;
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        aa=QString::number(gd->u_d.percentDioxide,'f',1);
        labCO2D->setText(aa);
        aa=QString::number(gd->u_d.setpointDioxide,'f',1);
        labCO2F->setText(aa);
        aa=QString::number(gd->u_d.percentAir,'f',1);
        labO2D->setText(aa);
        aa=QString::number(gd->u_d.setpointAir,'f',1);
        labO2F->setText(aa);
        aa=QString::number(gd->u_d.setpointFull,'f',1);
        labFN2D->setText(aa);
        aa=QString::number(gd->u_d.setpointNitrogen,'f',1);
        labFN2F->setText(aa);
        aa=QString::number(gd->u_d.receiverPmax,'f',1);
        labMAXPD->setText(aa);
        //____________________________________________________

        this->show();
        ui->progressBar->setValue(0);
        ptimer->start(3000);


    }


}
//========================================================================================================================
void Widget::timMesB(void)
{
    timerMesB->stop();
    msgBox->close();
    ui->progressBar->setValue(0);
    ptimer->start(3000);


}
//========================================================================================================================
void Widget::winExit()
{
    //____________________________
    msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("ПРЕДУПРЕЖДЕНИЕ");
    msgBox->setStyleSheet("background-color: white");
    font = msgBox->font();
    font.setPointSize(40*FSCALE);
    font.setBold(true);
    msgBox->setFont(font);
    msgBox->setText("Внимание!");
    msgBox->setInformativeText("Завершить работу программы?\nОк - продолжить\nCancel - отменить");
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->button(QMessageBox::Ok)->setStyleSheet("padding: 40px;background-color: rgb(255,255, 0)");
    msgBox->button(QMessageBox::Cancel)->setStyleSheet("padding: 40px; background-color: rgb(255,255, 0)");
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setDefaultButton(QMessageBox::Ok);
    msgBox->setGeometry(msgBox->width()/2,
                        msgBox->height()/2,
                        msgBox->width(),msgBox->height());
    timerMesB->start(10000);
    int res = msgBox->exec();
    //_______________________________

    if (res == QMessageBox::Ok)
    {
        timerMesB->stop();
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
        QProcess process;
        process.startDetached("shutdown -P now");
        exit(0);
    }
    else
    {

    }

}
//========================================================================================================================
void Widget::winInit()
{
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  ЗАГОЛОВОК   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    lab1 = new QLabel(this);
    lab1->setWordWrap(true);
    lab1->setAlignment(Qt::AlignCenter);
    lab1->setText("<FONT COLOR=#ffff00>ГАЗОСМЕСИТЕЛЬНАЯ СТАНЦИЯ</FONT>");
    font = lab1->font(); //создание объекта класса QFont копированием свойсв QFont у QLabel
    font.setPointSize(55*FSCALE); //установка высоты шрифта, в данном случае 20
    font.setWeight(QFont::Normal);
    font.setBold(true);
    lab1->setFont(font); //установка изменненного шрифта (QFont) объекту класса QLabel
    lab1->adjustSize();
    lw=lab1->width();
    lab1->setGeometry(((this->height()/3*4)-lw)/2,this->height()/30,lab1->width(),lab1->height());
    lab1->show(); //для просмотра
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    labCO2 = new QLabel(this);
    labCO2->setWordWrap(true);
    labCO2->setAlignment(Qt::AlignCenter);
    labCO2->setText("<FONT COLOR=#00ff00>CO2,%=</FONT>");
    font = labCO2->font();
    font.setPointSize(40*FSCALE);
    labCO2->setFont(font);
    labCO2->adjustSize();
    labCO2->setGeometry(((this->height()/3*4)-lw)/2,this->height()/2,labCO2->width(),labCO2->height());
    labCO2->show();

    labCO2D = new QLabel(this);
    labCO2D->setWordWrap(true);
    labCO2D->setAlignment(Qt::AlignCenter);
    labCO2D->setText("<FONT COLOR=#00ff00>6.00</FONT>");
    labCO2D->setStyleSheet("color: #00ff00");
    font = labCO2D->font();
    font.setPointSize(40*FSCALE);
    labCO2D->setFont(font);
    labCO2D->adjustSize();
    labCO2D->setGeometry(((this->height()/3*4)-lw)/2+labCO2->width(),this->height()/2,labCO2D->width(),labCO2D->height());
    labCO2D->show();

    labCO2F = new QLabel(this);
    labCO2F->setWordWrap(true);
    labCO2F->setAlignment(Qt::AlignCenter);
    labCO2F->setText("<FONT COLOR=#00ff00>119.90</FONT>");
    labCO2F->setStyleSheet("color: #00ff00");
    font = labCO2F->font();
    font.setPointSize(40*FSCALE);
    labCO2F->setFont(font);
    labCO2F->adjustSize();
    labCO2F->setGeometry(((this->height()/3*4)/3*2),this->height()/2,labCO2F->width(),labCO2F->height());
    labCO2F->show();


    labO2 = new QLabel(this);
    labO2->setWordWrap(true);
    labO2->setAlignment(Qt::AlignCenter);
    labO2->setText("<FONT COLOR=#00ff00>O2,%=</FONT>");
    font = labO2->font();
    font.setPointSize(40*FSCALE);
    labO2->setFont(font);
    labO2->adjustSize();
    labO2->setGeometry(((this->height()/3*4)-lw)/2,this->height()/2+labO2->height(),labO2->width(),labO2->height());
    labO2->show();

    labO2D = new QLabel(this);
    labO2D->setWordWrap(true);
    labO2D->setAlignment(Qt::AlignCenter);
    labO2D->setText("<FONT COLOR=#00ff00>5.00</FONT>");
    labO2D->setStyleSheet("color: #00ff00");
    font = labO2D->font();
    font.setPointSize(40*FSCALE);
    labO2D->setFont(font);
    labO2D->adjustSize();
    labO2D->setGeometry(((this->height()/3*4)-lw)/2+labO2->width(),this->height()/2+labO2->height(),
                        labO2D->width(),labO2D->height());
    labO2D->show();

    labO2F = new QLabel(this);
    labO2F->setWordWrap(true);
    labO2F->setAlignment(Qt::AlignCenter);
    labO2F->setText("<FONT COLOR=#00ff00>476.20</FONT>");
    labO2F->setStyleSheet("color: #00ff00");
    font = labO2F->font();
    font.setPointSize(40*FSCALE);
    labO2F->setFont(font);
    labO2F->adjustSize();
    labO2F->setGeometry(((this->height()/3*4)/3*2),this->height()/2+labO2->height(),
                        labO2F->width(),labO2F->height());
    labO2F->show();


    labFN2 = new QLabel(this);
    labFN2->setWordWrap(true);
    labFN2->setAlignment(Qt::AlignCenter);
    labFN2->setText("<FONT COLOR=#00ff00>F_N2=</FONT>");
    font = labFN2->font();
    font.setPointSize(40*FSCALE);
    labFN2->setFont(font);
    labFN2->adjustSize();
    labFN2->setGeometry(((this->height()/3*4)-lw)/2,this->height()/2+labO2->height()*2,labFN2->width(),labFN2->height());
    labFN2->show();

    labFN2D = new QLabel(this);
    labFN2D->setWordWrap(true);
    labFN2D->setAlignment(Qt::AlignCenter);
    labFN2D->setText("<FONT COLOR=#00ff00>2000.00</FONT>");
    labFN2D->setStyleSheet("color: #00ff00");
    font = labFN2D->font();
    font.setPointSize(40*FSCALE);
    labFN2D->setFont(font);
    labFN2D->adjustSize();
    labFN2D->setGeometry(((this->height()/3*4)-lw)/2+labFN2->width(),this->height()/2+labO2->height()*2,
                         labFN2D->width(),labFN2D->height());
    labFN2D->show();

    labFN2F = new QLabel(this);
    labFN2F->setWordWrap(true);
    labFN2F->setAlignment(Qt::AlignCenter);
    labFN2F->setText("<FONT COLOR=#00ff00>1403.90</FONT>");
    labFN2F->setStyleSheet("color: #00ff00");
    font = labFN2F->font();
    font.setPointSize(40*FSCALE);
    labFN2F->setFont(font);
    labFN2F->adjustSize();
    labFN2F->setGeometry(((this->height()/3*4)/3*2),this->height()/2+labO2->height()*2,
                         labFN2F->width(),labFN2F->height());
    labFN2F->show();


    labMAXP = new QLabel(this);
    labMAXP->setWordWrap(true);
    labMAXP->setAlignment(Qt::AlignCenter);
    labMAXP->setText("<FONT COLOR=#00ff00>MaxP,bar=</FONT>");
    font = labMAXP->font();
    font.setPointSize(40*FSCALE);
    labMAXP->setFont(font);
    labMAXP->adjustSize();
    labMAXP->setGeometry(((this->height()/3*4)-lw)/2,this->height()/2+labO2->height()*3,labMAXP->width(),labMAXP->height());
    labMAXP->show();

    QString aa="2.90";
    labMAXPD = new QLabel(this);
    labMAXPD->setWordWrap(true);
    labMAXPD->setAlignment(Qt::AlignCenter);
    labMAXPD->setText(aa);
    labMAXPD->setStyleSheet("color: #00ff00");
    font = labMAXPD->font();
    font.setPointSize(40*FSCALE);
    labMAXPD->setFont(font);
    labMAXPD->adjustSize();
    labMAXPD->setGeometry(((this->height()/3*4)-lw)/2+labMAXP->width(),this->height()/2+labO2->height()*3,
                          labMAXPD->width(),labMAXPD->height());
    labMAXPD->show();


    labFLOW = new QLabel(this);
    labFLOW->setWordWrap(true);
    labFLOW->setAlignment(Qt::AlignCenter);
    labFLOW->setText("<FONT COLOR=#00ff00>Поток мл/мин</FONT>");
    font = labFLOW->font();
    font.setPointSize(25*FSCALE);
    labFLOW->setFont(font);
    labFLOW->adjustSize();
    labFLOW->setGeometry(((this->height()/3*4)/3*2),this->height()/2-labFLOW->height()*2,labFLOW->width(),labFLOW->height());
    labFLOW->show();
}
//========================================================================================================================
