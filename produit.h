#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class produit
{
    //attribut
    int cin;
    float prix;
    int quantite;
    float produit_solde;
public:
    //construc
    produit(){}
    produit(int,float,int,float);
    //getters
    int getCin(){return cin;}
    float getPrix(){return prix;}
    int getQuantite(){return quantite;}
    float getProduit_Solde(){return produit_solde;}
    //setters
    void setCin(int c){this->cin=c;}
    void setPrix(float p){this->prix=p;}
    void setQuantite(int q){this->quantite=q;}
    void setProduit_Solde(float ps){this->produit_solde=ps;}
     //ajouter afficher supprimer (methode de base )
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);



};

#endif // PRODUIT_H
