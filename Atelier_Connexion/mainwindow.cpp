#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande_vente.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QLineEdit>
#include <QPrinter>
#include <QTextDocument>
#include <QTextStream>
#include <QFileDialog>
#include <QSqlQuery>
 #include <QtWidgets>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id_commande->setValidator( new QIntValidator(0, 99999999, this));
    ui->le_jour->setValidator (new QIntValidator(1, 31, this));
    ui->le_mois->setValidator ( new QIntValidator(1, 12, this));
    ui->le_annee->setValidator ( new QIntValidator(2020, 2022, this));
    ui->le_idcl->setValidator ( new QIntValidator(0, 99999999, this));

    ui->tab_commande->setModel(cv.afficher());


    int ret=a.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).
}





MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pb_ajouter_clicked()
{
    int id_commande=ui->le_id_commande->text().toInt();
    int jour=ui->le_jour->text().toInt();
    int mois=ui->le_mois->text().toInt();
    int annee=ui->le_annee->text().toInt();
    int prix=ui->le_prix->text().toFloat();
    int id_client=ui->le_idcl->text().toInt();

    Commande_vente CV(id_commande,jour,mois,annee,prix,id_client);

     bool test=CV.ajouter();//inserer employé e dans la table
         if (test)
         {
     ui->tab_commande->setModel(CV.afficher());

             QMessageBox::information(nullptr,QObject::tr("ok"),
                                      QObject::tr("ajout effectué \n"
                                                  "Click Cancel to exist ."),QMessageBox::Cancel);

         }
         else
               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                           QObject::tr("connection failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);




     }



void MainWindow::on_pb_supprimer_clicked()
{


 Commande_vente cv; cv.setid_commande(ui->le_id_supp->text().toInt());
    bool test=cv.supprimer(cv.getid_commande());
    QMessageBox msgBox ;
     if (test)
       { msgBox.setText("supperssion avec succes.");

              ui->tab_commande->setModel(cv.afficher());
       }

        else

     msgBox.setText("Echec de supperssion");
     msgBox.exec();

}

void MainWindow::on_pb_modifier_clicked()
{
    int id_commande =ui->le_id_commande_modif ->text().toInt();

        int jour=ui->le_id_commande_modif->text().toInt();
        int mois=ui->le_mois_modif->text().toInt();
         int annee=ui->le_annee_modif->text().toInt();
         int id_client=ui->le_idcl_modif->text().toInt();
         int prix=ui->le_prix_modif->text().toInt();
        Commande_vente  cv(id_commande,jour,mois,annee,prix,id_client);

        bool test= cv.modifier();
        QMessageBox msgBox ;
        if(test)
       {

             ui->tab_commande->setModel(cv.afficher());
       QMessageBox::information(nullptr, QObject::tr("modifier "),
                         QObject::tr("Modification effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

       }
         else
             QMessageBox::critical(nullptr, QObject::tr("modifier "),
                         QObject::tr("Modification non effectuée  \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pb_chercher_clicked()
{
    Commande_vente cv;
    QString choix=ui->comboBox_chercher->currentText();

    if (choix=="id_commande")
    {
       QString id_commande = ui->le_chercher->text();
        ui->tab_chercher->setModel(cv.rechid_commande(id_commande));
    }
    if (choix=="id_client")
    {
        QString prix = ui->le_chercher->text();
        ui->tab_chercher->setModel(cv.rechprix(prix));
    }
    if (choix=="prix")
    {
        QString id_client = ui->le_chercher->text();
        ui->tab_chercher->setModel(cv.rechid_client(id_client));
    }

}

void MainWindow::on_pb_croissant_clicked()
{
     Commande_vente cv;
    QString choix=ui->comboBox->currentText();
    if (choix=="prix")
    {
        ui->tab_tri->setModel(cv.tri_prixcroissant());
        ui->tab_tri->setModel(cv.afficher());
        bool test=cv.tri_prixcroissant();//tri commande
        if (test)
        {

    ui->tab_tri->setModel(cv.tri_prixcroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri croissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri croissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="id_commande")
    {
        ui->tab_tri->setModel(cv.tri_id_commandecroissant());
        ui->tab_tri->setModel(cv.afficher());
        bool test=cv.tri_id_commandedecroissant();//tri id_commande
        if (test)
        {

    ui->tab_tri->setModel(cv.tri_id_commandecroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri croissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri croissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="id_client")
    {
        ui->tab_tri->setModel(cv.tri_id_clientcroissant());
        ui->tab_tri->setModel(cv.afficher());
        bool test=cv.tri_id_clientcroissant();//tri commande
        if (test)
        {

    ui->tab_tri->setModel(cv.tri_id_clientcroissant());
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


void MainWindow::on_pb_decroissant_clicked()
{
    Commande_vente cv;
    QString choix=ui->comboBox1->currentText();
    if (choix=="prix")
    {
        ui->tab_tri->setModel(cv.tri_prixdecroissant());
        ui->tab_tri->setModel(cv.afficher());
        bool test=cv.tri_prixdecroissant();//tri commande
        if (test)
        {

    ui->tab_tri->setModel(cv.tri_prixdecroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri decroissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri decroissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="id_commande")
    {
        ui->tab_tri->setModel(cv.tri_id_commandedecroissant());
        ui->tab_tri->setModel(cv.afficher());
        bool test=cv.tri_id_commandedecroissant();//tri commande
        if (test)
        {

    ui->tab_tri->setModel(cv.tri_id_commandedecroissant());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri decroissante effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri decroissante failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="id_client")
    {
        ui->tab_tri->setModel(cv.tri_id_clientdecroissant());
        ui->tab_tri->setModel(cv.afficher());
        bool test=cv.tri_id_clientdecroissant();//tri commande
        if (test)
        {

    ui->tab_tri->setModel(cv.tri_id_clientdecroissant());
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




void MainWindow::on_pb_word_clicked()
{
    QString strStream;
                            QTextStream out(&strStream);

                            const int rowCount = ui->tab_commande->model()->rowCount();
                            const int columnCount = ui->tab_commande->model()->columnCount();
                            out <<  "<html>\n"
                                    "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("strTitle")
                            <<  "</head>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"

                             //     "<align='right'> " << datefich << "</align>"
                   "<center> <H1>Liste Des Clients </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                   // headers
                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                    for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_commande->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->tab_commande->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                    for (int column = 0; column < columnCount; column++) {
                    if (!ui->tab_commande->isColumnHidden(column)) {
         QString data = ui->tab_commande->model()->data(ui->tab_commande->model()->index(row, column)).toString().simplified();
             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
           }
           }
        out << "</tr>\n";
           }
        out <<  "</table> </center>\n"
                "</body>\n"
                "</html>\n";
          QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en WORD", QString(), "*.docx");
                        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".docx"); }

          QPrinter printer (QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setPaperSize(QPrinter::A4);
          printer.setOutputFileName(fileName);

          QTextDocument doc;
         doc.setHtml(strStream);
         doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
          doc.print(&printer);

}

void MainWindow::on_tri_currentChanged(int index)
{
    QLinearGradient gradient(0, 0, 0, 400);

                          gradient.setColorAt(0, QColor(90, 90, 90));

                          gradient.setColorAt(0.38, QColor(105, 105, 105));

                          gradient.setColorAt(1, QColor(70, 70, 70));

                          ui->plot->setBackground(QBrush(gradient));



                          QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);

                          amande->setAntialiased(false);

                          amande->setStackingGap(1);

                           //couleurs

                          amande->setName("prix");

                          amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));

                          amande->setBrush(QColor(0, 168, 140));



                           //axe des abscisses

                          QVector<double> ticks;

                          QVector<QString> labels;

                          cv.statistique(&ticks,&labels);



                          QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

                          textTicker->addTicks(ticks, labels);

                          ui->plot->xAxis->setTicker(textTicker);

                          ui->plot->xAxis->setTickLabelRotation(60);

                          ui->plot->xAxis->setSubTicks(false);

                          ui->plot->xAxis->setTickLength(0, 4);

                          ui->plot->xAxis->setRange(0, 8);

                          ui->plot->xAxis->setBasePen(QPen(Qt::white));

                          ui->plot->xAxis->setTickPen(QPen(Qt::white));

                          ui->plot->xAxis->grid()->setVisible(true);

                          ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                          ui->plot->xAxis->setTickLabelColor(Qt::white);

                          ui->plot->xAxis->setLabelColor(Qt::white);



                          // axe des ordonnées

                          ui->plot->yAxis->setRange(0,10);

                          ui->plot->yAxis->setPadding(5);

                          ui->plot->yAxis->setLabel("Statistiques");

                          ui->plot->yAxis->setBasePen(QPen(Qt::white));

                          ui->plot->yAxis->setTickPen(QPen(Qt::white));

                          ui->plot->yAxis->setSubTickPen(QPen(Qt::white));

                          ui->plot->yAxis->grid()->setSubGridVisible(true);

                          ui->plot->yAxis->setTickLabelColor(Qt::white);

                          ui->plot->yAxis->setLabelColor(Qt::white);

                          ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));

                          ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));



                          // ajout des données  (statistiques des prix)//



                          QVector<double> PlaceData;

                          QSqlQuery q1("select PRIX from Commande_vente");

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

void MainWindow::on_pb_hist_clicked()
{
    QString strStream;
                            QTextStream out(&strStream);

                            const int rowCount = ui->tab_commande->model()->rowCount();
                            const int columnCount = ui->tab_commande->model()->columnCount();
                            out <<  "<html>\n"
                                    "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("strTitle")
                            <<  "</head>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"

                             //     "<align='right'> " << datefich << "</align>"
                   "<center> <H1>Liste Des Clients </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                   // headers
                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                    for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_commande->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->tab_commande->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                    for (int column = 0; column < columnCount; column++) {
                    if (!ui->tab_commande->isColumnHidden(column)) {
         QString data = ui->tab_commande->model()->data(ui->tab_commande->model()->index(row, column)).toString().simplified();
             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
           }
           }
        out << "</tr>\n";
           }
        out <<  "</table> </center>\n"
                "</body>\n"
                "</html>\n";
          QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en WORD", QString(), "*.docx");
                        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".docx"); }

          QPrinter printer (QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setPaperSize(QPrinter::A4);
          printer.setOutputFileName(fileName);

          QTextDocument doc;
         doc.setHtml(strStream);
         doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
          doc.print(&printer);

}

void MainWindow::on_pb_ard_0_clicked()
{
    a.write_to_arduino("0");  //envoyer 0 à arduino

}

void MainWindow::on_pb_ard_1_clicked()
{
    a.write_to_arduino("1");  //envoyer 0 à arduino

}

void MainWindow::on_pb_ard_2_clicked()
{
    a.write_to_arduino("2");  //envoyer 0 à arduino

}

void MainWindow::on_pb_ard_3_clicked()
{
    a.write_to_arduino("3");  //envoyer 0 à arduino

}

