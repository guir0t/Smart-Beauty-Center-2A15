#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "offre.h"
#include <QIntValidator>
#include <QMessageBox>
#include"connection.h"
#include<QPainter>
#include <QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include"QFileDialog"
#include"QTextStream"
#include<QTextDocument>
#include"smtp.h"

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
        ui->tab_offre->setModel(O.afficher());
           }
       else
            {
                msgBox.setText("echec du modification ");
            }
    msgBox.exec();
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




void MainWindow::on_pb_send_clicked()

    {
    QString objet=ui->Le_objet->text();
    QString mail=ui->Le_mail->text();
    QString contenu=ui->Le_cont->text();
    Smtp* smtp = new Smtp("kramtihedi85@gmail.com", "safiadiptox1999", "smtp.gmail.com", 465);
     connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
     smtp->sendMail("hedikramti85@gmail.com", mail , objet , contenu );
    }


void MainWindow::on_pb_recher_2_clicked()
{
    Offre o;
          QString  designation=ui->le_idrecher_2->text();
           ui->tab_recher->setModel(o.chercher(designation));
}

void MainWindow::on_offr_PD_clicked()
{

    Offre o;
    ui->tab_offrepd->setModel(o.offre_pd());
}
