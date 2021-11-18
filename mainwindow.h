#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "produit.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();


    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();


    void on_pushButton_combo_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_trid_clicked();


    void on_pushButton_3_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_exp_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    produit tempProduit;
};
#endif // MAINWINDOW_H
