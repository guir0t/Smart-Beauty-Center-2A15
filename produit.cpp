#include "produit.h"
#include <QMessageBox>

produit::produit()
{

    cin=prix=quantite=produitsolde=0;
    nom_produit="";
}
produit::produit(int c,float p,float ps,int q,int f,QString np)
{
    this ->cin=c;
    this ->prix=p;
    this ->quantite=q;
    this ->produitsolde=ps;
    this ->id_fournisseur=f;
    this ->nom_produit=np;

}
//getters
int produit:: getCin(){return cin;}
float produit::getPrix(){return prix;}
int produit::getQuantite(){return quantite;}
float produit::getProduitSolde(){return produitsolde;}
int produit::getIdf(){return  id_fournisseur;}
QString produit:: getNomproduit(){return nom_produit; }
//setters
void produit::setCin(int c){this->cin=c;}
void produit::setPrix(float p){this->prix=p;}
void produit::setQuantite(int q){this->quantite=q;}
void produit::setProduitSolde(float ps){this->produitsolde=ps;}
void produit::setidf(int f){this->id_fournisseur=f;}
void produit:: setNomproduit(QString np){this ->nom_produit=np;};

bool produit::ajouter()
{
    QSqlQuery query ;

    QString cin_string =QString::number(cin);
    QString prix_string =QString::number(prix);
    QString quantite_string =QString::number(quantite);
    QString produitsolde_string =QString::number(produitsolde);
    QString idfournisseur_string =QString::number(id_fournisseur);

    //preparation de lexecution (requete)
    query.prepare("INSERT INTO produit (cin, prix, produit_solde, quantite,id_fournisseur,nom_produit)"
                  "VALUES (:cin, :prix, :produit_solde, :quantite, :id_fournisseur, :nom_produit)");
    // creation des variables liées
    query.bindValue(0,cin_string);
    query.bindValue(1,prix_string);
    query.bindValue(2,produitsolde_string);
    query.bindValue(3,quantite_string);
    query.bindValue(4,idfournisseur_string);
     query.bindValue(5,nom_produit);
    // envoie de requete pour l'executer ;
    return query.exec();
}
QSqlQueryModel * produit::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from produit");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_produit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("produit_solde"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_fournisseur"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nom_produit"));

    return model;
    }

bool produit::supprimer(int cin)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
query.prepare("Delete from produit where cin=:cin");
query.bindValue(":cin",cin_string);
return    query.exec();
}

bool produit::modifier(int cin,float prix,float  produitsolde,int quantite ,int id_fournisseur,QString nom_produit)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
QString prix_string =QString::number(prix);
QString quantite_string =QString::number(quantite);
QString produitsolde_string =QString::number(produitsolde);
QString idfournisseur_string =QString::number(id_fournisseur);
query.prepare("update produit set prix=:prix,produit_solde=:produit_solde,quantite=:quantite,id_fournisseur=:id_fournisseur,nom_produit=:nom_produit where cin=:cin");
query.bindValue(":cin", cin_string);
query.bindValue(":prix", prix_string);
query.bindValue(":produit_solde", produitsolde_string);
query.bindValue(":quantite", quantite_string);
query.bindValue(":id_fournisseur", idfournisseur_string);
query.bindValue(":nom_produit", nom_produit);


return    query.exec();
}

QSqlQueryModel * produit::tri_prixcroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY prix ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));

    return model;
}
QSqlQueryModel * produit::tri_prixdecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY prix DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
              model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
              model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));
            return model;
}

QSqlQueryModel * produit::tri_quantitecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY quantite ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));

    return model;
}

QSqlQueryModel * produit::tri_produitsoldecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY  produit_solde ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));

    return model;
}
QSqlQueryModel * produit::tri_quantitedecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY quantite DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));

    return model;
}

QSqlQueryModel * produit::tri_produitsoldedecroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM produit ORDER BY  produit_solde DESC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));

    return model;
}
bool produit::rech(int x){
    QSqlQuery query;
    query.prepare("select * from produit where cin = :cin;");
    query.bindValue(":cin", x);
    return query.exec();
}
QSqlQueryModel* produit::rechercher(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from produit where cin ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));
        return model;

}

bool produit::rechprix(int x){
    QSqlQuery query;
    query.prepare("select * from produit where prix = :prix;");
    query.bindValue(":prix", x);
    return query.exec();
}
QSqlQueryModel* produit::rechercherprix(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from produit where prix ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));
        return model;

}

bool produit::rechquantite(int x){
    QSqlQuery query;
    query.prepare("select * from produit where quantite = :quantite;");
    query.bindValue(":quantite", x);
    return query.exec();
}
QSqlQueryModel* produit::rechercherquantite(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from produit where quantite ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("produitsolde"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_fournisseur"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom_produit"));
        return model;

}
void produit::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select nom_produit from produit");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
