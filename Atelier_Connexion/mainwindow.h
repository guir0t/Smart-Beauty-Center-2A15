#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commande_vente.h"
#include <QMainWindow>
#include "Arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_chercher_clicked();

    void on_pb_croissant_clicked();

    void on_pb_decroissant_clicked();

    void on_pb_word_clicked();

    void on_tri_currentChanged(int index);

    void on_pb_hist_clicked();

    void on_pb_ard_0_clicked();

    void on_pb_ard_1_clicked();

    void on_pb_ard_2_clicked();

    void on_pb_ard_3_clicked();

    void on_label_2_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    Commande_vente cv;

    QByteArray data; // variable contenant les données reçues

        Arduino a; // objet temporaire


};

#endif // MAINWINDOW_H
