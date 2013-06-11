/********************************************************************************
** Form generated from reading UI file 'qtkalmanfiltercalculationdialog.ui'
**
** Created: Mon 10. Jun 09:21:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTERCALCULATIONDIALOG_H
#define UI_QTKALMANFILTERCALCULATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtKalmanFilterCalculationDialog
{
public:

    void setupUi(QDialog *QtKalmanFilterCalculationDialog)
    {
        if (QtKalmanFilterCalculationDialog->objectName().isEmpty())
            QtKalmanFilterCalculationDialog->setObjectName(QString::fromUtf8("QtKalmanFilterCalculationDialog"));
        QtKalmanFilterCalculationDialog->resize(1172, 31);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtKalmanFilterCalculationDialog->setWindowIcon(icon);

        retranslateUi(QtKalmanFilterCalculationDialog);

        QMetaObject::connectSlotsByName(QtKalmanFilterCalculationDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFilterCalculationDialog)
    {
        QtKalmanFilterCalculationDialog->setWindowTitle(QApplication::translate("QtKalmanFilterCalculationDialog", "QtKalmanFilterCalculationDialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFilterCalculationDialog: public Ui_QtKalmanFilterCalculationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTERCALCULATIONDIALOG_H
