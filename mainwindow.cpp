#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include<QPainter>
#include <QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include"QFileDialog"
#include"QTextStream"
#include<QTextDocument>
#include"smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_client->setModel(c.afficher());
    ui->comboBox_2->setModel(c.afficher());
    ui->leid_rdv->setValidator(new QIntValidator(0,999999,this));
    ui->tab_rendezvous->setModel(R.afficher());
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setModel(tempProduit.afficher());
    ui->tab_offre->setModel(O.afficher());

ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
ui->lineEdit_quantite->setValidator(new QIntValidator(0,99999999,this));
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int tel=ui->le_tel->text().toInt();
    QString adresse=ui->le_adresse->text();

clientt c (cin,nom,prenom,tel,adresse);
bool test=c.ajouter();
if(test)
  {  QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("ajout effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
   { QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                QObject::tr("ajout non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

}





void MainWindow::on_pb_modifier_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int tel=ui->le_tel->text().toInt();
    QString adresse=ui->le_adresse->text();

        clientt c (cin,nom,prenom,tel,adresse);
        bool test=c.modifier(cin,nom,prenom,tel,adresse);
            if(test)
          {ui->tab_client->setModel(c.afficher());
          QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                            QObject::tr("invite modifiée.\n"
                                        "Click ok to exit."), QMessageBox::Ok);

          }
            else
                QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_afficher_clicked()
{
     ui->tab_client->setModel(c.afficher());


}

void MainWindow::on_pb_importer_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this ,tr("choisir"),"",tr("photos(*.png)"));
    if(QString::compare(filename, QString())!=0)
    {
        QImage photo;
        bool valid=photo.load(filename);
        if(valid)
        {   photo=photo.scaledToWidth(ui->label_9->width(), Qt::SmoothTransformation);
            ui->label_9->setPixmap(QPixmap::fromImage(photo));
        }
        else
        {
        //error
        }
    }
}

void MainWindow::on_pb_supprimer_clicked()
{

    int cin=ui->le_cin->text().toInt();
    bool test=c.supprimer(cin);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("suppression effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else
          { QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("suppression non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }

}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
    int cin = ui->comboBox_2->currentText().toInt();
         QString cin_string= QString::number(cin);
                QSqlQuery query;
                query.prepare("select * from client where cin='"+cin_string+"'");

                if(query.exec()){

                    while(query.next())
                    {

                   ui->le_cin->setText(query.value(0).toString());
                    ui->le_nom->setText(query.value(1).toString());
                    ui->le_prenom->setText(query.value(2).toString());
                    ui->le_tel->setText(query.value(3).toString());
                    ui->le_adresse->setText(query.value(4).toString());
               }
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr(" echoué"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_trier_prenom_clicked()
{
  ui->tab_client->setModel(c.trierprenom());
}

void MainWindow::on_trier_annees_clicked()
{
ui->tab_client->setModel(c.trieradresse());
}

void MainWindow::on_tri_tel_clicked()
{
     ui->tab_client->setModel(c.triertel());
}

void MainWindow::on_export_pdf_clicked()
{
    c.telechargerPDF();
     QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);

}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    clientt c;

     QString rech = ui->lineEdit_3->text();
         c.recherche(ui->tab_client,rech);
         if (ui->lineEdit_3->text().isEmpty())
         {
             ui->tab_client->setModel(c.afficher());
         }

}

void MainWindow::on_tab_client_activated(const QModelIndex &index)
{
    clientt f;
      QString val=ui->tab_client->model()->data(index).toString();
      QSqlQuery query;
      query.prepare("select * from client where cin='"+val+"'");

      if(query.exec()){

          while(query.next())
          {

         ui->le_cin->setText(query.value(0).toString());
          ui->le_nom->setText(query.value(1).toString());
          ui->le_prenom->setText(query.value(2).toString());
          ui->le_tel->setText(query.value(3).toString());
          ui->le_adresse->setText(query.value(4).toString());


     }
      }
      else
          QMessageBox::critical(nullptr, QObject::tr(" echoué"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_stat_clicked()
{
    QChart* chart_bar = c.chart_pie();
    QChartView* chart_view_bar = new QChartView(chart_bar, ui->label_stat);
    chart_view_bar->setRenderHint(QPainter::Antialiasing);
    chart_view_bar->setMinimumSize(400,400);
    chart_view_bar->show();

}



void MainWindow::on_pb_ajouter_2_clicked()
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

void MainWindow::on_pb_supprimer_2_clicked()
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
        if (ui->comboBox_3->currentText()=="par ID")
        {
            choix=1;
            id=ui->lineEdit_id->text().toInt();
        }
        else if(ui->comboBox_3->currentText()=="par ID client")
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

void MainWindow::on_connecter_clicked()
    { QStackedWidget stackedWidget;
        connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));
        QString username=ui->lineEdit_username->text();
                QString password = ui->lineEdit_password->text();
                if(username == "achraf" && password == "achraf")
                { QMessageBox::information(this, "Login", "Username and password is correct");
               //connect(ui->MainWindow->page_3, SIGNAL(on_connecter_clicked()), this, SLOT(viewData));
                ui->stackedWidget->setCurrentIndex(1);
                }
                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                    else if(username == "ahmed" && password == "ahmed")
                { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(2);
                }
                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                        else if(username == "guira" && password == "guira")
                        { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(5);
                }
                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                            else if(username == "turki" && password == "turki")
                            { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(4);
                }
                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                else if(username == "hedi" && password == "hedi")
                                { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(3);
                }
                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                else if(username == "aziz" && password == "aziz")
                { QMessageBox::information(this, "Login", "Username and password is correct");
             ui->stackedWidget->setCurrentIndex(6);
                }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                            else { QMessageBox::warning(this,"Login", "Username and password is not correct"); }
    }


void MainWindow::on_pushButton_ajouter_clicked()
{
    //recuperation des info dans les4 champs
      int cin=ui->lineEdit_id_2->text().toInt();
      float prix=ui->lineEdit_prix->text().toFloat();
      int quantite=ui->lineEdit_quantite->text().toInt();
      float produitsolde=ui->lineEdit_produit_solde->text().toFloat();
     int id_fournisseur=ui->comboBox_4->currentText().toInt();
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
                  ui->comboBox_4->addItem(nsch);
                  ui->comboBox_4->setEditText(nsch);
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

void MainWindow::on_pushButton_5_clicked()
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

void MainWindow::on_tabWidget_2_currentChanged(int index)
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

void MainWindow::on_pushButton_4_clicked()
{
    produit p;
    ui->tableView->setModel(p.produitsplusdemande());
}
//offre

void MainWindow::on_pb_ajouter_3_clicked()
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

void MainWindow::on_triePB_clicked()
{
    Offre o;
    ui->tab_trier->setModel(o.trierprix());
    ui->tab_trier->setModel(o.afficher());
    bool test=o.trierprix();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("trie reussit");
                    ui->tab_trier->setModel(o.trierprix());
                }
                else
                    msgBox.setText("echec de trie");
                    msgBox.exec();
}


void MainWindow::on_triePB_2_clicked()
{
    Offre o;
    ui->tab_trier->setModel(o.trierdes());
    ui->tab_trier->setModel(o.afficher());
    bool test=o.trierdes();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("trie reussit");
                    ui->tab_trier->setModel(o.trierdes());
                }
                else
                    msgBox.setText("echec de trie");
                    msgBox.exec();
}

void MainWindow::on_pb_modifier_2_clicked()
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
        ui->tab_offre->setModel(O.afficher());
           }
       else
            {
                msgBox.setText("echec du modification ");
            }
    msgBox.exec();
}

void MainWindow::on_pb_recher_clicked()
{
    Offre o;
    {
        int id=ui->le_idrecher->text().toInt() ;
           if (id==NULL)
           {
               QMessageBox :: information (this,tr("Empty Filed"),
                       tr ("Please enter a Number."));
               return ;

           }
           else { ui->tab_recher->setModel(o.rechercher(id));}
    }
}

void MainWindow::on_pb_recher_2_clicked()
{
    Offre o;
          QString  designation=ui->le_idrecher_2->text();
           ui->tab_recher->setModel(o.chercher(designation));
}

void MainWindow::on_PDF_pb_clicked()
{
    QString strStream;
      QTextStream out(&strStream);

   const int rowCount = ui->tab_trier->model()->rowCount();
   const int columnCount = ui->tab_trier->model()->columnCount();
   out <<  "<html>\n"
           "<head>\n"
   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
   <<  QString("<title>%1</title>\n").arg("strTitle")
   <<  "</head>\n"
  "<body bgcolor=#ffffff link=#5000A0>\n"

  //     "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste Des Offres </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
   for (int column = 0; column < columnCount; column++)
   if (!ui->tab_trier->isColumnHidden(column))
       out << QString("<th>%1</th>").arg(ui->tab_trier->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

                                           // data table
           for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_trier->isColumnHidden(column)) {
     QString data = ui->tab_trier->model()->data(ui->tab_trier->model()->index(row, column)).toString().simplified();
     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                   }
                                               }
                      out << "</tr>\n";
                                           }
                            out <<  "</table> </center>\n"
                                    "</body>\n"
                                  "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}

void MainWindow::on_offr_PD_clicked()
{

    Offre o;
    ui->tab_offrepd->setModel(o.offre_pd());
}

void MainWindow::on_pb_send_clicked()
{
    QString objet=ui->Le_objet->text();
    QString mail=ui->Le_mail->text();
    QString contenu=ui->Le_cont->text();
    Smtp* smtp = new Smtp("kramtihedi85@gmail.com", "safiadiptox1999", "smtp.gmail.com", 465);
     connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
     smtp->sendMail("hedikramti85@gmail.com", mail , objet , contenu );
}
