#ifndef COMMANDE_VENTE_H
#define COMMANDE_VENTE_H
#include <QSqlQueryModel>
#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>


class Commande_vente
{
public:
    Commande_vente();
    Commande_vente(int,int,int,int,float,int) ;
    int getid_commande();
    int getjour();
    int getmois();
    int getannee();
    int getid_client();
    float getprix();
    void setid_commande(int);
    void setjour(int);
    void setmois(int);
    void setannee(int);
    void setid_client(int);
    void setprix(float);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* rechid_commande(QString );
    bool rechid_commande(int );
     bool rechprix(float );
    QSqlQueryModel* rechprix(QString );
    bool rechid_client(int );
QSqlQueryModel* rechid_client(QString );

QSqlQueryModel * tri_prixdecroissant();
   QSqlQueryModel * tri_prixcroissant();
     QSqlQueryModel * tri_id_commandecroissant();
     QSqlQueryModel * tri_id_commandedecroissant();
     QSqlQueryModel * tri_id_clientcroissant();
     QSqlQueryModel * tri_id_clientdecroissant();
void statistique(QVector<double>* ticks,QVector<QString> *labels );
private:
    int id_commande ;
    int jour,mois,annee ;
    int id_client ;
    float prix ;
};

#endif // COMMANDE_VENTE_H

class historique
{
    QString tmp;
   public:
       historique();
       void Commande_vente(QString,QString);
           QString load();
};

#endif // HISTORIQUE_H
