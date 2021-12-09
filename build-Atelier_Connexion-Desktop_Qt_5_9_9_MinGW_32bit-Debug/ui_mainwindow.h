/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *le_id_commande;
    QLineEdit *le_jour;
    QLineEdit *le_mois;
    QLineEdit *le_annee;
    QLineEdit *le_idcl;
    QLineEdit *le_prix;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pb_ajouter;
    QWidget *tab_2;
    QTableView *tab_commande;
    QWidget *tab_3;
    QLabel *label;
    QLineEdit *le_id_supp;
    QPushButton *pb_supprimer;
    QWidget *tab_4;
    QGroupBox *groupBox_3;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *le_id_commande_modif;
    QLineEdit *le_jour_modif;
    QLineEdit *le_mois_modif;
    QLineEdit *le_annee_modif;
    QLineEdit *le_idcl_modif;
    QLineEdit *le_prix_modif;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QPushButton *pb_modifier;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(738, 408);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 0, 521, 361));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 10, 461, 311));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 40, 81, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 80, 47, 13));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 120, 47, 13));
        le_id_commande = new QLineEdit(groupBox_2);
        le_id_commande->setObjectName(QStringLiteral("le_id_commande"));
        le_id_commande->setGeometry(QRect(140, 40, 113, 20));
        le_jour = new QLineEdit(groupBox_2);
        le_jour->setObjectName(QStringLiteral("le_jour"));
        le_jour->setGeometry(QRect(140, 80, 113, 20));
        le_mois = new QLineEdit(groupBox_2);
        le_mois->setObjectName(QStringLiteral("le_mois"));
        le_mois->setGeometry(QRect(140, 120, 113, 20));
        le_annee = new QLineEdit(groupBox_2);
        le_annee->setObjectName(QStringLiteral("le_annee"));
        le_annee->setGeometry(QRect(140, 160, 113, 20));
        le_idcl = new QLineEdit(groupBox_2);
        le_idcl->setObjectName(QStringLiteral("le_idcl"));
        le_idcl->setGeometry(QRect(140, 190, 113, 20));
        le_prix = new QLineEdit(groupBox_2);
        le_prix->setObjectName(QStringLiteral("le_prix"));
        le_prix->setGeometry(QRect(140, 240, 113, 20));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 160, 47, 13));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 200, 47, 13));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 200, 47, 13));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 240, 47, 13));
        pb_ajouter = new QPushButton(groupBox_2);
        pb_ajouter->setObjectName(QStringLiteral("pb_ajouter"));
        pb_ajouter->setGeometry(QRect(340, 160, 75, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_commande = new QTableView(tab_2);
        tab_commande->setObjectName(QStringLiteral("tab_commande"));
        tab_commande->setGeometry(QRect(10, 20, 481, 281));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label = new QLabel(tab_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 91, 16));
        le_id_supp = new QLineEdit(tab_3);
        le_id_supp->setObjectName(QStringLiteral("le_id_supp"));
        le_id_supp->setGeometry(QRect(130, 40, 113, 20));
        pb_supprimer = new QPushButton(tab_3);
        pb_supprimer->setObjectName(QStringLiteral("pb_supprimer"));
        pb_supprimer->setGeometry(QRect(150, 130, 75, 23));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        groupBox_3 = new QGroupBox(tab_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 20, 461, 311));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 40, 81, 16));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 80, 47, 13));
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 120, 47, 13));
        le_id_commande_modif = new QLineEdit(groupBox_3);
        le_id_commande_modif->setObjectName(QStringLiteral("le_id_commande_modif"));
        le_id_commande_modif->setGeometry(QRect(140, 40, 113, 20));
        le_jour_modif = new QLineEdit(groupBox_3);
        le_jour_modif->setObjectName(QStringLiteral("le_jour_modif"));
        le_jour_modif->setGeometry(QRect(140, 80, 113, 20));
        le_mois_modif = new QLineEdit(groupBox_3);
        le_mois_modif->setObjectName(QStringLiteral("le_mois_modif"));
        le_mois_modif->setGeometry(QRect(140, 120, 113, 20));
        le_annee_modif = new QLineEdit(groupBox_3);
        le_annee_modif->setObjectName(QStringLiteral("le_annee_modif"));
        le_annee_modif->setGeometry(QRect(140, 160, 113, 20));
        le_idcl_modif = new QLineEdit(groupBox_3);
        le_idcl_modif->setObjectName(QStringLiteral("le_idcl_modif"));
        le_idcl_modif->setGeometry(QRect(140, 200, 113, 20));
        le_prix_modif = new QLineEdit(groupBox_3);
        le_prix_modif->setObjectName(QStringLiteral("le_prix_modif"));
        le_prix_modif->setGeometry(QRect(140, 240, 113, 20));
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 160, 47, 13));
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 200, 47, 13));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 200, 47, 13));
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 240, 47, 13));
        pb_modifier = new QPushButton(groupBox_3);
        pb_modifier->setObjectName(QStringLiteral("pb_modifier"));
        pb_modifier->setGeometry(QRect(340, 160, 75, 23));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 738, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestion des Clients", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Ajouter une commande de vente ", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "id_commande", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "jour", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "mois", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "annee", Q_NULLPTR));
        label_12->setText(QString());
        label_13->setText(QApplication::translate("MainWindow", "id_client", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "prix", Q_NULLPTR));
        pb_ajouter->setText(QApplication::translate("MainWindow", "ajouter", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "ajouter commande_vente", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "afficher commande", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "id_commande", Q_NULLPTR));
        pb_supprimer->setText(QApplication::translate("MainWindow", "supprimer", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "supprimer commande", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Ajouter une commande de vente ", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "id_commande", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "jour", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "mois", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "annee", Q_NULLPTR));
        label_19->setText(QString());
        label_20->setText(QApplication::translate("MainWindow", "id_client", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "prix", Q_NULLPTR));
        pb_modifier->setText(QApplication::translate("MainWindow", "modifier", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "modifier commande", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
