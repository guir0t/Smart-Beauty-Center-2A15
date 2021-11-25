#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQueryModel>
#include<QObject>


class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int,int,int,QString,QString,QString,QString);
bool ajouter ();
int get_cin();
int get_numero();
int get_idfournisseur();
QString get_nom();
QString get_prenom ();
QString get_contract ();
QString get_adresse ();
void set_cin (int);
void set_idfournisseur (int);
void set_numero(int);
void get_nom(QString);
void get_prenom (QString);
void get_contract (QString);
void get_adresse (QString);
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier();
QSqlQueryModel * chercher_nom(const QString&);
QSqlQueryModel * tri_idcroissant();
QSqlQueryModel * tri_iddecroissant();
QSqlQueryModel * tri_cincroissant();
QSqlQueryModel * tri_cindecroissant();
QSqlQueryModel * tri_numcroissant();
QSqlQueryModel * tri_numdecroissant();
bool chercher_cin(int);
QSqlQueryModel* chercher_cin(QString );
QSqlQueryModel* chercher_contract(const QString&);
bool pdfunction(QString &,QString &);
void statistique(QVector<double>* ticks,QVector<QString> *labels );
private:
    int cin,numero,id_fournisseur ;
    QString nom,prenom,contract,adresse;


};

#endif // FOURNISSEUR_H
