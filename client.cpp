#include "client.h"

client::client()
{
cin=tel=0;
prenom=nom=adresse="";

}
client::client(int cin,QString nom,QString prenom,int tel,QString adresse)
{

    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
    this->adresse=adresse;
}






bool client::ajouter()
{
    QSqlQuery query;
    QString cin_string =QString::number(cin);
    QString tel_string =QString::number(tel);
    //prepare() prend la requete en parametre pour l'execution.

    query.prepare("INSERT INTO CLIENT (cin,nom,prenom,tel,adresse "
                        "VALUES (:cin,:nom,:prenom,:tel,:adresse)");
    //creation des variables liees

    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":tel",tel);
    query.bindValue(":adresse",adresse);

    return    query.exec(); //exec() envoie de la requete pour l'executer.
}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));

    return model;
    }

bool client::supprimer(int cin)
{

    QSqlQuery query;
    QString cin_string =QString::number(cin);
    query.prepare("Delete from CLIENT where cin=:cin");
    query.bindValue(":cin",cin_string);
    return    query.exec();

}
bool client::modifier(int cin,QString nom,QString prenom,int tel,QString adresse)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
QString tel_string =QString::number(tel);
query.prepare("update CLIENT set nom=:nom,prenom=:prenom,tel=:tel,adresse=:adresse,where cin=:cin");
query.bindValue(":cin", cin_string);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":tel", tel_string);
query.bindValue(":adresse", adresse);
return    query.exec();
}
