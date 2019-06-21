#include "adbprocess.h"
#include <QDebug>
#include <QFile>

QString AdbProcess::s_adbPath = "";

AdbProcess::AdbProcess(QObject *parent)
    : QProcess(parent)
{
    initSignals();
}

QString AdbProcess::getAdbPath()
{
    if (s_adbPath.isEmpty()) {
        s_adbPath = QString::fromLocal8Bit(qgetenv("QTSCRCPY_ADB_PATH"));
        QFile()
    }
    return s_adbPath;
}

void AdbProcess::initSignals()
{
    connect(this, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error){
        qDebug()<<error;
    });

    connect(this, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus exitStatus){
        qDebug()<<exitCode<<exitStatus;
    });

    connect(this, &QProcess::readyReadStandardError, this, [this](){
        qDebug()<<readAllStandardError();

    });

    connect(this, &QProcess::readyReadStandardOutput,this,[this](){
        qDebug()<<readAllStandardOutput();
    });

    connect(this,&QProcess::started,this,[this](){
        qDebug()<<"start!";
    });
}
