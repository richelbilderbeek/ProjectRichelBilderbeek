/********************************************************************************
** Form generated from reading UI file 'qtkalmanfiltererparameterdialog.ui'
**
** Created: Mon 10. Jun 09:21:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTERERPARAMETERDIALOG_H
#define UI_QTKALMANFILTERERPARAMETERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_QtKalmanFiltererParameterDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTableView *table;

    void setupUi(QDialog *QtKalmanFiltererParameterDialog)
    {
        if (QtKalmanFiltererParameterDialog->objectName().isEmpty())
            QtKalmanFiltererParameterDialog->setObjectName(QString::fromUtf8("QtKalmanFiltererParameterDialog"));
        QtKalmanFiltererParameterDialog->resize(235, 107);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtKalmanFiltererParameterDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(QtKalmanFiltererParameterDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(QtKalmanFiltererParameterDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        table = new QTableView(QtKalmanFiltererParameterDialog);
        table->setObjectName(QString::fromUtf8("table"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(table->sizePolicy().hasHeightForWidth());
        table->setSizePolicy(sizePolicy1);
        table->setAlternatingRowColors(true);

        gridLayout->addWidget(table, 1, 0, 1, 2);


        retranslateUi(QtKalmanFiltererParameterDialog);

        QMetaObject::connectSlotsByName(QtKalmanFiltererParameterDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFiltererParameterDialog)
    {
        QtKalmanFiltererParameterDialog->setWindowTitle(QApplication::translate("QtKalmanFiltererParameterDialog", "QtKalmanFilterDialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QtKalmanFiltererParameterDialog", "[description]", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFiltererParameterDialog: public Ui_QtKalmanFiltererParameterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTERERPARAMETERDIALOG_H
