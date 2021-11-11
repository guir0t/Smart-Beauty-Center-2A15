#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class Rendezvous
{
public:
    Rendezvous();
    Rendezvous(int,int,int,int);
    int getid_rdv();
   // int getid_client();
    int getjour();
    int getmois();
    int getannees();

    void setid_rdv(int);
   // void setid_client(int);
    void setjour(int);
    void setmois(int);
    void setannees(int);
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,int,int,int);
private:
        int id_rdv,jour,mois,annees;


};

#endif // RENDEZVOUS_H
