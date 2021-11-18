#ifndef CLIENTT_H
#define CLIENTT_H
#include <QString>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPdfWriter>
#include <QPainter>

class clientt
{
public:
    clientt();
    clientt(int,QString,QString,int,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    int gettel();
    QString getadresse();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void settel(int);
    void setadresse(QString);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel *afficher();
    bool modifier(int,QString,QString,int,QString);
    QSqlQueryModel * trierprenom();
    QSqlQueryModel * trieradresse();
    void recherche(QTableView * table, QString);
    void telechargerPDF(QString);
private:
    int cin,tel;
    QString nom,prenom,adresse;
};



#endif // CLIENTT_H
