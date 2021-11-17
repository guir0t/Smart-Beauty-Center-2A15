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
    int id_client=ui->le_idclient->text().toInt();
     int id_offre=ui->le_idoffre->text().toInt();
    int jour=ui->lej->text().toInt();
    int mois=ui->lem->text().toInt();
    int annees=ui->lean->text().toInt();
    Rendezvous R (id_rdv,id_client,id_offre,jour,mois,annees);

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
    Rendezvous R1;
    R1.setid_rdv(ui->le_id_supp->text().toInt());
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
 int id_client=ui->lineEdit_id_c->text().toInt();
 int id_offre=ui->lineEdit_id_o->text().toInt();
 int jour=ui->lineEdit_j->text().toInt();
 int mois=ui->lineEdit_m->text().toInt();
 int annee=ui->lineEdit_a->text().toInt();

 Rendezvous R1(id_rdv,id_client,id_offre,jour,mois,annee);

  bool test;
  test= R1.modifier(id_rdv,id_client,id_offre,jour,mois,annee);
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

void MainWindow::on_pushButton_clicked()
{
    int choix=0;
    if (ui->comboBox->currentText()=="par ID")
    {
        choix=1;
    }
    else if(ui->comboBox->currentText()=="par ID client")
    {
        choix=2;
    }
    else choix=3;
    ui->tab_rendezvous->setModel(R.trier(choix));

}

void MainWindow::on_pushButton_2_clicked()
{
    int choix=0,id,id_client,id_offre,j,m,a;
    if (ui->comboBox_2->currentText()=="par ID")
    {
        choix=1;
        id=ui->lineEdit_id->text().toInt();
    }
    else if(ui->comboBox_2->currentText()=="par ID client")
    {
        choix=2;
        id_client=ui->lineEdit_id_c->text().toInt();
    }
    else
    {
        choix=3;
        id_offre=ui->lineEdit_id_o->text().toInt();
    }
    Rendezvous rdv(id,id_client,id_offre,j,m,a);
    ui->tab_rendezvous->setModel(rdv.rechercher(choix));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
        QTextCharFormat f=ui->calendarWidget->weekdayTextFormat(Qt::Saturday);

        R.calendrier(f,ui->calendarWidget);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (R.nbr_rdv()>0)
    {
        QString notif=QString::number(R.nbr_rdv())+" rendez-vous pour cette semaine.\n""Click Ok to exit.";
        QMessageBox::information(nullptr, QObject::tr("Alerte"),notif, QMessageBox::Ok);
    }
    else QMessageBox::information(nullptr, QObject::tr("Information"),"pas de rendez-vous pour cette semaine", QMessageBox::Ok);
}
