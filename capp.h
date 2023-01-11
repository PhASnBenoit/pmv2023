#ifndef CAPP_H
#define CAPP_H
#include <QMainWindow>
#include <QObject>
#include <QDateTime>
#include "ccapteurpassage.h"
#include <QString>


class CApp : public QObject
{
    Q_OBJECT
public:
    CApp();

signals:
    void sig_timerStart();
    void sig_timerStop();

public slots:
    void on_timerStart();
    void on_timerStop();

private:
    QDateTime _dt1;
    QDateTime _dt2;
    qint64 _deltaTm;
    qint64 _deltaTs;
    qint64 _deltaTms;
    CCapteurPassage *_capteurPassage;

    void calculateTime();
};

#endif // CAPP_H
