#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked()
{

      //recuperation des info dans les4 champs
    int cin=ui->lineEdit_id->text().toInt();
    float prix=ui->lineEdit_prix->text().toFloat();
    int quantite=ui->lineEdit_quantite->text().toInt();
    float produit_solde=ui->lineEdit_produit_solde->text().toFloat();
    produit P(cin,prix,quantite,produit_solde);

    bool test=P.ajouter();//inserer produit p dans la table
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué \n"
                                             "Click Cancel to exist ."),QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr(" not ok"),
                                 QObject::tr("ajout non effectué \n"
                                             "Click Cancel to exist ."),QMessageBox::Cancel);

    }


}
