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
ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
ui->lineEdit_quantite->setValidator(new QIntValidator(0,99999999,this));
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
     int id_fournisseur=ui->comboBox->currentText().toInt();

      produit P(cin,prix,produitsolde,quantite,id_fournisseur);

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
    int id_fournisseur=ui->comboBox->currentText().toInt();
        produit P(cin,prix,produitsolde,quantite,id_fournisseur);
      bool test=P.modifier(cin,prix,produitsolde,quantite,id_fournisseur);//modifier produit
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

void MainWindow::on_pushButton_tricroissant_clicked()
{


    produit P;
    ui->tableView->setModel(P.tri_prixcroissant());
    ui->tableView->setModel(P.afficher());
    bool test=P.tri_prixcroissant();//tri produit
    if (test)
    {

ui->tableView->setModel(P.tri_prixcroissant());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("tri croissante effectué \n"
                                             "Click Cancel to exist ."),QMessageBox::Cancel);

    }
    else
          QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                      QObject::tr("tri croissante failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_tridecroissant_clicked()
{
    produit P;
       ui->tableView->setModel(P.tri_prixdecroissant());
       ui->tableView->setModel(P.afficher());
       bool test=P.tri_prixdecroissant();//tri produit
       if (test)
       {

   ui->tableView->setModel(P.tri_prixdecroissant());
           QMessageBox::information(nullptr,QObject::tr("ok"),
                                    QObject::tr("tri decroissante  effectué \n"
                                                "Click Cancel to exist ."),QMessageBox::Cancel);

       }
       else
             QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                         QObject::tr("tri decroissante failed.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_combo_clicked()
{
    QSqlQuery query2("SELECT id_fournisseur FROM fournisseurs");
            while (query2.next())
                {
                  QString nsch=query2.value(0).toString();
                  ui->comboBox->addItem(nsch);
                  ui->comboBox->setEditText(nsch);
                }
}

