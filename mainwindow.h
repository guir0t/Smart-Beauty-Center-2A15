#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseur.h"
#include"exportertext.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSortFilterProxyModel *proxy;
    void show_tables();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_chercher_clicked();

   // void on_chercherbutton_clicked();



    void on_pb_trie_c_clicked();

    void on_pb_trie_dec_clicked();

    void on_pb_PDF_clicked();

    void on_pb_txt_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    Fournisseur f;
    int selected=0;
    QStringList files;

};

#endif // MAINWINDOW_H
