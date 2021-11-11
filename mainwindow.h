#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "client.h"

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

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

private:
    Ui::MainWindow *ui;
    client Etmp;
};
#endif // MAINWINDOW_H
