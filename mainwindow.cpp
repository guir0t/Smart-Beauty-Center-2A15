#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QtSql/QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_2->setModel(Etmp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButton_ajouter_clicked()
{
    //recuperation des info
        int cin=ui->lineEdit_cin->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString prenom=ui->lineEdit_prenom->text();
        int tel=ui->lineEdit_tel->text().toInt();
        QString adresse=ui->lineEdit_adresse->text();

        client  C(cin,nom,prenom,tel,adresse);
        bool test=C.ajouter();
        if (test)
        {
    ui->tableView_2->setModel(C.afficher());

            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("ajout effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("ena jen lakhzena"),
                          QObject::tr("Ajout non effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_Supprimer_clicked()
{


    //recuperation du cin
        int cin=ui->lineEdit_cin->text().toInt();client c1;
        bool test=c1.supprimer(cin);
        ui->tableView_2->setModel(c1.afficher());

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
    int cin=ui->lineEdit_cin->text().toInt();client c1;
        QString nom=ui->lineEdit_nom->text();
        QString prenom=ui->lineEdit_prenom->text();
        int tel=ui->lineEdit_tel->text().toInt();
        QString adresse=ui->lineEdit_adresse->text();

        client C(cin,nom,prenom, tel, adresse );
        bool test=C.modifier(cin,nom,prenom,tel,adresse);//modifier
        if (test)
        {

    ui->tableView_2->setModel(c1.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("Modification effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("Modification failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}


