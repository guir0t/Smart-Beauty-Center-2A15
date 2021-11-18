#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QMessageBox>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(tempProduit.afficher());

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
        QString nom_produit=ui->lineEdit_nomproduit->text();
      produit P(cin,prix,produitsolde,quantite,id_fournisseur,nom_produit);

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
   QString nom_produit=ui->lineEdit_nomproduit->text();
   produit P(cin,prix,produitsolde,quantite,id_fournisseur,nom_produit);

   bool test=P.modifier(cin,prix,produitsolde,quantite,id_fournisseur,nom_produit);//modifier produit

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


void MainWindow::on_pushButton_tri_clicked()
{
     produit P;
     QString choix=ui->comboBox_tri->currentText();
     if (choix=="prix")
     {
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
     if (choix=="produitsolde")
     {
         ui->tableView->setModel(P.tri_produitsoldecroissant());
         ui->tableView->setModel(P.afficher());
         bool test=P.tri_produitsoldecroissant();//tri produit
         if (test)
         {

     ui->tableView->setModel(P.tri_produitsoldecroissant());
             QMessageBox::information(nullptr,QObject::tr("ok"),
                                      QObject::tr("tri croissante effectué \n"
                                                  "Click Cancel to exist ."),QMessageBox::Cancel);

         }
         else
               QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                           QObject::tr("tri croissante failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
     }
     if (choix=="quantite")
     {
         ui->tableView->setModel(P.tri_quantitecroissant());
         ui->tableView->setModel(P.afficher());
         bool test=P.tri_quantitecroissant();//tri produit
         if (test)
         {

     ui->tableView->setModel(P.tri_quantitecroissant());
             QMessageBox::information(nullptr,QObject::tr("ok"),
                                      QObject::tr("tri croissante effectué \n"
                                                  "Click Cancel to exist ."),QMessageBox::Cancel);

         }
         else
               QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                           QObject::tr("tri croissante failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
     }

}

void MainWindow::on_pushButton_trid_clicked()
{
    produit P;
    QString choix=ui->comboBox_trid->currentText();
    if (choix=="prix")
    {
        ui->tableView->setModel(P.tri_prixdecroissant());
        ui->tableView->setModel(P.afficher());
        bool test=P.tri_prixdecroissant();//tri produit
        if (test)
        {

    ui->tableView->setModel(P.tri_prixdecroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri decroissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri decroissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="produitsolde")
    {
        ui->tableView->setModel(P.tri_produitsoldedecroissant());
        ui->tableView->setModel(P.afficher());
        bool test=P.tri_produitsoldedecroissant();//tri produit
        if (test)
        {

    ui->tableView->setModel(P.tri_produitsoldedecroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri decroissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri decroissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="quantite")
    {
        ui->tableView->setModel(P.tri_quantitedecroissant());
        ui->tableView->setModel(P.afficher());
        bool test=P.tri_quantitedecroissant();//tri produit
        if (test)
        {

    ui->tableView->setModel(P.tri_quantitedecroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri decroissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri decroissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}





void MainWindow::on_pushButton_3_clicked()
{
    produit p;
    QString choix=ui->comboBox_chercher->currentText();

    if (choix=="id_produit")
    {
        QString cin = ui->lineEdit_rech->text();
        ui->tableView_2->setModel(p.rechercher(cin));
    }
    if (choix=="prix")
    {
        QString prix = ui->lineEdit_rech->text();
        ui->tableView_2->setModel(p.rechercherprix(prix));
    }
    if (choix=="quantite")
    {
        QString quantite = ui->lineEdit_rech->text();
        ui->tableView_2->setModel(p.rechercherquantite(quantite));
    }

    }


void MainWindow::on_tabWidget_currentChanged(int index)
{
    // background //
              QLinearGradient gradient(0, 0, 0, 400);
              gradient.setColorAt(0, QColor(198, 156, 109));
              gradient.setColorAt(0.38, QColor(237, 187, 130));
              gradient.setColorAt(1, QColor(255, 200, 138));
              ui->plot->setBackground(QBrush(gradient));

              QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
              amande->setAntialiased(false);
              amande->setStackingGap(1);
               //couleurs
              amande->setName("Repartition des produit selon nom de produit ");
              amande->setPen(QPen(QColor(247, 198, 132).lighter(150)));
              amande->setBrush(QColor(247, 198, 132));

               //axe des abscisses
              QVector<double> ticks;
              QVector<QString> labels;
              tempProduit.statistique(&ticks,&labels);

              QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
              textTicker->addTicks(ticks, labels);
              ui->plot->xAxis->setTicker(textTicker);
              ui->plot->xAxis->setTickLabelRotation(60);
              ui->plot->xAxis->setSubTicks(false);
              ui->plot->xAxis->setTickLength(0, 4);
              ui->plot->xAxis->setRange(0, 8);
              ui->plot->xAxis->setBasePen(QPen(Qt::black));
              ui->plot->xAxis->setTickPen(QPen(Qt::black));
              ui->plot->xAxis->grid()->setVisible(true);
              ui->plot->xAxis->grid()->setPen(QPen(QColor(242, 149, 102), 0, Qt::DotLine));
              ui->plot->xAxis->setTickLabelColor(Qt::black);
              ui->plot->xAxis->setLabelColor(Qt::black);

              // axe des ordonnées
              ui->plot->yAxis->setRange(0,10);
              ui->plot->yAxis->setPadding(5);
              ui->plot->yAxis->setLabel("quantite");
              ui->plot->yAxis->setBasePen(QPen(Qt::black));
              ui->plot->yAxis->setTickPen(QPen(Qt::black));
              ui->plot->yAxis->setSubTickPen(QPen(Qt::black));
              ui->plot->yAxis->grid()->setSubGridVisible(true);
              ui->plot->yAxis->setTickLabelColor(Qt::black);
              ui->plot->yAxis->setLabelColor(Qt::black);
              ui->plot->yAxis->grid()->setPen(QPen(QColor(242, 149, 102), 0, Qt::SolidLine));
              ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(242, 149, 102), 0, Qt::DotLine));

              // ajout des données  (statistiques de la quantité)//

              QVector<double> PlaceData;
              QSqlQuery q1("select quantite from produit");
              while (q1.next()) {
                            int  nbr_fautee = q1.value(0).toInt();
                            PlaceData<< nbr_fautee;
                              }
              amande->setData(ticks, PlaceData);

              ui->plot->legend->setVisible(true);
              ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
              ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
              ui->plot->legend->setBorderPen(Qt::NoPen);
              QFont legendFont = font();
              legendFont.setPointSize(5);
              ui->plot->legend->setFont(legendFont);
              ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pushButton_exp_clicked()
{
    QTableView *table;
                      table = ui->tableView;

                      QString filters("CSV files (.csv);;All files (.*)");
                      QString defaultFilter("CSV files (*.csv)");
                      QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                         filters, &defaultFilter);
                      QFile file(fileName);

                      QAbstractItemModel *model =  table->model();
                      if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                          QTextStream data(&file);
                          QStringList strList;
                          for (int i = 0; i < model->columnCount(); i++) {
                              if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                  strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                              else
                                  strList.append("");
                          }
                          data << strList.join(";") << "\n";
                          for (int i = 0; i < model->rowCount(); i++) {
                              strList.clear();
                              for (int j = 0; j < model->columnCount(); j++) {

                                  if (model->data(model->index(i, j)).toString().length() > 0)
                                      strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                  else
                                      strList.append("");
                              }
                              data << strList.join(";") + "\n";
                          }
                          file.close();
                          QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                                    QObject::tr("Export avec succes .\n"
                                                                "Click OK to exit."), QMessageBox::Ok);
                      }

}


void MainWindow::on_pushButton_clicked()
{
     produit p;
     ui->tableView->setModel(p.produitsplusdemande());
}
