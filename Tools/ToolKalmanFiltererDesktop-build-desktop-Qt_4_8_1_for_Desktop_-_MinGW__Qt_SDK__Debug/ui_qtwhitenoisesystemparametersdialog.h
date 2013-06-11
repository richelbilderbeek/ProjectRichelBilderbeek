/********************************************************************************
** Form generated from reading UI file 'qtwhitenoisesystemparametersdialog.ui'
**
** Created: Mon 10. Jun 14:15:15 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWHITENOISESYSTEMPARAMETERSDIALOG_H
#define UI_QTWHITENOISESYSTEMPARAMETERSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QtWhiteNoiseSystemParametersDialog
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *box_white_noise_system_type;
    QHBoxLayout *horizontalLayout;
    QLabel *label_lag;
    QSpinBox *box_lag;

    void setupUi(QDialog *QtWhiteNoiseSystemParametersDialog)
    {
        if (QtWhiteNoiseSystemParametersDialog->objectName().isEmpty())
            QtWhiteNoiseSystemParametersDialog->setObjectName(QString::fromUtf8("QtWhiteNoiseSystemParametersDialog"));
        QtWhiteNoiseSystemParametersDialog->resize(182, 66);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtWhiteNoiseSystemParametersDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(QtWhiteNoiseSystemParametersDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        box_white_noise_system_type = new QComboBox(QtWhiteNoiseSystemParametersDialog);
        box_white_noise_system_type->setObjectName(QString::fromUtf8("box_white_noise_system_type"));

        verticalLayout->addWidget(box_white_noise_system_type);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_lag = new QLabel(QtWhiteNoiseSystemParametersDialog);
        label_lag->setObjectName(QString::fromUtf8("label_lag"));

        horizontalLayout->addWidget(label_lag);

        box_lag = new QSpinBox(QtWhiteNoiseSystemParametersDialog);
        box_lag->setObjectName(QString::fromUtf8("box_lag"));

        horizontalLayout->addWidget(box_lag);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QtWhiteNoiseSystemParametersDialog);

        box_white_noise_system_type->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(QtWhiteNoiseSystemParametersDialog);
    } // setupUi

    void retranslateUi(QDialog *QtWhiteNoiseSystemParametersDialog)
    {
        QtWhiteNoiseSystemParametersDialog->setWindowTitle(QApplication::translate("QtWhiteNoiseSystemParametersDialog", "QtWhiteNoiseSystemParametersDialog", 0, QApplication::UnicodeUTF8));
        box_white_noise_system_type->clear();
        box_white_noise_system_type->insertItems(0, QStringList()
         << QApplication::translate("QtWhiteNoiseSystemParametersDialog", "Standard white noise system", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtWhiteNoiseSystemParametersDialog", "Lagged white noise system", 0, QApplication::UnicodeUTF8)
        );
        label_lag->setText(QApplication::translate("QtWhiteNoiseSystemParametersDialog", "Lag (timesteps)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtWhiteNoiseSystemParametersDialog: public Ui_QtWhiteNoiseSystemParametersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWHITENOISESYSTEMPARAMETERSDIALOG_H
