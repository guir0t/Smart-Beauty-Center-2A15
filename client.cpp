#include "client.h"

client::client()
{
cin="";
prenom="";
nom="";
tel="";
adresse="";

}
void client::setcin(QString n){cin=n;}
void client::setprenom(QString n){prenom=n;}
void client::setnom(QString n){nom=n;}
void client::settel(QString n){tel=n;}
void client::setAdresse(QString n){adresse=n;}

QString client::get_cin(){return cin;}
QString client::get_prenom(){return prenom;}
QString client::get_nom(){return nom;}
QString client::get_tel(){return tel;}
QString client::get_Adresse(){return adresse;}
