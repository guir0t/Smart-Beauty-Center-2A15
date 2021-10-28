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
    produit();
    produit(int,float,float,int);
    //getters
    int getCin();
    float getPrix();
    int getQuantite();
    float getProduit_Solde();
    //setters
    void setCin(int c);
    void setPrix(float p);
    void setQuantite(int q);
    void setProduit_Solde(float ps);
     //ajouter afficher supprimer (methode de base )
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);



};

#endif // PRODUIT_H
