#include "commande_vente.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QStackedWidget>
#include "commande_vente.h"



Commande_vente::Commande_vente()
{
    id_commande=0; id_client=0; jour=0 ; mois=0 ; annee=0; prix=0 ;

}
Commande_vente::Commande_vente(int id_commande,int jour,int mois,int annee ,float prix ,int id_client)
{ this->id_commande=id_commande ; this->jour=jour ; this->mois=mois ; this->annee=annee ; this->id_client=id_client ;this->prix=prix ;}

int Commande_vente::getid_commande(){return id_commande;}
int Commande_vente::getjour(){return jour;}
int Commande_vente::getmois(){return mois;}
int Commande_vente::getannee(){return annee;}
int Commande_vente::getid_client(){return id_client;}
float Commande_vente::getprix(){return prix;}
void Commande_vente::setid_commande(int id_commande){this->id_commande=id_commande ;}
void Commande_vente::setjour(int jour){this->jour=jour ;}
void Commande_vente::setmois(int mois){this->mois=mois ;}
void Commande_vente::setannee(int annee){this->annee=annee ;}
void Commande_vente::setid_client(int id_client){this->id_client=id_client ;}
void Commande_vente::setprix(float prix){this->prix=prix ;}
bool Commande_vente::ajouter()
{

  QSqlQuery query;
  QString id_commande_string=QString::number(id_commande);
  QString jour_string=QString::number(jour);
  QString mois_string=QString::number(mois);
  QString annee_string=QString::number(annee);
QString prix_string=QString::number(prix);
  QString id_client_string=QString::number(id_client);
       query.prepare("INSERT INTO commande_vente (id_commande,jour,mois,annee,prix,id_client)VALUES (:id_commande, :jour, :mois, :annee, :prix, :id_client)");

       query.bindValue(":id_commande", id_commande_string);
       query.bindValue(":jour", jour_string);
       query.bindValue(":mois", mois_string);
       query.bindValue(":annee", annee_string);
       query.bindValue(":prix", prix_string);
       query.bindValue(":id_client", id_client_string);
       return  query.exec();
      }
bool Commande_vente::supprimer(int id_commande)
{

    QSqlQuery query;
         query.prepare("Delete from commande_vente where id_commande=id_commande");

         query.bindValue(0, id_commande);

         return  query.exec();


}



QSqlQueryModel*Commande_vente::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM commande_vente");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("jour"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("mois"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("annee"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_client"));


return model ;
}
bool Commande_vente::modifier( )
{  QSqlQuery query ;

query.prepare("Update  commande_vente set id_commande=:id_commande,jour=:hour,mois=:mois,annee=:annee,prix=:prix,id_client=:id_client where id_commande=:id_commande ");
query.bindValue(":id_commande",id_commande );
query.bindValue(":jour",jour);
query.bindValue(":mois",mois);
query.bindValue(":annee",annee);
query.bindValue(":prix",prix);
query.bindValue(":id_client",id_client);


return    query.exec();
}

bool Commande_vente::rechid_commande(int x){
    QSqlQuery query;
    query.prepare("select * from Commande_vente where id_commande = :id_commande;");
    query.bindValue(":id_commande", x);
    return query.exec();
}

QSqlQueryModel* Commande_vente::rechid_commande(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Commande_vente where id_commande ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));
        return model;

}



bool Commande_vente::rechprix(float x){
    QSqlQuery query;
    query.prepare("select * from Commande_vente where prix = :prix;");
    query.bindValue(":prix", x);
    return query.exec();
}
QSqlQueryModel* Commande_vente::rechprix(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Commande_vente where prix ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));
        return model;

}



bool Commande_vente::rechid_client(int x){
    QSqlQuery query;
    query.prepare("select * from Commande_vente where id_client = :id_client;");
    query.bindValue(":id_client", x);
    return query.exec();
}
QSqlQueryModel* Commande_vente::rechid_client(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Commande_vente where id_client ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));
        return model;

}


QSqlQueryModel * Commande_vente::tri_prixcroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Commande_vente ORDER BY prix ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));

    return model;
}
QSqlQueryModel * Commande_vente::tri_prixdecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Commande_vente ORDER BY prix DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
              model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
              model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));
            return model;
}

QSqlQueryModel * Commande_vente::tri_id_commandecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Commande_vente ORDER BY id_commande ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));

    return model;
}

QSqlQueryModel * Commande_vente::tri_id_commandedecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Commande_vente ORDER BY  id_commande DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));

    return model;
}
QSqlQueryModel * Commande_vente::tri_id_clientcroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Commande_vente ORDER BY id_client ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));

    return model;
}

QSqlQueryModel * Commande_vente::tri_id_clientdecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Commande_vente ORDER BY  id_client DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_commande"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("jour"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("mois"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("annee"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_client"));

    return model;
}

void Commande_vente::statistique(QVector<double> *ticks, QVector<QString> *labels)
{
    QSqlQuery q;



        int i=0;



        q.exec("select PRIX from Commande_vente");



        while (q.next())



        {



            QString identifiant = q.value(0).toString();



            i++;



            *ticks<<i;



            *labels <<identifiant;



        }
}


historique::historique()
{

}
void historique::Commande_vente(QString prix,QString id_client)
{    QFile file ("D:/Users/dhiaa/Desktop/Wedding_planner_2A1/INTEGRATIONhistorique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << prix+"\n"+id_client << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:\ Users\Aziz\Desktop\Atelier_Connexion\historique\historiquedevente.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}


