#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QIntValidator>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_id_fournisseur->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_numero->setValidator(new QIntValidator(0, 99999999, this));
   ui->tab_fournisseur->setModel(f.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
   int cin = ui->le_cin->text().toInt();
   int numero = ui->le_numero->text().toInt();
   int id_fournisseur = ui->le_id_fournisseur->text().toInt();
   QString nom = ui->le_nom->text();
   QString prenom = ui->le_prenom->text();
   QString contract = ui->le_contract->text();
   QString adresse = ui->le_adresse->text();
   Fournisseur F(cin,numero,id_fournisseur,nom,prenom,contract,adresse);
   bool test=F.ajouter();
   QMessageBox msgBox ;
   if (test)
   {
           msgBox.setText("ajouter avec succes");
           ui->tab_fournisseur->setModel(f.afficher());}

      else
            msgBox.setText("echec du l'ajou ");
       msgBox.exec();

}

void MainWindow::on_pb_supprimer_clicked()
{
     Fournisseur F1;
    int id = ui->le_id_supp->text().toInt();
        bool test= F1.supprimer(id);
        QMessageBox msgBox ;
        if (test)
                {
                msgBox.setText("Supression avec succes");
                ui->tab_fournisseur->setModel(f.afficher());}
           else
                 msgBox.setText("echec du supression ");
            msgBox.exec();
    /*Fournisseur F1;F1.set_idfournisseur(ui->le_id_supp->text().toInt());
    bool test= F1.supprimer(F1.get_idfournisseur());
    QMessageBox msgBox ;
    if (test)
            {
            msgBox.setText("Supression avec succes");
            ui->tab_fournisseur->setModel(f.afficher());}
       else
             msgBox.setText("echec du supression ");
        msgBox.exec();*/
}

void MainWindow::on_pb_modifier_clicked()
{
    int cin = ui->le_cin_m->text().toInt();
    int numero = ui->le_numero_m->text().toInt();
    int id_fournisseur = ui->le_id_m->text().toInt();
    QString nom = ui->le_nom_m->text();
    QString prenom = ui->le_prenom_m->text();
    QString contract = ui->le_contract_m->text();
    QString adresse = ui->le_adresse_m->text();
    Fournisseur F(cin,numero,id_fournisseur,nom,prenom,contract,adresse);
    bool test=F.modifier();
       QMessageBox msgBox ;
       if(test)
      {

            ui->tab_fournisseur->setModel(f.afficher());
      QMessageBox::information(nullptr, QObject::tr("modifier "),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("modifier "),
                        QObject::tr("Modification non effectuée  \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
