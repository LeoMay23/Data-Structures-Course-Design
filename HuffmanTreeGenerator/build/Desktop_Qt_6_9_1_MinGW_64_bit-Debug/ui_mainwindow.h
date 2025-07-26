/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *selectFileButton;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *nodeLineEdit;
    QLineEdit *weightLineEdit;
    QPushButton *addButton;
    QPushButton *delButton;
    QGroupBox *groupBox_2;
    QTextEdit *textEdit;
    QPushButton *addTextButton;
    QTableView *displayTable;
    QTableView *displayTable_2;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *calculateButton;
    QPushButton *generateButton;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(748, 437);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        selectFileButton = new QPushButton(centralwidget);
        selectFileButton->setObjectName("selectFileButton");
        selectFileButton->setGeometry(QRect(20, 10, 75, 24));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 50, 171, 131));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 54, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 54, 16));
        nodeLineEdit = new QLineEdit(groupBox);
        nodeLineEdit->setObjectName("nodeLineEdit");
        nodeLineEdit->setGeometry(QRect(80, 30, 81, 20));
        weightLineEdit = new QLineEdit(groupBox);
        weightLineEdit->setObjectName("weightLineEdit");
        weightLineEdit->setGeometry(QRect(80, 60, 81, 20));
        addButton = new QPushButton(groupBox);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(10, 100, 75, 24));
        delButton = new QPushButton(groupBox);
        delButton->setObjectName("delButton");
        delButton->setGeometry(QRect(90, 100, 75, 24));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 195, 171, 181));
        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 20, 151, 121));
        addTextButton = new QPushButton(groupBox_2);
        addTextButton->setObjectName("addTextButton");
        addTextButton->setGeometry(QRect(60, 150, 101, 24));
        displayTable = new QTableView(centralwidget);
        displayTable->setObjectName("displayTable");
        displayTable->setGeometry(QRect(220, 50, 241, 291));
        displayTable_2 = new QTableView(centralwidget);
        displayTable_2->setObjectName("displayTable_2");
        displayTable_2->setGeometry(QRect(490, 50, 241, 291));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(220, 10, 81, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_7->setFont(font);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(490, 10, 81, 31));
        label_8->setFont(font);
        calculateButton = new QPushButton(centralwidget);
        calculateButton->setObjectName("calculateButton");
        calculateButton->setGeometry(QRect(420, 350, 141, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font1.setPointSize(11);
        font1.setBold(true);
        calculateButton->setFont(font1);
        generateButton = new QPushButton(centralwidget);
        generateButton->setObjectName("generateButton");
        generateButton->setGeometry(QRect(590, 350, 141, 31));
        generateButton->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(650, 10, 81, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font2.setPointSize(10);
        font2.setBold(true);
        label_3->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 748, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        selectFileButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\345\217\226\346\226\207\344\273\266", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\273\231\345\256\232\346\235\203\351\207\215\345\200\274", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\255\227\347\254\246", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\235\203\351\207\215\345\200\274", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\212\202\347\202\271", nullptr));
        delButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\212\202\347\202\271", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        addTextButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\346\234\254\345\210\260\350\212\202\347\202\271", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\255\227\347\254\246\351\242\221\347\216\207", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\223\210\345\244\253\346\233\274\347\274\226\347\240\201", nullptr));
        calculateButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\345\223\210\345\244\253\346\233\274\347\274\226\347\240\201", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "\345\217\257\350\247\206\345\214\226\345\223\210\345\244\253\346\233\274\346\240\221", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "2352036 \351\233\267\350\276\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
