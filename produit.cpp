#include "produit.h"
produit::produit(int c,float p,float ps,int q)
{
    this ->cin=c;
    this ->prix=p;
    this ->quantite=q;
    this ->produit_solde=ps;
}
//getters
int produit:: getCin(){return cin;}
float produit::getPrix(){return prix;}
int produit::getQuantite(){return quantite;}
float produit::getProduit_Solde(){return produit_solde;}
//setters
void produit::setCin(int c){this->cin=c;}
void produit::setPrix(float p){this->prix=p;}
void produit::setQuantite(int q){this->quantite=q;}
void produit::setProduit_Solde(float ps){this->produit_solde=ps;}
bool produit::ajouter()
{
    QSqlQuery query ;

    QString cin_string =QString::number(cin);
    QString prix_string =QString::number(prix);
    QString quantite_string =QString::number(quantite);
    QString produitsld_string =QString::number(produit_solde);
    //preparation de lexecution (requete)
    query.prepare("INSERT INTO produit (cin, prix, produit_solde, quantite)"
                  "VALUES (:cin, :prix, :produit_solde, :quantite)");
    // creation des variables liées
    query.bindValue(0,cin_string);
    query.bindValue(1,prix_string);
    query.bindValue(2,produitsld_string);
    query.bindValue(3,quantite_string);
    // envoie de requete pour l'executer ;
    return query.exec();
}

/* QSqlQueryModel * produit::afficher()
{
 //to do
}*/
bool produit::supprimer(int)
{
    QSqlQuery query;
    query.prepare(" Delete from produit where cin=:cin");
    query.bindValue(0, cin);

  return  query.exec();
}
