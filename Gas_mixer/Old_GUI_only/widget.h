#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QDebug>
#include <QElapsedTimer>
#include <QScreen>
#include "border.h"
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "wnormwork.h"
#include "wtuning.h"
//#include "spi.h"
//#include "spidac.h"
//#include "klapan.h"
//#include "objnorwork.h"
//#include "objselgas.h"
#include "gmdata.h"
#include "initper.h"
#include "voen.h"
//#include "setdattim.h"
#include "testtypes.h" /// Disable


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    void winInit(void);
    QRect rect;
    int scrWidth; // ширина Экрана
    int scrHeight; // высота экрана
    int lw;
    unsigned char countTim=0;
    border *bo;
    QLabel *lab1;
    QLabel *labCO2;
    QLabel *labCO2D;
    QLabel *labCO2F;
    QLabel *labO2F;
    QLabel *labO2;
    QLabel *labO2D;
    QLabel *labFN2;
    QLabel *labFN2D;
    QLabel *labFN2F;
    QLabel *labMAXP;
    QLabel *labMAXPD;
    QLabel *labFLOW;
    QFont font;

    QProgressBar *progress_bar;
    QTimer *ptimer;
    QTimer *timerMesB;
    QTimer *pptpTim;

    wnormwork *wn;
    wtuning *wt;

    spi *datSpi; //не нужно
    spiDAC *wDAC;  //инициализация других
    klapan *setKL;
    objnorwork *obnw;
    objselgas *obsg;
    gmdata *gd;
    initPer *ind;
    voen *vo;
    setDatTim *tset;

    QString aa;
    QMessageBox *msgBox;
    unsigned char errGdatFile=0;
    int res;  int res1;
    unsigned char pptpCoun=0;


private slots:
    void slotPtim(void);
    void timMesB(void);
    void slotpptpTim(void);

public slots:
    void winExit(void);
    void winRestart(int a);
    void winFactorySet(int arg);
protected:
   virtual void keyPressEvent(QKeyEvent *event);
};

#endif // WIDGET_H
