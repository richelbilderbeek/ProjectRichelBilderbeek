/********************************************************************************
** Form generated from reading UI file 'qtkalmanfilterermenudialog.ui'
**
** Created: Mon 10. Jun 09:21:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTERERMENUDIALOG_H
#define UI_QTKALMANFILTERERMENUDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QtKalmanFiltererMenuDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *button_about;
    QPushButton *button_quit;
    QLabel *label_2;
    QPushButton *button_start;

    void setupUi(QDialog *QtKalmanFiltererMenuDialog)
    {
        if (QtKalmanFiltererMenuDialog->objectName().isEmpty())
            QtKalmanFiltererMenuDialog->setObjectName(QString::fromUtf8("QtKalmanFiltererMenuDialog"));
        QtKalmanFiltererMenuDialog->resize(378, 712);
        QFont font;
        font.setPointSize(20);
        QtKalmanFiltererMenuDialog->setFont(font);
        QtKalmanFiltererMenuDialog->setStyleSheet(QString::fromUtf8("QDialog { \n"
"background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0  #808080, stop: 1 #ffffff);\n"
"}\n"
"QPushButton { background-color: rgb(255, 255, 255);  }\n"
"QPushButton { color: rgb(0,0,0); }\n"
"QPushButton { font: 48px, \"monospace\" }"));
        gridLayout = new QGridLayout(QtKalmanFiltererMenuDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        button_about = new QPushButton(QtKalmanFiltererMenuDialog);
        button_about->setObjectName(QString::fromUtf8("button_about"));
        button_about->setFlat(true);

        gridLayout->addWidget(button_about, 2, 0, 1, 1);

        button_quit = new QPushButton(QtKalmanFiltererMenuDialog);
        button_quit->setObjectName(QString::fromUtf8("button_quit"));
        button_quit->setFlat(true);

        gridLayout->addWidget(button_quit, 3, 0, 1, 1);

        label_2 = new QLabel(QtKalmanFiltererMenuDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/ToolKalmanFiltererWelcome.png")));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        button_start = new QPushButton(QtKalmanFiltererMenuDialog);
        button_start->setObjectName(QString::fromUtf8("button_start"));
        button_start->setFlat(true);

        gridLayout->addWidget(button_start, 1, 0, 1, 1);

        QWidget::setTabOrder(button_start, button_about);
        QWidget::setTabOrder(button_about, button_quit);

        retranslateUi(QtKalmanFiltererMenuDialog);

        QMetaObject::connectSlotsByName(QtKalmanFiltererMenuDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFiltererMenuDialog)
    {
        QtKalmanFiltererMenuDialog->setWindowTitle(QApplication::translate("QtKalmanFiltererMenuDialog", "KalmanFilterer", 0, QApplication::UnicodeUTF8));
        button_about->setText(QApplication::translate("QtKalmanFiltererMenuDialog", "About", 0, QApplication::UnicodeUTF8));
        button_quit->setText(QApplication::translate("QtKalmanFiltererMenuDialog", "Quit", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        button_start->setText(QApplication::translate("QtKalmanFiltererMenuDialog", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFiltererMenuDialog: public Ui_QtKalmanFiltererMenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTERERMENUDIALOG_H
