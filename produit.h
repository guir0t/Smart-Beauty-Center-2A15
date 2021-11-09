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
    float produitsolde;
public:
    //construc
    produit();
    produit(int,float,float,int);
    //getters
    int getCin();
    float getPrix();
    int getQuantite();
    float getProduitSolde();
    //setters
    void setCin(int c);
    void setPrix(float p);
    void setQuantite(int q);
    void setProduitSolde(float ps);
     //ajouter afficher supprimer (methode de base )
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,float,float,int);
    QSqlQueryModel * tri_prixdecroissant();
       QSqlQueryModel * tri_prixcroissant();

};

#endif // PRODUIT_H
