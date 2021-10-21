#ifndef CLIENT_H
#define CLIENT_H
#include<QString>

class client
{
public:
    void setcin(QString n);
    void setprenom(QString n);
    void setnom(QString n);
    void settel(QString n);
    void setAdresse(QString n);
    QString get_cin();
    QString get_prenom();
    QString get_nom();
    QString get_tel();
    QString get_Adresse();
    client();
private:
    QString cin, prenom, nom, tel,adresse;
};
#endif // CLIENT_H
