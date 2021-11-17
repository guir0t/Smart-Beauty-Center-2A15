#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"rendezvous.h"


#include <QMainWindow>

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

    void on_modifier_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Rendezvous R;
};

#endif // MAINWINDOW_H
