#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class client
{
    QString  prenom, nom,adresse;
    int cin,tel;


public:
   client();
   client(int ,QString ,QString ,int,QString );

   //foncionalitee de base relatives
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,int,QString);


};
#endif // CLIENT_H
