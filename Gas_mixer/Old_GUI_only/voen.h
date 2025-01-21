#ifndef VOEN_H
#define VOEN_H

#include <QObject>
//#include <QtSerialPort/QtSerialPort>
#include <QProcess>
#include <QRect>
#include <QDir>
#include <QUrl>
#include <QTimer>
#include <QSoundEffect>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioFormat>


class voen : public QObject
{
    Q_OBJECT
public:
    explicit voen(QObject *parent = 0);

signals:
private slots:
//    void on_tick();
void mediaStatusChanged(QMediaPlayer::MediaStatus state);

private:
//    QSerialPort *sport;
    QByteArray  buf;
    unsigned int num;
    unsigned int pinNum[7];
    int i;
    unsigned char inp[1];
    unsigned char trigOu;
    unsigned char trigPLAY;
    unsigned char numFl;
        unsigned char dum;
    QString strX;
    QString strY;
    QProcess *_FFMPEG;
    QString _process;
    QStringList _paramList;
    QString fiNam[50];
    QTimer   *m_tim;
    QSoundEffect *so;
    QSoundEffect *soo;
    QMediaPlayer *pl;
    QAudioOutput* audio_output;
    void voiOu(void);

    int gpio [28] = {0,0,8,9,7,21,22,11,10,13,12,14,26,23,15,16,27, 0, 1,24,28,29, 3, 4, 5, 6,25, 2};
    //               0,1,2,3,4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27


    //    void readData();
public:
    void on_alarm();

public slots:
};

#endif // VOEN_H
