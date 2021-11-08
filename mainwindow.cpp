#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "offre.h"
#include <QIntValidator>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Le_id->setValidator(new  QIntValidator(100, 999, this));
    ui->tab_offre->setModel(O.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()

{

    int id=ui->Le_id->text().toInt();
    int prix=ui->le_prix->text().toInt();
    int dispo=ui->le_disponibilite->text().toInt();
    QString designation=ui->le_designation->text();
    Offre O(id,prix,dispo,designation);
    bool test=O.ajouter();
    QMessageBox msgBox ;

    if (test)
           { msgBox.setText("ajout avec succes");
    ui->tab_offre->setModel(O.afficher());}

     else
            msgBox.setText("echec d'ajout ");
                msgBox.exec();


}

void MainWindow::on_pb_supp_clicked()
{
bool test=O.supprimer(ui->le_offresupp->text().toInt());
QMessageBox msgBox ;
if (test)
       {
    msgBox.setText("Supression avec succes");
    ui->tab_offre->setModel(O.afficher()); }
   else
        { msgBox.setText("echec du supression ");
     }
msgBox.exec();
}


void MainWindow::on_pb_modifier_clicked()
{
    O.setprix(ui->le_prix_2->text().toInt());
    O.setdispo(ui->le_disponibilite_2->text().toInt());
    O.setdesignation(ui->le_designation_2->text());
    O.setid(ui->Le_id_2->text().toInt());
    bool test=O.modifier();
    QMessageBox msgBox ;
    if (test)
           {
        msgBox.setText("Modification avec succes");
        ui->tab_offre->setModel(O.afficher()); }
       else
            { msgBox.setText("echec du modification ");
         }
    msgBox.exec();
}
