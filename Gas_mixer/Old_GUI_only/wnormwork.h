#ifndef WNORMWORK_H
#define WNORMWORK_H

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
#include <QPainter>
#include <QProcess>
#include <QMessageBox>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>

#include "border.h"
#include "gmdata.h"
//#include "klapan.h"
#include "testtypes.h"

#define SETPRESU 2


class wnormwork : public QWidget
{
    Q_OBJECT
public:
    explicit wnormwork(QWidget *parent = nullptr,gmdata *d=0,klapan *k=0);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QPainter painter;

    void winInit(void);
    void ifErrr(void);
    QRect rect;
    int scrWidth; // ширина Экрана
    int scrHeight; // высота экрана
    int lw;
    border *bo;

    klapan *setKL;
    gmdata *gd;

    QLabel *lab1;
    QLabel *labCO2;
    QLabel *labCO2D; // Лейбл СО2 %
    QLabel *labO2;
    QLabel *labO2D; // Лейбл О2 %
    QLabel *labSCO2;
    QLabel *labSCO2Ust;
    QLabel *labSO2Ust;
    QLabel *labSCO2D;// Лейбл СО2 % установленное
    QLabel *labSO2;
    QLabel *labSO2D;// Лейбл О2 % установленное
    QLabel *labInCO2; //--
    QLabel *labInCO2D; //--
    QLabel *labInO2; //--
    QLabel *labInO2D; //--
    QLabel *labLE; //--
    QLabel *labRE;//--
    QLabel *labRI;//--
    QLabel *labNF;
    QLabel *labNFD; // Лейбл поток N2
    QLabel *labCo2F;
    QLabel *labCo2FD; // Лейбл поток CO2
    QLabel *labO2F;
    QLabel *labO2FD; // Лейбл потток Воздуха
    QLabel *labNP; // Лейбл давление N2
    QLabel *labCP;  // Лейбл давление CO2
    QLabel *labOP;  // Лейбл давление Воздуха
    QLabel *labGAS; //"Поток"
    QLabel *labGASD; // Лейбл поток Итоговый
    QLabel *labReP; //"Давление"
    QLabel *labRePD; // Лейбл Ресивер давление
    QLabel *labReP1; //"Давление"
    QLabel *labGAS1; //"Поток"
    QLabel *labReP2;//"Давление"
    QLabel *labOutP; // Лейбл итоговое давление
    QLabel *labErGasOut;
    QLabel *labErGasInp;
    QFont font;
    QProgressBar *prB; // Центральный прогресс бар
    QProgressBar *prBO; // Прогресс бар - выход
    QProgressBar *prIN; // Прогресс бар - вход N2
    QProgressBar *prIO; // Прогресс бар - вход воздух
    QProgressBar *prIC; // Прогресс бар - вход CO2
    QPalette palette;
    QString aa;


    int prBX;
    int prBY;
    int leftX;

    QMessageBox *msgBox;
    QTimer *ptimer;
//    QTimer *pptpTim;
    QTimer *timerMesB;
    unsigned char trigErr=1;
    unsigned char trigAllErr=0;
//    unsigned char pptpCoun=0;

private slots:
    void slotPtim(void);
    void winExit(void);
    void winTest(void);
    void winKl3(int ve);
    void timMesB(void);
//    void slotpptpTim(void);
signals:
    void workRestart(int);


public slots:
};

#endif // WNORMWORK_H
