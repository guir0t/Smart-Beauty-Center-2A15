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
    QString nom_produit;
public:
    //construc
    produit();
    produit(int,float,float,int,int,QString);
    //getters
    int getCin();
    float getPrix();
    int getQuantite();
    float getProduitSolde();
     int getIdf();
     QString getNomproduit();
    //setters
    void setCin(int c);
    void setPrix(float p);
    void setQuantite(int q);
    void setProduitSolde(float ps);
    void setidf(int f);
    void setNomproduit(QString np);
     //ajouter afficher supprimer (methode de base )
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,float,float,int,int,QString);
    QSqlQueryModel * tri_prixdecroissant();
       QSqlQueryModel * tri_prixcroissant();
         QSqlQueryModel * tri_quantitecroissant();
         QSqlQueryModel * tri_produitsoldecroissant();
         QSqlQueryModel * tri_quantitedecroissant();
         QSqlQueryModel * tri_produitsoldedecroissant();
            bool rech(int );
        QSqlQueryModel* rechercher(QString );
        bool rechprix(int );
    QSqlQueryModel* rechercherprix(QString );
    bool rechquantite(int );
QSqlQueryModel* rechercherquantite(QString );
};

#endif // PRODUIT_H
