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
QSqlQueryModel* Offre::trierprix()
{

        QSqlQueryModel * model= new QSqlQueryModel();

              model->setQuery("SELECT * FROM offre ORDER BY prix ");
              model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
              model->setHeaderData(2,Qt::Horizontal,QObject::tr("disponibilité"));
              model->setHeaderData(3,Qt::Horizontal,QObject::tr("designation"));

        return model;

}
QSqlQueryModel *Offre::trierdes()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM offre ORDER BY designation ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("disponibilité"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("designation"));

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

QSqlQueryModel* Offre::rechercher(int id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
                QString id_string=QString ::number(id);
            model->setQuery("select * from offre where id_offre='"+id_string+"'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRIX"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESIGNATION"));

   return model;
}
QSqlQueryModel* Offre::chercher(QString a)
{
    QSqlQueryModel *model=new QSqlQueryModel();

            model->setQuery("select * from offre where DESIGNATION='"+a+"'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRIX"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESIGNATION"));

   return model;
}

QSqlQueryModel * Offre::offre_pd(){
    QSqlQueryModel *model=new QSqlQueryModel();
    int occ=0 , occmax=0 , idmax ;

    model->setQuery("select * from RENDEZ_VOUS ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_RDV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("JOUR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("MOIS"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ANNEE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_OFFRE"));

    idmax=model->data(model->index(0,5)).toInt();
    for(int i=0 ; i<model->rowCount(); i++)
    {
    occ=0 ;

    for(int j=0 ; j<model->rowCount(); j++)
    {
        if (model->data(model->index(j,5)).toInt()==model->data(model->index(i,5)).toInt())
            occ++;
    }
    if(occ>occmax)
    { occmax=occ;
      idmax=model->data(model->index(i,5)).toInt();
    }
    }
    model=rechercher(idmax);
    return model;
}



