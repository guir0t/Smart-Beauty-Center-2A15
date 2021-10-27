#include "produit.h"
produit::produit(int c,float p,int q,float ps)
{
    this ->cin=c;
    this ->prix=p;
    this ->quantite=q;
    this ->produit_solde=ps;
}

bool produit::ajouter()
{
    QSqlQuery query ;

    QString cin_string =QString::number(cin);
    //preparation de lexecution (requete)
    query.prepare(" INSERT INTO produit(cin,prix,quantite,produit_solde)""VALUES(:cin, :prix, :quantite, :produit_solde");
    // creation des variables liées
    query.bindValue(0,cin_string);
    query.bindValue(1,prix);
    query.bindValue(2,quantite);
    query.bindValue(3,produit_solde);
    // envoie de requete pour l'executer ;
    return query.exec();
}

/* QSqlQueryModel * produit::afficher()
{
 //to do
}
bool produit::supprimer(int)
{
    //to do
}*/
