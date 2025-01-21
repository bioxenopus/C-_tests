#include "voen.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
//#include <wiringPi.h> Включить!!
#include <QDebug>
//void myInterrupt0 (void);
unsigned char trEn;
//======================================================
voen::voen(QObject *parent) : QObject(parent)
{
//#include "finam.h" - Нужен ресурс звука
    trigOu=0; trigPLAY=0; trEn=0;
pinNum[0]=21;
pinNum[1]=22;pinNum[2]=26;pinNum[3]=23;pinNum[4]=27;pinNum[5]=24;pinNum[6]=28;
    /*pl = new QMediaPlayer;
    audio_output = new QAudioOutput;
    pl->setAudioOutput(audio_output);
    audio_output->setVolume(30);
     connect(pl,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,
             SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
     //connect(pl, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error),   Непонятная штука...
         //[=](QMediaPlayer::Error error){ qDebug()<<"Error="<<pl->errorString(); });*/
trEn=1;
}
//=======================================================
void voen::voiOu(void)
{
numFl=1;
if((numFl > 0) && (numFl < 32) )
 {
if(trigPLAY==1)
    {
     qDebug() << "voen.cpp : Play "<< trigPLAY<<numFl;
    pl->setSource(QUrl::fromLocalFile(QDir::toNativeSeparators("/home/pi/Gdata/Tada.mp3")));
    pl->play();
     }
if(trigPLAY==3)
    {
//m_tim->stop();
//    pl->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(fiNam[0])));
    pl->setSource(QUrl::fromLocalFile(QDir::toNativeSeparators("/home/pi/Gdata/Tada.wav")));
    pl->play();
    }
 }
else
 {
    trigPLAY=0;
 }

}
//=======================================================
void voen::on_alarm()
{
     qDebug()<<"On_ALA"<<  trEn<<trigPLAY;
if(trEn)
    {
     trEn=0;
     trigOu=1;
    }
if(trigOu && (trigPLAY==0))
    {
    trigOu=0;trigPLAY=1;
    voiOu();
    }
else if(trigPLAY==2)
    {
    trigPLAY=3;
    voiOu();
    }
else
    {
    }
}
//=======================================================
void voen::mediaStatusChanged(QMediaPlayer::MediaStatus state)
{
    if(state==QMediaPlayer::EndOfMedia)
    {
    if(trigPLAY==1){trigPLAY=2;}
    else if(trigPLAY==3){trigPLAY=0;trEn=1;}
       // qDebug()<<"Audio played"<<  trigPLAY;
//        m_tim->start(500);
    }
}
//=======================================================

