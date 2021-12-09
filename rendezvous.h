#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QCalendarWidget>
#include <QTextCharFormat>
#include<QMessageBox>

class Rendezvous
{
public:
    Rendezvous();
    Rendezvous(int,int,int,int,int,int);
    int getid_rdv();
    int getid_client();
    int getid_offre();
    int getjour();
    int getmois();
    int getannees();

    void setid_rdv(int);
    void setid_client(int);
    void setid_offre(int);
    void setjour(int);
    void setmois(int);
    void setannees(int);
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,int,int,int,int,int);

    QSqlQueryModel * trier(int choix);
    QSqlQueryModel * rechercher(int choix);
    void calendrier(QTextCharFormat f,QCalendarWidget * w);
    int nbr_rdv();


private:
        int id_rdv,id_client,id_offre,jour,mois,annees;


};

#endif // RENDEZVOUS_H
