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
    produit P(cin,prix,produit_solde,quantite);

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

/*void MainWindow::on_pushButton_4_clicked()
{
    produit pp;

    pp.setCin(ui->lineEdit_cin_supp->text().toInt());
    bool test=pp.supprimer(pp.getCin());
        if(test)
    {
            ui->tab_2->setModel(pp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("suppresion effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    QMessageBox::critical(nullptr, QObject::tr("echec"),
                QObject::tr("suprresion non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
*/
