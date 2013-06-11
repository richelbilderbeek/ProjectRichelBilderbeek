/********************************************************************************
** Form generated from reading UI file 'qtkalmanfilterexamplesdialog.ui'
**
** Created: Mon 10. Jun 14:15:15 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTEREXAMPLESDIALOG_H
#define UI_QTKALMANFILTEREXAMPLESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QtKalmanFilterExamplesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *button_1;
    QPushButton *button_2;
    QPushButton *button_3;
    QPushButton *button_4;
    QPushButton *button_5;
    QPushButton *button_6;
    QPushButton *button_7;
    QPushButton *button_8;
    QPushButton *button_9;
    QPushButton *button_10;

    void setupUi(QDialog *QtKalmanFilterExamplesDialog)
    {
        if (QtKalmanFilterExamplesDialog->objectName().isEmpty())
            QtKalmanFilterExamplesDialog->setObjectName(QString::fromUtf8("QtKalmanFilterExamplesDialog"));
        QtKalmanFilterExamplesDialog->resize(212, 302);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtKalmanFilterExamplesDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(QtKalmanFilterExamplesDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        button_1 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_1->setObjectName(QString::fromUtf8("button_1"));

        verticalLayout->addWidget(button_1);

        button_2 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_2->setObjectName(QString::fromUtf8("button_2"));

        verticalLayout->addWidget(button_2);

        button_3 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_3->setObjectName(QString::fromUtf8("button_3"));

        verticalLayout->addWidget(button_3);

        button_4 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_4->setObjectName(QString::fromUtf8("button_4"));

        verticalLayout->addWidget(button_4);

        button_5 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_5->setObjectName(QString::fromUtf8("button_5"));

        verticalLayout->addWidget(button_5);

        button_6 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_6->setObjectName(QString::fromUtf8("button_6"));

        verticalLayout->addWidget(button_6);

        button_7 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_7->setObjectName(QString::fromUtf8("button_7"));

        verticalLayout->addWidget(button_7);

        button_8 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_8->setObjectName(QString::fromUtf8("button_8"));

        verticalLayout->addWidget(button_8);

        button_9 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_9->setObjectName(QString::fromUtf8("button_9"));

        verticalLayout->addWidget(button_9);

        button_10 = new QPushButton(QtKalmanFilterExamplesDialog);
        button_10->setObjectName(QString::fromUtf8("button_10"));

        verticalLayout->addWidget(button_10);


        retranslateUi(QtKalmanFilterExamplesDialog);

        QMetaObject::connectSlotsByName(QtKalmanFilterExamplesDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFilterExamplesDialog)
    {
        QtKalmanFilterExamplesDialog->setWindowTitle(QApplication::translate("QtKalmanFilterExamplesDialog", "QtKalmanFilterExamplesDialog", 0, QApplication::UnicodeUTF8));
        button_1->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &1: Voltage", 0, QApplication::UnicodeUTF8));
        button_2->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &2: Accelerating car (2 states)", 0, QApplication::UnicodeUTF8));
        button_3->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &3: Cannonball", 0, QApplication::UnicodeUTF8));
        button_4->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &4: Spring", 0, QApplication::UnicodeUTF8));
        button_5->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &5: Airhockey puck", 0, QApplication::UnicodeUTF8));
        button_6->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &6: System under investigation", 0, QApplication::UnicodeUTF8));
        button_7->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &7: System under investigation", 0, QApplication::UnicodeUTF8));
        button_8->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &8: Accelerating car (3 states)", 0, QApplication::UnicodeUTF8));
        button_9->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example &9: LSQ", 0, QApplication::UnicodeUTF8));
        button_10->setText(QApplication::translate("QtKalmanFilterExamplesDialog", "Example 1&0: SUI with LSQ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFilterExamplesDialog: public Ui_QtKalmanFilterExamplesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTEREXAMPLESDIALOG_H
