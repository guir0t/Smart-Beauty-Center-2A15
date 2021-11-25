#include "fournisseur.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include <QDebug>
#include <QTextDocument>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QPainter>
#include <QPainterPath>
#include <QDateTime>



Fournisseur::Fournisseur()
{
cin=0;
numero=0;
id_fournisseur=0;
nom=" ";
prenom=" ";
contract=" ";
adresse=" ";
}

Fournisseur::Fournisseur(int cin, int numero,int id_fournisseur, QString prenom, QString nom, QString contract , QString adresse)
{
this->cin=cin ;
this->numero=numero;
this->id_fournisseur=id_fournisseur;
this->nom=nom;
this->prenom=prenom;
this->contract=contract;
this->adresse=adresse;
}
int Fournisseur::get_cin(){return cin;}
int Fournisseur::get_idfournisseur(){return id_fournisseur;}
int Fournisseur::get_numero(){return numero;}
QString Fournisseur::get_nom(){return nom ;}
QString Fournisseur::get_prenom(){return prenom ;}
QString Fournisseur::get_adresse(){return adresse ;}
QString Fournisseur::get_contract(){return contract ;}
void Fournisseur::set_cin (int cin) {this->cin=cin;}
void Fournisseur::set_numero(int numero) {this ->numero=numero;}
void Fournisseur::set_idfournisseur(int id_fournisseur) {this->id_fournisseur=id_fournisseur;}
void Fournisseur::get_nom(QString nom) {this->nom=nom;}
void Fournisseur::get_prenom (QString prenom) {this->prenom=prenom;}
void Fournisseur::get_contract(QString contract) {this->contract=contract;}
void Fournisseur::get_adresse(QString adresse) {this->adresse=adresse;}
bool Fournisseur::ajouter()
{

    QSqlQuery query;
    QString cin_string = QString::number(cin);
    QString numero_string = QString::number(numero);
    QString id_fournisseur_string = QString::number(id_fournisseur);
    query.prepare("INSERT INTO FOURNISSEURS (ID_FOURNISSEUR,NUM,CONTRAT,ADRESSE,NOM,PRENOM,CIN) "
                        "VALUES (:ID_FOURNISSEUR, :NUM, :CONTRAT, :ADRESSE , :NOM, :PRENOM , :CIN)");
          query.bindValue(":ID_FOURNISSEUR",id_fournisseur_string);
          query.bindValue(":NUM",numero_string);
          query.bindValue(":CONTRAT",contract);
          query.bindValue(":ADRESSE",adresse);
          query.bindValue(":NOM",nom);
          query.bindValue(":PRENOM",prenom);
          query.bindValue(":CIN",cin_string);
          return   query.exec();
}

QSqlQueryModel* Fournisseur::afficher()
{

      QSqlQueryModel *model = new QSqlQueryModel;

      model->setQuery("SELECT* FROM FOURNISSEURS");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("CONTRAT"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN"));



return model;
}

bool Fournisseur::supprimer(int id_fournisseur)
{


    QSqlQuery query;
          QString id_fournisseur_string = QString::number(id_fournisseur);
          query.prepare("Delete from FOURNISSEURS where ID_FOURNISSEUR=:id_fournisseur");
          query.bindValue(":id_fournisseur",id_fournisseur_string);

           return query.exec();


}
bool Fournisseur::modifier()
{  QSqlQuery query ;
QString id_string =QString::number(id_fournisseur);
QString cin_string = QString::number(cin);
QString numero_string = QString::number(numero);
query.prepare("Update  FOURNISSEURS set ID_FOURNISSEUR=:ID_FOURNISSEUR,NUM=:NUM,CONTRAT=:CONTRAT,NOM=:NOM,PRENOM=:PRENOM,CIN=:CIN,ADRESSE=:ADRESSE where ID_FOURNISSEUR=:ID_FOURNISSEUR ");
query.bindValue(":ID_FOURNISSEUR",id_string );
query.bindValue(":NUM",numero_string);
query.bindValue(":CONTRAT",contract);
query.bindValue(":NOM",nom);
query.bindValue(":PRENOM",prenom );
query.bindValue(":CIN",cin_string);
query.bindValue(":ADRESSE",adresse);
return    query.exec();
}
QSqlQueryModel * Fournisseur::chercher_nom(const QString &nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select * from FOURNISSEURS where (NOM LIKE '%"+nom+"%') ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("CONTRAT"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN"));
     return model;
}

QSqlQueryModel * Fournisseur::chercher_contract(const QString &contract)
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select * from FOURNISSEURS where (CONTRAT LIKE '%"+contract+"%') ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("CONTRAT"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN"));
     return model;
}

bool Fournisseur::chercher_cin(int x)
{
    QSqlQuery query;
    query.prepare("select * from FOURNISSEURS where CIN = :cin;");
    query.bindValue(":cin", x);
    return query.exec();
}

QSqlQueryModel * Fournisseur::chercher_cin(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from FOURNISSEURS where CIN ='"+a+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CONTRAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}

QSqlQueryModel * Fournisseur::tri_idcroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY ID_FOURNISSEUR ASC ");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FOURNISSEUR"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("CONTRAT"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRENOM"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("CIN"));
    return model;
}
QSqlQueryModel * Fournisseur::tri_cincroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY CIN ASC ");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FOURNISSEUR"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("CONTRAT"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRENOM"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("CIN"));
    return model;
}
QSqlQueryModel * Fournisseur::tri_numcroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY NUM ASC ");
            model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_FOURNISSEUR"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("NUM"));
            model->setHeaderData(2, Qt::Horizontal,QObject::tr("CONTRAT"));
            model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
            model->setHeaderData(4, Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(5, Qt::Horizontal,QObject::tr("PRENOM"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("CIN"));
    return model;
}
QSqlQueryModel * Fournisseur::tri_iddecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY ID_FOURNISSEUR DESC ");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FOURNISSEUR"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("CONTRAT"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRENOM"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("CIN"));
    return model;
}
QSqlQueryModel * Fournisseur::tri_cindecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY CIN DESC ");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FOURNISSEUR"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("CONTRAT"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRENOM"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("CIN"));
    return model;
}
QSqlQueryModel * Fournisseur::tri_numdecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY NUM DESC ");
            model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_FOURNISSEUR"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("NUM"));
            model->setHeaderData(2, Qt::Horizontal,QObject::tr("CONTRAT"));
            model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
            model->setHeaderData(4, Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(5, Qt::Horizontal,QObject::tr("PRENOM"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("CIN"));
    return model;
}

void Fournisseur::statistique(QVector<double>* ticks,QVector<QString> *labels)

{

    QSqlQuery q;

    int i=0;

    q.exec("select NUM from FOURNISSEURS");

    while (q.next())

    {

        QString identifiant = q.value(0).toString();

        i++;

        *ticks<<i;

        *labels <<identifiant;

    }

}

