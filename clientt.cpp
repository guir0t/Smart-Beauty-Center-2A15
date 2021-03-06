#include "clientt.h"

#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
//#include <QIntValidator>
//#include <QSystemTrayIcon>
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlTableModel>
#include <QPagedPaintDevice>


//#include "ui_client.h"

clientt::clientt()
{
cin=0;
tel=0;

}
clientt::clientt(int cin,QString nom ,QString prenom,int tel,QString adresse)
{
   this->cin=cin;
   this->nom=nom;
   this->prenom=prenom;
   this->tel=tel;
   this->adresse=adresse;
}

int clientt::getcin(){return cin;}
QString clientt::getnom(){return nom;}
QString clientt::getprenom(){return prenom;}
int clientt::gettel(){return tel;}
QString clientt::getadresse(){return adresse;}
void clientt::setcin(int cin){this->cin=cin;}
void clientt::setnom(QString nom){this->nom=nom;}
void clientt::setprenom(QString prenom){this->prenom=prenom;}
void clientt::settel(int tel){this->tel=tel;}
void clientt::setadresse(QString adresse){this->adresse=adresse;}
bool clientt::ajouter()
{
  //bool test=false;
   QSqlQuery query;
   QString cin_string=QString::number(cin);
    QString tel_string=QString::number(tel);
         query.prepare("INSERT INTO client (cin,nom,prenom,tel,adresse) "
                       "VALUES (:cin,:nom,:prenom,:tel,:adresse)");
         query.bindValue(0, cin_string);
         query.bindValue(1,nom);
         query.bindValue(2, prenom);
         query.bindValue(3, tel_string);
         query.bindValue(4,adresse);
         return  query.exec();



}
QSqlQueryModel * clientt::afficher(){



    QSqlQueryModel *model = new QSqlQueryModel();
              model->setQuery("SELECT* FROM client");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));


        return model;

}
bool clientt::supprimer(int cin2)
{
 QSqlQuery query;
 QString res=QString::number(cin2);
 query.prepare("delete from client where cin= :cin");
 query.bindValue(":cin",res);
 return query.exec();
}
bool clientt::modifier(int cin,QString nom,QString prenom,int tel,QString adresse)
{
    QSqlQuery query;

         QString cin_string=QString::number(cin);
         QString tel_string= QString::number(tel);
           query.prepare(" UPDATE client set cin=:cin ,nom=:nom,prenom=:prenom, tel=:tel,adresse=:adresse where cin=:cin");
           query.bindValue(":cin",cin_string);
           query.bindValue(":nom",nom);
           query.bindValue(":prenom",prenom);
           query.bindValue(":tel",tel_string);
           query.bindValue(":adresse",adresse);

           return query.exec();
}
QSqlQueryModel * clientt::trierprenom()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY prenom");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    return model;
}
QSqlQueryModel * clientt::trieradresse()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY adresse");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    return model;
}
QSqlQueryModel * clientt::triertel()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY tel");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    return model;
}

void clientt::recherche(QTableView * table, QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
        //QString annees_string=QString::number(annees);
        QSqlQuery *query=new QSqlQuery;
        query->prepare("select * from client where adresse like '%"+rech+"%' or cin like '%"+rech+"%' or nom like '%"+rech+"%' ;");
        query->exec();
        model->setQuery(*query);
        table->setModel(model);
        table->show();
}
void  clientt::telechargerPDF(){


                     QPdfWriter pdf("C:\\Users\\achra\\Desktop\\eexport\\eexport.xlsx");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"GESTION DU CLIENT");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",11));
                         painter.drawText(200,3300,"CIN");
                         painter.drawText(1300,3300,"NOM");
                         painter.drawText(2200,3300,"PRENOM");
                         painter.drawText(3200,3300,"TEL");
                         painter.drawText(5300,3300,"ADRESSE");

                         QSqlQuery query;
                        // query.prepare("select * from client where cin='"+val+"'");
                         query.prepare("select * from client");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2200,i,query.value(2).toString());
                             painter.drawText(3200,i,query.value(3).toString());
                             painter.drawText(5300,i,query.value(4).toString());


                            i = i + 500;
                         }}





QChart* clientt::chart_bar()
{
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM CLIENT");
    q1.exec();

    q2.prepare("SELECT * FROM CLIENT WHERE adresse<=200");
    q2.exec();

    q3.prepare("SELECT * FROM CLIENT WHERE CIN<6000 AND CIN>200");
    q3.exec();

    q4.prepare("SELECT * FROM CLIENT WHERE CIN<=999999 AND CIN>6000");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

//     Assign names to the set of bars used
    QBarSet *set0 = new QBarSet("inf 3");
    QBarSet *set1 = new QBarSet("inf 10");
    QBarSet *set2 = new QBarSet("inf 20");

//     Assign values for each bar
    *set0 << c1;
    *set1 << c2;
    *set2 << c3;

//     Add all sets of data to the chart as a whole
//     1. Bar Chart
    QBarSeries *series = new QBarSeries();

//     2. Stacked bar chart
    series->append(set0);
    series->append(set1);
    series->append(set2);

//     Used to define the bar chart to display, title, legend
    QChart *chart = new QChart();

//     Add the chart
    chart->addSeries(series);

//     Adds categories to the axes
//     QBarCategoryAxis *axis = new QBarCategoryAxis();

//     1. Bar chart
//     chart->setAxisX(axis, series);

//    // Used to change the palette
//    QPalette pal = qApp->palette();

//    // Change the color around the chart widget and text
//    pal.setColor(QPalette::Window, QRgb(0xffffff));
//    pal.setColor(QPalette::WindowText, QRgb(0x404044));

//     Apply palette changes to the application
//    qApp->setPalette(pal);

    return chart;
}

QChart* clientt::chart_pie()
{
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM CLIENT");
    q1.exec();

    q2.prepare("SELECT * FROM CLIENT WHERE CIN<=9000000");
    q2.exec();

    q3.prepare("SELECT * FROM CLIENT WHERE CIN<=15000000 AND CIN>9000000");
    q3.exec();

    q4.prepare("SELECT * FROM CLIENT WHERE CIN<=91999999 AND CIN>15000000");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

//     Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("inf 3", c1);
    series->append("inf 10", c2);
    series->append("inf 20", c3);
//     Create the chart widget
    QChart *chart = new QChart();

//     Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();

    return chart;
}
