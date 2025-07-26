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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "drawingarea.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    DrawingArea *DrawingArea;
    QLabel *label;
    QGroupBox *groupBox;
    QTextBrowser *textBrowser;
    QPushButton *cancelButton;
    QGroupBox *groupBox_2;
    QLabel *fromLabel;
    QLabel *toLabel;
    QLineEdit *fromLineEdit;
    QLineEdit *toLineEdit;
    QLabel *weightLabel;
    QLineEdit *weightLineEdit;
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *finishButton;
    QGroupBox *groupBox_3;
    QLabel *vexLabel;
    QLabel *edgeLabel;
    QLabel *vexNumLabel;
    QLabel *edgeNumLabel;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(771, 585);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        DrawingArea = new class DrawingArea(centralwidget);
        DrawingArea->setObjectName("DrawingArea");
        DrawingArea->setGeometry(QRect(10, 50, 751, 291));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 350, 251, 171));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font1.setPointSize(11);
        font1.setBold(true);
        groupBox->setFont(font1);
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(10, 20, 231, 141));
        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(686, 20, 75, 24));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(290, 350, 251, 171));
        groupBox_2->setFont(font1);
        fromLabel = new QLabel(groupBox_2);
        fromLabel->setObjectName("fromLabel");
        fromLabel->setGeometry(QRect(10, 30, 71, 16));
        fromLabel->setFont(font);
        toLabel = new QLabel(groupBox_2);
        toLabel->setObjectName("toLabel");
        toLabel->setGeometry(QRect(10, 70, 71, 16));
        toLabel->setFont(font);
        fromLineEdit = new QLineEdit(groupBox_2);
        fromLineEdit->setObjectName("fromLineEdit");
        fromLineEdit->setGeometry(QRect(110, 30, 113, 20));
        toLineEdit = new QLineEdit(groupBox_2);
        toLineEdit->setObjectName("toLineEdit");
        toLineEdit->setGeometry(QRect(110, 70, 113, 20));
        weightLabel = new QLabel(groupBox_2);
        weightLabel->setObjectName("weightLabel");
        weightLabel->setGeometry(QRect(10, 110, 71, 16));
        weightLabel->setFont(font);
        weightLineEdit = new QLineEdit(groupBox_2);
        weightLineEdit->setObjectName("weightLineEdit");
        weightLineEdit->setGeometry(QRect(110, 110, 113, 20));
        addButton = new QPushButton(groupBox_2);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(10, 140, 91, 24));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font2.setPointSize(9);
        font2.setBold(false);
        addButton->setFont(font2);
        delButton = new QPushButton(groupBox_2);
        delButton->setObjectName("delButton");
        delButton->setGeometry(QRect(134, 140, 91, 24));
        delButton->setFont(font2);
        finishButton = new QPushButton(centralwidget);
        finishButton->setObjectName("finishButton");
        finishButton->setGeometry(QRect(686, 495, 75, 24));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(570, 350, 191, 131));
        groupBox_3->setFont(font1);
        vexLabel = new QLabel(groupBox_3);
        vexLabel->setObjectName("vexLabel");
        vexLabel->setGeometry(QRect(10, 30, 71, 16));
        vexLabel->setFont(font);
        edgeLabel = new QLabel(groupBox_3);
        edgeLabel->setObjectName("edgeLabel");
        edgeLabel->setGeometry(QRect(10, 70, 71, 16));
        edgeLabel->setFont(font);
        vexNumLabel = new QLabel(groupBox_3);
        vexNumLabel->setObjectName("vexNumLabel");
        vexNumLabel->setGeometry(QRect(100, 30, 71, 16));
        vexNumLabel->setFont(font);
        edgeNumLabel = new QLabel(groupBox_3);
        edgeNumLabel->setObjectName("edgeNumLabel");
        edgeNumLabel->setGeometry(QRect(100, 70, 71, 16));
        edgeNumLabel->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(570, 495, 101, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font3.setPointSize(11);
        font3.setBold(true);
        label_2->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 771, 22));
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
        label->setText(QCoreApplication::translate("MainWindow", "\345\234\250\344\273\245\344\270\213\345\214\272\345\237\237\347\273\230\345\210\266AOE\347\275\221\347\273\234", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\351\202\273\346\216\245\351\223\276\350\241\250", nullptr));
        cancelButton->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\347\275\221\347\273\234\347\232\204\350\276\271", nullptr));
        fromLabel->setText(QCoreApplication::translate("MainWindow", "\345\211\215\351\251\261\351\241\266\347\202\271", nullptr));
        toLabel->setText(QCoreApplication::translate("MainWindow", "\345\220\216\347\273\247\351\241\266\347\202\271", nullptr));
        weightLabel->setText(QCoreApplication::translate("MainWindow", "\346\235\203\351\207\215\345\200\274", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\276\271", nullptr));
        delButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\276\271", nullptr));
        finishButton->setText(QCoreApplication::translate("MainWindow", "\346\236\204\345\273\272\345\256\214\346\257\225", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\351\241\266\347\202\271/\350\276\271\347\273\237\350\256\241", nullptr));
        vexLabel->setText(QCoreApplication::translate("MainWindow", "\351\241\266\347\202\271\346\225\260", nullptr));
        edgeLabel->setText(QCoreApplication::translate("MainWindow", "\350\276\271\346\225\260", nullptr));
        vexNumLabel->setText(QString());
        edgeNumLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\233\267\350\276\276 2352036", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
