#include "ccapteurpassage.h"

CCapteurPassage::CCapteurPassage(int gpio, QObject *parent) : QObject(parent)
{
    _in = new CGpio(this, gpio, IN);
    connect(_in, &CGpio::sigErreur, this, &CCapteurPassage::on_erreur);
    QString path("sys/class/gpio"+QString::number(gpio)+"/value");
    //QString path("/Users/juliensoler/Desktop/test.txt");
    _file.addPath(path);
    connect(&_file, &QFileSystemWatcher::fileChanged, this, &CCapteurPassage::sig_coureurArrived);

}

void CCapteurPassage::on_fileChanged(QString path)
{
    path.clear();
    emit sig_coureurArrived();
}

void CCapteurPassage::on_erreur(QString err)
{
    emit sig_erreur(err);
}
