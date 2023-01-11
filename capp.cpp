#include "capp.h"

CApp::CApp()
{
    _capteurPassage = new CCapteurPassage();
}

void CApp::calculateTime()
{
    _deltaTms = _dt1.msecsTo(_dt2);
    _deltaTm = _deltaTms / 60000;
    _deltaTs = (_deltaTms % 60000) / 1000;
    _deltaTms = (_deltaTms % 60000) % 1000;
    QString resultat = QString::number(_deltaTm) + " : " + QString::number(_deltaTs) +" : " + QString::number(_deltaTms);
}

void CApp::on_timerStop()
{
    _dt2 = QDateTime::currentDateTime();
    disconnect(_capteurPassage, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
    calculateTime();

}

void CApp::on_timerStart()
{
    connect(_capteurPassage, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
    _dt1 = QDateTime::currentDateTime();
}
