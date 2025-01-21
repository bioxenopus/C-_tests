#ifndef BORDER_H
#define BORDER_H

#include <QLabel>
#include <QtWidgets>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QPalette>
#include <QTimer>



class border : public QLabel
{
    Q_OBJECT

public:
    border(QWidget *parent=0,unsigned char nw=0,int w=0,int h=0);
    QPushButton *pb;
    QPushButton *pb1;
    QPushButton *pb2;
    QPushButton *pb3;
    QPushButton *pb4;
    QPushButton *pb5;
    QPushButton *pbE;
private:
    QFont font;
    unsigned char numW;
    unsigned char trigKl=0;
    unsigned char trigKl4=0;
    int pbEYminus=10;
    void initPB(void);
    QTimer *timerMesB;
    QMessageBox *msgBox;


QWidget *pa;
private slots:
void on_pushPB_clicked();
void on_pushPB1_clicked();
void on_pushPB2_clicked();
void on_pushPB3_clicked();
void on_pushPB4_clicked();
void on_pushPB5_clicked();


void on_pushPBE_clicked();
void timMesB(void);


signals:
void workEND(void);
void workRestart(int);
void test();
void startA();
void settunCO2(int);
void settunO2(int);
void opclKl3(int);
void opclKl4(int);
void calibrO2(int);
void workFactorySet(int);

};

#endif // BORDER_H
