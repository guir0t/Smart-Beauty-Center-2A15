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
#include "ui_client.h"

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
void clientt::setadresse(QString nationalite){this->adresse=adresse;}
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
           query.prepare(" UPDATE client set cin=:cin ,nom=:nom,prenom=:prenom, tel=:tel,adresse=:adresse");
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
void  clientt::telechargerPDF(QString val){


                     QPdfWriter pdf("C:\\Users\\achra\\Desktop\\exporter\\exporter.pdf");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"JOUEUR");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",11));
                         painter.drawText(200,3300,"ID");
                         painter.drawText(1300,3300,"NOM");
                         painter.drawText(2200,3300,"PRENOM");
                         painter.drawText(3200,3300,"ANNEES_NAISSANCE");
                         painter.drawText(5300,3300,"NATIONALITE");
                         painter.drawText(6700,3300,"TYPE_SPORT");
                         painter.drawText(7000,3300,"EQUIPE");
                         painter.drawText(7500,3300,"SCORE");

                         QSqlQuery query;
                         query.prepare("select * from joueurs where id='"+val+"'");
                         //query.prepare("select * from joueurs");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(2).toString());
                             painter.drawText(2200,i,query.value(3).toString());
                             painter.drawText(3200,i,query.value(1).toString());
                             painter.drawText(5300,i,query.value(4).toString());
                             painter.drawText(6700,i,query.value(5).toString());
                             painter.drawText(7000,i,query.value(6).toString());
                             painter.drawText(7500,i,query.value(7).toString());


                            i = i + 500;
                         }}
