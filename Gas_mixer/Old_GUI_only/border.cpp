#include "border.h"

#define FSCALE 0.7
#define BSCALE 0.9

border::border(QWidget *parent, unsigned char nw, int w, int h) : QLabel(parent)
{
    trigKl=0; pbEYminus=10;
    trigKl4=0;
    setGeometry(h/3*4,0,w/4,h);
    setStyleSheet("background-color: white");
    pa=parent;

    numW=nw;
    initPB();
    timerMesB = new QTimer(this);
    timerMesB->stop();
    connect(timerMesB, SIGNAL(timeout()),this,SLOT(timMesB()));

}
//==============================================
void border::initPB(void)
{
    if(numW==0)
    {

        pb = new QPushButton(this);

        //    pb->setStyleSheet(QString("color: white;"));// Цвет Текста
        this->pb->setGeometry(width()/12*BSCALE*FSCALE,this->height()/12*BSCALE,this->width()/12*BSCALE*10,this->height()/6);
        pb->setText("Изменить\nНастройки");
        pb->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset; border: 3px solid grey; "
                          "border-radius: 20px;");
        //border-right: 2px transparent; border-left: 2px transparent;
        //border-radius: 20px transparent;
        pb->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset; border: 3px solid grey;"
                          "border-radius: 20px;");
        font = pb->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb->setFont(font);
        connect(pb, SIGNAL(clicked()), this, SLOT(on_pushPB_clicked()));

        /*
    if (button->fontMetrics().elidedText(button->text(), Qt::ElideMiddle, button->geometry().width()) != button->text())
    {
        // Текст не помещается.
    }
    */

        pb->show();

        pb1 = new QPushButton(this);
        pb1->setGeometry(width()/12*BSCALE*FSCALE,this->height()/12*BSCALE*2+this->height()/6,this->width()/12*BSCALE*10,this->height()/6);
        pb1->setText("Продолжить\nРаботу");

        pb1->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset; border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pb1->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb1->setFont(font);
        /*
    font = pb1->font();
    font.setPointSize(FSCALE*18);
    pb1->setFont(font);
*/
        connect(pb1, SIGNAL(clicked()), this, SLOT(on_pushPB1_clicked()));
        pb1->show();

        pb2 = new QPushButton(this);
        pb2->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2,this->width()/12*BSCALE*10,this->height()/6);
        pb2->setText("Заводские\nНастройки");

        pb2->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset; border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pb2->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb2->setFont(font);
        /*
    font = pb2->font();
    font.setPointSize(FSCALE*18);
    pb2->setFont(font);
*/
        connect(pb2, SIGNAL(clicked()), this, SLOT(on_pushPB2_clicked()));
        pb2->show();


        pbE = new QPushButton(this);
        pbE->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset; border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pbE->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pbE->setFont(font);
        pbE->setText("ВЫХОД");
        pbE->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*4+(this->height()/6)*3-pbEYminus,
                         this->width()/12*BSCALE*10,this->height()/6);
        connect(pbE, SIGNAL(clicked()), this, SLOT(on_pushPBE_clicked()));
        pbE->show();
    }
    else if(numW==1)
    {
        pb = new QPushButton(this);

        //    pb->setStyleSheet(QString("color: white;"));// Цвет Текста
        this->pb->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE,this->width()/12*BSCALE*10,this->height()/6);
        pb->setText("Открыть клапан O2");
        pb->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                          "border-radius: 20px;");
        font = pb->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb->setFont(font);
        connect(pb, SIGNAL(clicked()), this, SLOT(on_pushPB_clicked()));

        /*
    if (button->fontMetrics().elidedText(button->text(), Qt::ElideMiddle, button->geometry().width()) != button->text())
    {
        // Текст не помещается.
    }
    */

        //    pb->show();
        pb->hide();


        pb1 = new QPushButton(this);
        pb1->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pb1->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb1->setFont(font);
        pb1->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*2+this->height()/6,this->width()/12*BSCALE*10,this->height()/6);
        pb1->setText("СБРОС");
        connect(pb1, SIGNAL(clicked()), this, SLOT(on_pushPB1_clicked()));
        pb1->show();
        //   pb1->hide();

        pb2 = new QPushButton(this);
        pb2->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2,this->width()/12*BSCALE*10,this->height()/6);
        pb2->setText("Заводские Настройки");
        font = pb2->font();
        font.setPointSize(FSCALE*25);
        pb2->setFont(font);
        connect(pb2, SIGNAL(clicked()), this, SLOT(on_pushPB2_clicked()));
        //    pb2->show();
        pb2->hide();


        pbE = new QPushButton(this);
        pbE->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pbE->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pbE->setFont(font);
        pbE->setText("ВЕРНУТЬСЯ");
        pbE->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*4+(this->height()/6)*3-pbEYminus-20,
                         this->width()/12*BSCALE*10,this->height()/6);
        connect(pbE, SIGNAL(clicked()), this, SLOT(on_pushPBE_clicked()));
        pbE->show();

    }
    //================================= НАСТРОЙКИ ===============================================
    else if(numW==2)// wtuning
    {
        pb = new QPushButton(this);

        //    pb->setStyleSheet(QString("color: white;"));// Цвет Текста
        this->pb->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE,
                              this->width()/12*BSCALE*10,this->height()/6);
        pb->setText("Настроить по\nCO2");
        pb->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                          "border-radius: 20px;");
        font = pb->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb->setFont(font);
        connect(pb, SIGNAL(clicked()), this, SLOT(on_pushPB_clicked()));
        pb->show();


        pb1 = new QPushButton(this);
        pb1->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*2+this->height()/6,
                         this->width()/12*BSCALE*10,this->height()/6);
        pb1->setText("Настроить по\nO2");
        pb1->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pb1->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb1->setFont(font);
        connect(pb1, SIGNAL(clicked()), this, SLOT(on_pushPB1_clicked()));
        pb1->show();
        //    pb1->hide();

        pb2 = new QPushButton(this);
        pb2->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2,
                         this->width()/12*BSCALE*10,this->height()/6);
        pb2->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        pb2->setText("Авто CO2");
        font = pb2->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb2->setFont(font);
        connect(pb2, SIGNAL(clicked()), this, SLOT(on_pushPB2_clicked()));
        //    pb2->show();
        pb2->hide();

        pb3 = new QPushButton(this);
        //    pb3->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2+this->height()/6/2+20,
        pb3->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2,
                         this->width()/12*BSCALE*10,this->height()/6);
        pb3->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        pb3->setText("Авто O2");
        font = pb3->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb3->setFont(font);
        connect(pb3, SIGNAL(clicked()), this, SLOT(on_pushPB3_clicked()));
        //    pb2->show();
        pb3->hide();

        pbE = new QPushButton(this);
        pbE->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        font = pbE->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pbE->setFont(font);
        pbE->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*4+(this->height()/6)*3-pbEYminus,
                         this->width()/12*BSCALE*10,this->height()/6);
        pbE->setText("ВЕРНУТЬСЯ");
        connect(pbE, SIGNAL(clicked()), this, SLOT(on_pushPBE_clicked()));
        pbE->show();

        pb4 = new QPushButton(this);
        //    pb3->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2+this->height()/6/2+20,
        pb4->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2,
                         this->width()/12*BSCALE*10,this->height()/6);
        pb4->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        pb4->setText("Калибровка\nO2");
        font = pb4->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb4->setFont(font);
        connect(pb4, SIGNAL(clicked()), this, SLOT(on_pushPB4_clicked()));
        pb4->show();
        //    pb4->hide();

        pb5 = new QPushButton(this);
        //    pb3->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE*3+this->height()/6*2+this->height()/6/2+20,
        pb5->setGeometry(width()/12*BSCALE,this->height()/12*BSCALE,
                         this->width()/12*BSCALE*10,this->height()/6);
        pb5->setStyleSheet("background-color: rgb(255,255, 0);   border-style: inset;border: 3px solid grey;"
                           "border-radius: 20px;");
        pb5->setText("СЧИТАТЬ");
        font = pb5->font();
        font.setPointSize(FSCALE*25);
        font.setBold(true);
        pb5->setFont(font);
        connect(pb5, SIGNAL(clicked()), this, SLOT(on_pushPB5_clicked()));
        //    pb5->show();
        pb5->hide();


    }


}

//==============================================
void border::on_pushPB_clicked()
{
    qDebug() <<"+++++++ on_pushPB_clicked +++++++++";
    if(numW==0)
    {
//        // qDebug() <<"+++++++ on_pushPB_clicked +++++++++";
        emit workRestart(2);
    }
    else if(numW==1)
    {
//        // qDebug() <<"+++++++ on_pushPB_clicked +++++++++";
        //    emit test();
    }
    else if(numW==2)
    {
        // qDebug() <<"+++++++ on_pushPB_clicked +++++++++";
        pb4->hide();
        pb->hide();
        pb1->hide();
        emit settunCO2(1);
    }

}
//==============================================
void border::on_pushPB1_clicked()
{
    qDebug() <<"+++++++ on_pushPB1_clicked +++++++++";
    if(numW==0)
    {
        // qDebug() <<"+++++++ on_pushPB1_clicked +++++++++";
        emit workRestart(1);
    }
    else if(numW==1)
    {
        if(trigKl==0)
        {
            pb1->setText("ОСТАНОВИТЬ");
            emit opclKl3(1);trigKl=1;
        }
        else if(trigKl==1)
        {
            pb1->setText("СБРОС");
            emit opclKl3(0);trigKl=0;
        }

    }
    else if(numW==2)
    {
        // qDebug() <<"+++++++ numW==2_clicked +++++++++";
        pb4->hide();
        pb->hide();
        pb1->hide();
        emit settunO2(1);
    }
}
//==============================================
void border::on_pushPB2_clicked()
{
    qDebug() <<"+++++++ on_pushPB2_clicked +++++++++";
    if(numW==2)
    {
        // qDebug() <<"+++++++ on_pushPB2_clicked +++++++++";
        pb2->hide();
        emit settunCO2(0);
    }

    else if(numW==0)
    {

        emit workFactorySet(0);

    }
}
//==============================================
void border::on_pushPB3_clicked()
{
    qDebug() <<"+++++++ on_pushPB3_clicked +++++++++";
    if(numW==2)
    {
        // qDebug() <<"+++++++ on_pushPB3_clicked +++++++++";
        pb3->hide();
        emit settunO2(0);
    }

}
//===================================== Калибровка O2 =========
void border::on_pushPB4_clicked() //начать калибровку по О2
{
    qDebug() <<"+++++++ numW==4_clicked +++++++++";
    if(numW==2)
    {

        pb->hide();
        pb1->hide();
        pb5->show();
        emit calibrO2(1);
    }

}
//==============================================
void border::on_pushPB5_clicked() // считать значения О2 при калибровке по О2
{
    qDebug() <<"+++++++on_pushPB5_clicked+++++++++";
    if(numW==2)
    {
        // qDebug() <<"+++++++ numW==5_clicked +++++++++";
        pb->hide();
        pb1->hide();
        pb5->show();
        emit calibrO2(0);
    }

    /*
    if(trigKl4==0)
    {
        pb5->setText("Закрыть\nКлапан");
        trigKl4=1;
        emit opclKl4(1);
    }
    else if(trigKl4==1)
    {
        pb5->setText("Открыть\nКлапан");
        trigKl4=0;
        emit opclKl4(0);
    }
*/
}
//==============================================
void border::on_pushPBE_clicked()
{
    qDebug() <<"+++++++ on_pushPBE_clicked +++++++++";
    if(numW==0)
    {
        emit workEND();
    }
    else if(numW==1)
    {

        //____________________________
        msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("ПРЕДУПРЕЖДЕНИЕ");
        msgBox->setStyleSheet("background-color: white");
        font = msgBox->font();
        font.setPointSize(FSCALE*40);
        font.setBold(true);
        msgBox->setFont(font);
        msgBox->setText("Внимание!");
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
        //  QTimer::singleShot(5000, msgBox, SLOT(close()));
        //timerMesB->singleShot(5000, msgBox, SLOT(close()));
        timerMesB->start(10000);
        int res = msgBox->exec();
        //_______________________________

        if (res == QMessageBox::Ok)
        {
            timerMesB->stop();
            // qDebug() <<"+++++++ on_pushPBE_clicked +++++++++";
            emit workEND();
            this->close();
            this->deleteLater();
        }
        else
        {
            timerMesB->stop();
            //                    ui->progressBar->setValue(0);
            //                    ptimer->start(3000);

        }

    }
    else
    {
        // qDebug() <<"+++++++ on_pushPBE_clicked +++++++++";
        emit workEND();
        this->close();
        this->deleteLater();
    }
}
//========================================================================================================================
void border::timMesB(void)
{
    qDebug() <<"+++++++ border::timMesB +++++++++";
    timerMesB->stop();
    msgBox->close();
    //    ui->progressBar->setValue(0);
    //    ptimer->start(3000);


}
//========================================================================================================================
