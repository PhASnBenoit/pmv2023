#ifndef CCAPTEURPASSAGE_H
#define CCAPTEURPASSAGE_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDateTime>
#include "biblis/cgpio.h"

class CCapteurPassage : public QObject
{
    Q_OBJECT

public:
    explicit CCapteurPassage(int gpio = 15, QObject *parent = nullptr);

private:
    QFileSystemWatcher _file;
    CGpio *_in;

signals:
    void sig_coureurArrived();
    void sig_erreur(QString err);

public slots:
    void on_fileChanged(QString path);
    void on_erreur(QString err);
};

#endif // CCAPTEURPASSAGE_H

