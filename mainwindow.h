#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "clientt.h"
#include "rendezvous.h"
#include "produit.h"
#include "offre.h"
#include <QDialog>
#include <QFileDialog>

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
    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_pb_afficher_clicked();

    void on_pb_importer_clicked();

    void on_pb_supprimer_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_trier_prenom_clicked();

    void on_trier_annees_clicked();

    void on_tri_tel_clicked();

    void on_export_pdf_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_tab_client_activated(const QModelIndex &index);

    void on_pushButton_stat_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_modifier_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_3_clicked();

    void on_connecter_clicked();

    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_combo_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_trid_clicked();

    void on_pushButton_5_clicked();

    void on_tabWidget_2_currentChanged(int index);

    void on_pushButton_exp_clicked();

    void on_pushButton_4_clicked();

    void on_pb_ajouter_3_clicked();

    void on_pb_supp_clicked();

    void on_triePB_clicked();

    void on_triePB_2_clicked();

    void on_pb_modifier_2_clicked();

    void on_pb_recher_clicked();

    void on_pb_recher_2_clicked();

    void on_PDF_pb_clicked();

    void on_offr_PD_clicked();

    void on_pb_send_clicked();

private:

    Ui::MainWindow *ui;
    clientt c;
    produit tempProduit;
    Rendezvous R;
    Offre O;
};
#endif // MAINWINDOW_H
