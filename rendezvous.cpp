#include "rendezvous.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>


Rendezvous::Rendezvous()
{
id_rdv=0;id_client=0;id_offre=0,jour=0; mois=0; annees=0;
}

Rendezvous::Rendezvous(int id_rdv,int id_client,int id_offre,int jour,int mois,int annees)
{this->id_rdv=id_rdv;this->id_client=id_client;this->id_offre=id_offre; this->jour=jour; this->mois=mois;this->annees=annees;}
int Rendezvous:: getid_rdv(){return id_rdv;}
int Rendezvous:: getid_client(){return id_client;}
int Rendezvous:: getid_offre(){return id_offre;}
int Rendezvous:: getjour(){return jour;}
int Rendezvous:: getmois(){return mois;}
int Rendezvous:: getannees(){return annees;};

void Rendezvous::setid_rdv(int id_rdv){this->id_rdv=id_rdv;}
void Rendezvous::setid_client(int id_client){this->id_client=id_client;}
void Rendezvous::setid_offre(int id_offre){this->id_offre=id_offre;}
void Rendezvous::setjour(int jour){this->jour=jour;}
void Rendezvous:: setmois(int mois){this->mois=mois;}
void Rendezvous::setannees(int annees){this->annees=annees;}

bool Rendezvous::ajouter()
{
    QSqlQuery query;

          QString id_rdv_string=QString::number(id_rdv);
          QString id_client_string=QString::number(id_client);
          QString id_offre_string=QString::number(id_offre);
          QString jour_string=QString::number(jour);
          QString mois_string=QString::number(mois);
          QString annees_string=QString::number(annees);

          query.prepare("insert into RENDEZVOUS (ID_RDV, JOUR,MOIS,ANNEES,id_client,id_offre)VALUES (:id_rdv, :jour, :mois, :annees, :id_client, :id_offre)");
          query.bindValue(":id_rdv", id_rdv_string);
          query.bindValue(":jour", jour_string);
          query.bindValue(":mois", mois_string);
          query.bindValue(":annees", annees_string);
          query.bindValue(":id_client", id_client_string);
          query.bindValue(":id_offre", id_offre_string);

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
  model->setQuery("SELECT id_rdv,jour,mois,annees,id_client,id_offre  FROM Rendezvous");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_rdv"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("mois"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("annees"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("id_client"));
        model->setHeaderData(5, Qt::Horizontal,QObject::tr("id_offre"));
                return model;
}
bool Rendezvous::modifier(int id_rdv,int id_client,int id_offre ,int jour, int mois, int annees)
{

    QSqlQuery query ;
      QString id_rdv_string = QString::number(id_rdv);
      QString id_client_string = QString::number(id_client);
      QString id_offre_string = QString::number(id_offre);
      QString jour_string = QString::number(jour);
      QString mois_string = QString::number(mois);
      QString annees_string = QString::number(annees);

      query.prepare("update RENDEZVOUS set id_client=:id_client,id_offret=:id_offre,jour=:jour,mois=:mois,annees=:annees where id_rdv=:id_rdv");
      query.bindValue(":id_rdv",id_rdv_string);
      query.bindValue(":id_client",id_client_string);
      query.bindValue(":id_offre",id_offre_string);
      query.bindValue(":jour",jour_string);
      query.bindValue(":mois",mois_string);
      query.bindValue(":annees",annees_string);

      return query.exec();
}

QSqlQueryModel * Rendezvous::trier(int choix)
{
    QSqlQueryModel * model=afficher();
    QString query;
    QString ch;

        switch (choix)
        {
            case 1:
            {
              ch="id_rdv";
              break;
            }
            case 2:
            {
              ch="id_client";
              break;
            }
            case 3:
            {
              ch="id_offre";
              break;
            }

            default:
              break;
        }
     query="SELECT * FROM rendezvous ORDER BY "+ch+" DESC";
     model->setQuery(query);
    return model;
}

QSqlQueryModel * Rendezvous::rechercher(int choix)
{
    QSqlQueryModel * model=afficher();
    QString query;
    QString ch,ch2;
    switch (choix)
    {
    case 1:
        ch="id_rdv";
        ch2=QString::number(id_rdv);

        break;
    case 2:
        ch="id_client";
        ch2=QString::number(id_client);
        break;
    case 3:
        ch="id_offre";
        ch2=QString::number(id_offre);
        break;
    default:
        break;
    }
    query="SELECT * FROM rendezvous WHERE "+ch+" = "+ch2;
    model->setQuery(query);
    return model;
}

void Rendezvous::calendrier(QTextCharFormat f,QCalendarWidget * w)
{
    QDate date;
    QSqlQuery query("SELECT jour,mois,annees FROM rendezvous");
    while (query.next())
    {
        date.setDate(query.value(2).toInt(),query.value(1).toInt(),query.value(0).toInt());
        w->setDateTextFormat(date,f);
    }
    w->setDateTextFormat(date,f);
}

int Rendezvous::nbr_rdv()
{
    int i=0;
    QSqlQuery query("SELECT jour,mois,annees FROM rendezvous");
    while (query.next())
    {
        QDate date(query.value(2).toInt(),query.value(1).toInt(),query.value(0).toInt());
        if (date>=QDate::currentDate()&&(date<=QDate::currentDate().addDays(7)))
        {
            i++;
        }
    }
    return i;
}
