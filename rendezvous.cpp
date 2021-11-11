#include "rendezvous.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>


Rendezvous::Rendezvous()
{
id_rdv=0;jour=0; mois=0; annees=0;
}

Rendezvous::Rendezvous(int id_rdv,int jour,int mois,int annees)
{this->id_rdv=id_rdv;/*this->id_client=id_client;*/ this->jour=jour; this->mois=mois;this->annees=annees;}
int Rendezvous:: getid_rdv(){return id_rdv;}
//int Rendezvous:: getid_client(){return id_client;}
int Rendezvous:: getjour(){return jour;}
int Rendezvous:: getmois(){return mois;}
int Rendezvous:: getannees(){return annees;};

void Rendezvous::setid_rdv(int id_rdv){this->id_rdv=id_rdv;}
// void Rendezvous::setid_client(int id_client){this->id_client=id_client;}
void Rendezvous::setjour(int jour){this->jour=jour;}
void Rendezvous:: setmois(int mois){this->mois=mois;}
void Rendezvous::setannees(int annees){this->annees=annees;}
bool Rendezvous::ajouter()

{


    QSqlQuery query;

          QString id_rdv_string=QString::number(id_rdv);
         // QString id_client_string=QString::number(id_client);
          QString jour_string=QString::number(jour);
          QString mois_string=QString::number(mois);
          QString annees_string=QString::number(annees);

          query.prepare("insert into RENDEZVOUS (ID_RDV, JOUR,MOIS,ANNEES)VALUES (:id_rdv, :jour, :mois, :annees)");


         query.bindValue(":id_rdv", id_rdv_string);

        //  query.bindValue(":id_client", id_client_string);

          query.bindValue(":jour", jour_string);
          query.bindValue(":mois", mois_string);
          query.bindValue(":annees", annees_string);
          return query.exec();
}



bool Rendezvous::supprimer(int id_rdv)
{
    QSqlQuery query;

    query.prepare("Delete from RENDEZVOUS where id_rdv=:id_rdv");


   query.bindValue(0, id_rdv);

   return query.exec();

}



QSqlQueryModel * Rendezvous::afficher()
{
  QSqlQueryModel * model=new QSqlQueryModel();
  model->setQuery("SELECT id_rdv,jour,mois,annees  FROM Rendezvous");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_rdv"));
       // model->setHeaderData(1, Qt::Horizontal,QObject::tr("id_client"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("mois"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("annees"));
                return model;
}
bool Rendezvous::modifier(int id_rdv, int jour, int mois, int annees)
{

    QSqlQuery query ;
      QString id_rdv_string = QString::number(id_rdv);
      QString jour_string = QString::number(jour);

      QString mois_string = QString::number(mois);

      QString annees_string = QString::number(annees);

      query.prepare("update RENDEZVOUS set jour=:jour,mois=:mois,annees=:annees where id_rdv=:id_rdv");
      query.bindValue(":id_rdv",id_rdv_string);
      query.bindValue(":jour",jour_string);
      query.bindValue(":mois",mois_string);
      query.bindValue(":annees",annees_string);

      return query.exec();
}

