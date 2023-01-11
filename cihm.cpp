#include "cihm.h"
#include "ui_cihm.h"

CIhm::CIhm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CIhm)
{
    ui->setupUi(this);

    //Tableau de valeurs en responsive
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //

    //loginDialog
    _loginDialog = new CLoginDialog();
    connect(_loginDialog,&CLoginDialog::sig_badPassword,this,&CIhm::on_badPassword);
    _loginDialog->exec();
    //

    //Instanciation de l'App
    _app = new CApp();
    //

    //Execution commandes système
    connect(ui->actionRedemarrage,&QAction::triggered,this,&CIhm::on_reboot);
    connect(ui->actionArreter, &QAction::triggered, this, &CIhm::on_shutdown);
    connect(ui->actionQuitter, &QAction::triggered, this, &CIhm::on_quitterApp);
    //Execution commandes outils
    connect(ui->actionExport_CSV, &QAction::triggered, this, &CIhm::on_exportCSV);
    connect(ui->actionTest_Capteur, &QAction::triggered, this, &CIhm::on_testCapteurs);
    //

    //Boutons au démarrage
    ui->pbPreparation->setDisabled(true);
    ui->pbAvm->setDisabled(true);
    ui->pbPret->setDisabled(true);
    ui->pbPartez->setDisabled(true);
    ui->pbStop->setDisabled(true);
    //


}



CIhm::~CIhm()
{
    delete _app;
    delete ui;
}


void CIhm::on_pbPreparation_clicked()
{
    ui->pbPret->setDisabled(true);
    ui->pbPartez->setDisabled(true);
    ui->pbAvm->setEnabled(true);
}


void CIhm::on_pbAvm_clicked()
{
    ui->pbPartez->setDisabled(true);
    ui->pbPret->setEnabled(true);
}


void CIhm::on_pbPret_clicked()
{
    ui->pbPartez->setEnabled(true);
}


void CIhm::on_pbPartez_clicked()
{
    ui->pbPreparation->setDisabled(true);
    ui->pbAvm->setDisabled(true);
    ui->pbPret->setDisabled(true);
    ui->pbPartez->setDisabled(true);
    ui->pbStop->setEnabled(true);//setDisabled a l'affichage des 2 temps

    connect(this,&CIhm::sig_timerStart,_app, &CApp::on_timerStart);
    emit sig_timerStart();

}


void CIhm::on_pbStop_clicked()
{
    ui->pbPreparation->setEnabled(true);
}


void CIhm::on_pbStart_clicked()
{
    if(ui->pbStart->text()=="START")
    {
        QMessageBox msgBox;
        msgBox.setText("Voulez-vous lancer une nouvelle session?");
        msgBox.setInformativeText("Le nom de la session ne pourra plus être modifié");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        int reponse = msgBox.exec();
        if(reponse == QMessageBox::No){}
        else
        {
            ui->pbStart->setText("STOP");
            ui->pbPreparation->setEnabled(true);
            ui->leNomSession->setReadOnly(true);
            //Start la session;
        }
     }//IF START

    else
    {
        QMessageBox msgBox;
        ui->actionExport_CSV->setEnabled(true);
        msgBox.setText("Voulez-vous arreter la session en cours?");
        msgBox.setInformativeText("Pensez à EXPORTER la session");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        int reponse = msgBox.exec();
        if(reponse == QMessageBox::No){}
        else
        {
            ui->pbStart->setText("START");
            ui->pbPreparation->setDisabled(true);
            ui->leNomSession->setReadOnly(false);
            //Stop la session;
        }
    }//IF STOP
}


void CIhm::on_exportCSV()
{
    ui->leNomSession->setReadOnly(false);
    QMessageBox msgBox;
    msgBox.setText("Export de la session au format CSV");
    msgBox.setInformativeText("Voulez-vous exporter la session?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int reponse = msgBox.exec();
    if(reponse == QMessageBox::No){}
    //else
        //Export en CSV
}


void CIhm::on_quitterApp()
{
     QMessageBox msgBox;
     msgBox.setText("Voulez-vous quitter l'application?");
     msgBox.setInformativeText("Pensez à STOPPER et EXPORTER la session");
     msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
     msgBox.setDefaultButton(QMessageBox::No);
     int reponse = msgBox.exec();
     if(reponse == QMessageBox::No){
     }else
         QCoreApplication::quit();
}


void CIhm::on_tableWidget_cellClicked(int row, int column)
{

}


void CIhm::on_testCapteurs()
{
    QMessageBox msgBox;
    msgBox.setText("Test du fonctionnement des capteurs");
    msgBox.setInformativeText("Les capteurs sont fonctionnel");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int reponse = msgBox.exec();
    if(reponse == QMessageBox::Cancel){}
}

void CIhm::on_reboot()
{
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous redémarrer l'appareil??");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int reponse = msgBox.exec();
    if(reponse == QMessageBox::No){}
    else
    {
    system("/usr/bin/systemctl reboot");
    }
}


void CIhm::on_shutdown()
{
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous éteindre l'appareil??");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int reponse = msgBox.exec();
    if(reponse == QMessageBox::No){}
    else
    {
    system("sudo shutdown -h now");
    }
}

void CIhm::on_badPassword()
{
    QMessageBox::critical(this,"ERREUR","Echec de la connexion après 3 tentatives.\nFermeture de l'application.");
    exit(EXIT_FAILURE);
}


