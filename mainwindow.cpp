#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"rendezvous.h"
#include<QMessageBox>
#include<QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->leid_rdv->setValidator(new QIntValidator(0,999999,this));

    ui->tab_rendezvous->setModel(R.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id_rdv=ui->leid_rdv->text().toInt();
    //int id_client=ui->leid_client->text().toInt();
    int jour=ui->lej->text().toInt();
    int mois=ui->lem->text().toInt();
    int annees=ui->lean->text().toInt();
    Rendezvous R (id_rdv,jour,mois,annees);

    bool test=R.ajouter();
     MainWindow w;
     if(test)
     {ui->tab_rendezvous ->setModel(R.afficher());

         QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                     QObject::tr("ajout avec succes.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

    }
     else
         QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                     QObject::tr("echec d ajout.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
  }

void MainWindow::on_pb_supprimer_clicked()
{
    Rendezvous R1; R1.setid_rdv(ui->le_id_supp->text().toInt());
    bool test=R1.supprimer(R1.getid_rdv());

    QMessageBox msgBox;
    if(test)
        msgBox.setText("Suppression avec succes");
     else
        msgBox.setText("Echec de suppression");
        msgBox.exec();

}


void MainWindow::on_modifier_clicked()
{

    Rendezvous R;
  int id_rdv=ui->lineEdit_id->text().toInt();
 int jour=ui->lineEdit_j->text().toInt();
 int mois=ui->lineEdit_m->text().toInt();
 int annee=ui->lineEdit_a->text().toInt();

 Rendezvous R1(id_rdv,jour,mois,annee);

  bool test;
  test= R1.modifier(id_rdv,jour,mois,annee);
 if (test)

    {
     ui->tab_rendezvous->setModel(R1.afficher());
     QMessageBox::information(nullptr, QObject::tr("MODIFIER"),
                                   QObject::tr("MODIFICATION avec succes .\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);

     }
                   else
                       QMessageBox::critical(nullptr, QObject::tr("MODIFIER"),
                                   QObject::tr("UPDATE failed.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}
