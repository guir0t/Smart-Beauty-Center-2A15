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
    int id_fournisseur;
public:
    //construc
    produit();
    produit(int,float,float,int,int);
    //getters
    int getCin();
    float getPrix();
    int getQuantite();
    float getProduitSolde();
     int getIdf();
    //setters
    void setCin(int c);
    void setPrix(float p);
    void setQuantite(int q);
    void setProduitSolde(float ps);
    void setidf(int f);
     //ajouter afficher supprimer (methode de base )
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,float,float,int,int);
    QSqlQueryModel * tri_prixdecroissant();
       QSqlQueryModel * tri_prixcroissant();

};

#endif // PRODUIT_H
