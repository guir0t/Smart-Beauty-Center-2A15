#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include "Arduino.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include<QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_id_fournisseur->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_numero->setValidator(new QIntValidator(0, 99999999, this));
   ui->tab_fournisseur->setModel(f.afficher());

   ui->setupUi(this);
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


void MainWindow::on_pb_chercher_clicked()
{
    Fournisseur f;

        QString choix=ui->comboBox_chercher->currentText();



        if (choix=="nom")

        {

           QString nom = ui->le_chercher->text();

            ui->tab_fournisseur_chercher->setModel(f.chercher_nom(nom));

        }

        if (choix=="contract")

        {

            QString contract = ui->le_chercher->text();

            ui->tab_fournisseur_chercher->setModel(f.chercher_contract(contract));

        }

        if (choix=="cin")

        {

            QString cin = ui->le_chercher->text();

            ui->tab_fournisseur_chercher->setModel(f.chercher_cin(cin));
        }


}

void MainWindow::on_pb_trie_c_clicked()
{
    Fournisseur F;
    QString choix=ui->comboBox_trie->currentText();
    if (choix=="ID")
    {
        ui->tab_fournisseur_chercher->setModel(F.tri_idcroissant());
        ui->tab_fournisseur_chercher->setModel(F.afficher());
        bool test=F.tri_idcroissant();
        QMessageBox msgBox ;
        if (test)
        {
                ui->tab_fournisseur_chercher->setModel(F.tri_idcroissant());
                msgBox.setText("trie avec succes");}


           else
                 msgBox.setText("echec du trie ");
            msgBox.exec();}

    if (choix=="CIN")
    {
        ui->tab_fournisseur_chercher->setModel(F.tri_cincroissant());
        ui->tab_fournisseur_chercher->setModel(F.afficher());
        bool test=F.tri_cincroissant();
        QMessageBox msgBox ;
        if (test)
        {
            ui->tab_fournisseur_chercher->setModel(F.tri_cincroissant());
            msgBox.setText("trie avec succes");
                }

           else
                 msgBox.setText("echec du trie ");
            msgBox.exec();}


    if (choix=="NUMERO")
    {
        ui->tab_fournisseur_chercher->setModel(F.tri_numcroissant());
        ui->tab_fournisseur_chercher->setModel(F.afficher());
        bool test=F.tri_numcroissant();
        QMessageBox msgBox ;
        if (test)
        {
                ui->tab_fournisseur_chercher->setModel(F.tri_numcroissant());
                msgBox.setText("trie avec succes");
                }

           else
                 msgBox.setText("echec du trie ");
            msgBox.exec();}

}


void MainWindow::on_pb_trie_dec_clicked()
{
    Fournisseur F;
    QString choix=ui->comboBox_trie->currentText();
    if (choix=="ID")
    {
        ui->tab_fournisseur_chercher->setModel(F.tri_iddecroissant());
        ui->tab_fournisseur_chercher->setModel(F.afficher());
        bool test=F.tri_iddecroissant();
        QMessageBox msgBox ;
        if (test)
        {
                ui->tab_fournisseur_chercher->setModel(F.tri_iddecroissant());
                msgBox.setText("trie avec succes");}


           else
                 msgBox.setText("echec du trie ");
            msgBox.exec();}

    if (choix=="CIN")
    {
        ui->tab_fournisseur_chercher->setModel(F.tri_cindecroissant());
        ui->tab_fournisseur_chercher->setModel(F.afficher());
        bool test=F.tri_cindecroissant();
        QMessageBox msgBox ;
        if (test)
        {
            ui->tab_fournisseur_chercher->setModel(F.tri_cindecroissant());
            msgBox.setText("trie avec succes");
                }

           else
                 msgBox.setText("echec du trie ");
            msgBox.exec();}


    if (choix=="NUMERO")
    {
        ui->tab_fournisseur_chercher->setModel(F.tri_numdecroissant());
        ui->tab_fournisseur_chercher->setModel(F.afficher());
        bool test=F.tri_numdecroissant();
        QMessageBox msgBox ;
        if (test)
        {
                ui->tab_fournisseur_chercher->setModel(F.tri_numdecroissant());
                msgBox.setText("trie avec succes");
                }

           else
                 msgBox.setText("echec du trie ");
            msgBox.exec();}
}

void MainWindow::on_pb_PDF_clicked()
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tab_fournisseur->model()->rowCount();
                        const int columnCount = ui->tab_fournisseur->model()->columnCount();
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
                if (!ui->tab_fournisseur->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tab_fournisseur->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                for (int column = 0; column < columnCount; column++) {
                if (!ui->tab_fournisseur->isColumnHidden(column)) {
     QString data = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pb_txt_clicked()
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tab_fournisseur->model()->rowCount();
                        const int columnCount = ui->tab_fournisseur->model()->columnCount();
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
                if (!ui->tab_fournisseur->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tab_fournisseur->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                for (int column = 0; column < columnCount; column++) {
                if (!ui->tab_fournisseur->isColumnHidden(column)) {
     QString data = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, column)).toString().simplified();
         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
       }
       }
    out << "</tr>\n";
       }
    out <<  "</table> </center>\n"
            "</body>\n"
            "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en TXT", QString(), "*.txt");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".txt"); }

      QPrinter printer (QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName(fileName);

      QTextDocument doc;
     doc.setHtml(strStream);
     doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
      doc.print(&printer);
}

void MainWindow::on_tabWidget_currentChanged(int index)
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
                      amande->setName("num");
                      amande->setPen(QPen(QColor(0, 18, 110).lighter(130)));
                      amande->setBrush(QColor(0, 18, 110));

                       //axe des abscisses
                      QVector<double> ticks;
                      QVector<QString> labels;
                      f.statistique(&ticks,&labels);

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

                      // ajout des données  (statistiques de la quantité)//

                      QVector<double> PlaceData;
                      QSqlQuery q1("select NUM from FOURNISSEURS");
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

void MainWindow::on_pb_ard_on_clicked()
{
a.write_to_arduino("0");  //envoyer 0 à arduino
}

void MainWindow::on_pb_ard_1_clicked()
{
    a.write_to_arduino("1"); //envoyer 1 à arduino
}

void MainWindow::on_pb_ard_2_clicked()
{
    a.write_to_arduino("2");
}

void MainWindow::on_pb_ard_3_clicked()
{
    a.write_to_arduino("3");  //envoyer 3 à arduino
}
