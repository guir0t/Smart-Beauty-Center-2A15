#ifndef OFFRE_H
#define OFFRE_H
#include<QSqlQueryModel>
#include <QString>

class Offre
{

public:
    Offre();
    Offre(int id,int prix,int dispo,QString designation );
    int getid();
    int getprix();
    int getdispo();
    QString getdesignation();
    void setid(int);
    void setprix(int);
    void setdispo(int);
    void setdesignation(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * trierprix();
    QSqlQueryModel * trierdes();
    QSqlQueryModel* rechercher(int);
    QSqlQueryModel* chercher(QString );

    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * offre_pd();
private:
    int id_offre ;
    int prix;
    int disponibilite;
    QString designation;
};

#endif // OFFRE_H
