#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

ui->tableView->setModel(Etmp.afficher());
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
    float produitsolde=ui->lineEdit_produit_solde->text().toFloat();
    produit P(cin,prix,produitsolde,quantite);

    bool test=P.ajouter();//inserer produit p dans la table
    if (test)
    {
        ui->tableView->setModel(P.afficher());

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




void MainWindow::on_pushButton_supprimer_clicked()
{
    //recuperation du cin
       int cin=ui->lineEdit_cin_supp->text().toInt();produit P1;
       bool test=P1.supprimer(cin);
       ui->tableView->setModel(P1.afficher());


       if (test)
       {

           QMessageBox::information(nullptr,QObject::tr("ok"),
                                    QObject::tr("suppression effectué \n"
                                                "Click Cancel to exist ."),QMessageBox::Cancel);

       }
       else
             QMessageBox::critical(nullptr, QObject::tr("no"),
                         QObject::tr("Suppression failed.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pushButton_modifier_clicked()
{
    int cin=ui->lineEdit_id->text().toInt();
    float prix=ui->lineEdit_prix->text().toFloat();
    int quantite=ui->lineEdit_quantite->text().toInt();
    float produitsolde=ui->lineEdit_produit_solde->text().toFloat();
    produit P(cin,prix,produitsolde,quantite);
      bool test=P.modifier(cin,prix,produitsolde,quantite);//modifier employe
      if (test)
      {

  ui->tableView->setModel(P.afficher());
          QMessageBox::information(nullptr,QObject::tr("ok"),
                                   QObject::tr("Modification effectué \n"
                                               "Click Cancel to exist ."),QMessageBox::Cancel);

      }
      else
            QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                        QObject::tr("Modification failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
