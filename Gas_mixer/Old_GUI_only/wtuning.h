#ifndef WTUNING_H
#define WTUNING_H

#include <QWidget>
#include <QDebug>
#include <QElapsedTimer>
//#include <QDesktopWidget> устарело
#include <QApplication>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QProgressBar>
#include <QPalette>
#include <QLineEdit>
#include <QFont>
#include <QString>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QMessageBox>
#include "border.h"
#include "initper.h"

#include "gmdata.h"
/*#include "objselgas.h"
#include "klapan.h"
*/
#include "testtypes.h"


class wtuning : public QWidget
{
    Q_OBJECT

private:
    void winInit(void);
    klapan *setKL;

    QRect rect;
    int scrWidth; // ширина Экрана
    int scrHeight; // высота экрана
    int lw;
    border *bo;
    QTimer *ptimer;
    QFont font;
    /*
        QLabel *labFull;
        QLineEdit *linElabFullD;
        QLabel *labCO2;
        QDoubleSpinBox *linECO2D;
        QLabel *labO2;
        QDoubleSpinBox *linEO2D;
        QLabel *labNF;------------------------ N2-Расчетный поток
        QLabel *labNFD;
        QLabel *labNFR;----------------------------N2-Измеренный поток
        QLabel *labNFDR;
        QLabel *labCo2F;---------------------------CO2-Расчетный поток
        QLabel *labCo2FD;
        QLabel *labCo2FR;-------------------------CO2-Измеренный поток
        QLabel *labCo2FDR;
        QLabel *labO2F;----------------------------O2-Расчетный поток
        QLabel *labO2FD;
        QLabel *labO2FR;------------------------O2-Измеренный поток
        QLabel *labO2FDR;
        QLabel *labReP;---------------------------Давление в РЕСИВЕРЕ
        QLabel *labRePD;
        QLabel *labStat;--------------------------Статус программы
        QLabel *labStatD;
        QLabel *labO2M;-----------------------------O2-Измеренное значение
        QLabel *labO2MD;
        QLabel *labCO2M;---------------------------CO2-Измеренное значение
        QLabel *labCO2MD;
        QLabel *labCO2R;-------------------------CO2-Скорректированное значение
        QLabel *labCO2RD;
        QLabel *labO2R;----------------------------O2-Скорректированное значение
        QLabel *labO2RD;
        QLabel *labPT;----------------------------Уменьшить давление до
        QLabel *labPTD;
        */
    QLabel *labFull;
    QLineEdit *linElabFullD;
    QLabel *labCO2;
    QDoubleSpinBox *linECO2D;
    QLabel *labO2;
    QDoubleSpinBox *linEO2D;
    QLabel *labNF;
    QLabel *labNFD;
    QLabel *labNFR;
    QLabel *labNFDR;
    QLabel *labCo2F;
    QLabel *labCo2FD;
    QLabel *labCo2FR;
    QLabel *labCo2FDR;
    QLabel *labO2F;
    QLabel *labO2FD;
    QLabel *labO2FR;
    QLabel *labO2FDR;
    QLabel *labReP;
    QLabel *labRePD;
    QLabel *labStat;
    QLabel *labStatD;
    QLabel *labO2M;
    QLabel *labO2MD;
    QLabel *labCO2M;
    QLabel *labCO2MD;
    QLabel *labCO2R;
    QLabel *labCO2RD;
    QLabel *labO2R;
    QLabel *labO2RD;
    QLabel *labPT;
    QLabel *labPTD;
    QString aa;
    QString statText[10];

    gmdata *gd;
    objselgas *obsg;


    int prBX;
    int prBY;
    int leftX;
    unsigned char trigW;

    QDoubleSpinBox *dpb;
    QCheckBox *cb1;
    QCheckBox *cb2;

    initPer *inper;



    float coefficientO2;
    float defaultO2;
int countColibr=0;


public:
    explicit wtuning(QWidget *parent = nullptr, gmdata *d=0, objselgas *o=0, klapan *k=0);
    void winTe(void);
    unsigned char winRegim=0;

signals:
    void workRestart(int);

public slots:

private slots:
    void slotPtim(void);
    void winExit(void);
    void winTest(void);
    void winStartA(void);
    void winTunCO2(int );
    void winTunO2(int );
    void on_checkBox_cb1(int arg2);
    void on_checkBox_cb2(int arg3);
    void winCalibrO2(int);
    void winKl4(int ve);

};

#endif // WTUNING_H
