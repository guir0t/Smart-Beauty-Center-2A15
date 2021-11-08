#include "offre.h"
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QtDebug>
#include <QObject>

Offre::Offre()
{
id_offre=0; prix=0; disponibilite=0; designation="";
}


Offre::Offre(int id,int prix,int dispo,QString designation)
{ this->id_offre=id ; this->prix=prix ; this->disponibilite=dispo ; this->designation=designation;}
int Offre::getid(){return id_offre;};
int Offre::getprix(){return prix; }
int Offre::getdispo(){return disponibilite;}
QString Offre::getdesignation(){return designation;}
void Offre::setid(int id){this->id_offre=id ;}
void Offre::setprix(int prix){this->prix=prix;}
void Offre::setdispo(int dispo){this->disponibilite=dispo;}
void Offre::setdesignation(QString designation){this->designation=designation;}

bool Offre::ajouter()
{

    QString id_string= QString::number(id_offre);
    QString prix_string= QString::number(prix);
    QString dispo_string= QString::number(disponibilite);
    QSqlQuery query;

          query.prepare("INSERT INTO offre (ID_OFFRE, PRIX   , DISPONIBILITE , DESIGNATION) "
                        "VALUES (:id, :prix, :dispo, :designation)");
          query.bindValue(":id", id_string);
          query.bindValue(":prix", prix_string);
          query.bindValue(":dispo", dispo_string);
          query.bindValue(":designation", designation);
           return query.exec();
}


bool Offre::supprimer(int id)
{


    QSqlQuery query;

          query.prepare("Delete from offre where id_offre=:id");
          query.bindValue(":id", id);

           return query.exec();


}
QSqlQueryModel* Offre::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT*FROM offre");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("disponibilité"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("designation"));




    return model;

}

bool Offre::modifier()
{
    QSqlQuery query;
          QString charID=QString::number(id_offre);
          QString charPrix=QString::number(prix);
          QString charDispo=QString::number(disponibilite);
          query.prepare("UPDATE offre SET prix=:prix, disponibilite=:dispo, designation=:desig WHERE id_offre=:id");
          query.bindValue(":id", charID);
          query.bindValue(":prix", charPrix);
          query.bindValue(":dispo", charDispo);
          query.bindValue(":desig", designation);
           return query.exec();

}






