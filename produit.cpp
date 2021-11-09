#include "produit.h"
produit::produit()
{

    cin=prix=quantite=produitsolde=0;
}
produit::produit(int c,float p,float ps,int q)
{
    this ->cin=c;
    this ->prix=p;
    this ->quantite=q;
    this ->produitsolde=ps;
}
//getters
int produit:: getCin(){return cin;}
float produit::getPrix(){return prix;}
int produit::getQuantite(){return quantite;}
float produit::getProduitSolde(){return produitsolde;}
//setters
void produit::setCin(int c){this->cin=c;}
void produit::setPrix(float p){this->prix=p;}
void produit::setQuantite(int q){this->quantite=q;}
void produit::setProduitSolde(float ps){this->produitsolde=ps;}


bool produit::ajouter()
{
    QSqlQuery query ;

    QString cin_string =QString::number(cin);
    QString prix_string =QString::number(prix);
    QString quantite_string =QString::number(quantite);
    QString produitsolde_string =QString::number(produitsolde);
    //preparation de lexecution (requete)
    query.prepare("INSERT INTO produit (cin, prix, produit_solde, quantite)"
                  "VALUES (:cin, :prix, :produit_solde, :quantite)");
    // creation des variables liées
    query.bindValue(0,cin_string);
    query.bindValue(1,prix_string);
    query.bindValue(2,produitsolde_string);
    query.bindValue(3,quantite_string);
    // envoie de requete pour l'executer ;
    return query.exec();
}
QSqlQueryModel * produit::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from produit");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("produit_solde"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));

    return model;
    }


bool produit::supprimer(int cin)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
query.prepare("Delete from produit where cin=:cin");
query.bindValue(":cin",cin_string);
return    query.exec();
}

bool produit::modifier(int cin,float prix,float  produitsolde,int quantite)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
QString prix_string =QString::number(prix);
QString quantite_string =QString::number(quantite);
QString produitsolde_string =QString::number(produitsolde);
query.prepare("update produit set prix=:prix,produit_solde=:produit_solde,quantite=:quantite where cin=:cin");
query.bindValue(":cin", cin_string);
query.bindValue(":prix", prix_string);
query.bindValue(":produit_solde", produitsolde_string);
query.bindValue(":quantite", quantite_string);

return    query.exec();
}

QSqlQueryModel * produit::tri_prixcroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY prix ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));

    return model;
}
QSqlQueryModel * produit::tri_prixdecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY prix DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
            return model;
}
