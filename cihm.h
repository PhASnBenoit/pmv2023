#ifndef CIHM_H
#define CIHM_H

#include <QMainWindow>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include "clogindialog.h"
#include "capp.h"

//Include commandes système
#include <unistd.h>
#include <sys/reboot.h>
#include <sys/socket.h>
#include "ccapteurpassage.h"
//


QT_BEGIN_NAMESPACE
namespace Ui { class CIhm; }
QT_END_NAMESPACE

class CIhm : public QMainWindow
{
    Q_OBJECT

public:
    CIhm(QWidget *parent = nullptr);
    ~CIhm();

private slots:
    void on_pbPreparation_clicked();
    void on_pbAvm_clicked();
    void on_pbPret_clicked();
    void on_pbPartez_clicked();
    void on_pbStop_clicked();
    void on_pbStart_clicked();
    void on_exportCSV();
    void on_tableWidget_cellClicked(int row, int column);
    void on_testCapteurs();
    void on_reboot();
    void on_shutdown();
    void on_quitterApp();
    //void on_timerStart();

signals:
    void sig_timerStart();

public slots:
    //slots loginDialog
    void on_badPassword();

private:
    Ui::CIhm *ui;
    void idPage();
    void mdpPage();
    int cpt1;
    int cpt2;
    CLoginDialog *_loginDialog;
    CApp *_app;

};
#endif // CIHM_H
