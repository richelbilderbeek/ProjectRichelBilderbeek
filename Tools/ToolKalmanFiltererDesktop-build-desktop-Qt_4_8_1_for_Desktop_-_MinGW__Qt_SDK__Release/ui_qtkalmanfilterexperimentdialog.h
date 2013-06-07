/********************************************************************************
** Form generated from reading UI file 'qtkalmanfilterexperimentdialog.ui'
**
** Created: Fri 7. Jun 11:45:53 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTEREXPERIMENTDIALOG_H
#define UI_QTKALMANFILTEREXPERIMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_QtKalmanFilterExperimentDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_load;
    QPushButton *button_save;
    QComboBox *box_save;
    QHBoxLayout *horizontalLayout;
    QLabel *label_n_timesteps;
    QSpinBox *box_n_timesteps;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_n_states;
    QPushButton *button_add_state;
    QPushButton *button_remove_state;

    void setupUi(QDialog *QtKalmanFilterExperimentDialog)
    {
        if (QtKalmanFilterExperimentDialog->objectName().isEmpty())
            QtKalmanFilterExperimentDialog->setObjectName(QString::fromUtf8("QtKalmanFilterExperimentDialog"));
        QtKalmanFilterExperimentDialog->resize(251, 121);
        gridLayout = new QGridLayout(QtKalmanFilterExperimentDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(QtKalmanFilterExperimentDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_load = new QPushButton(QtKalmanFilterExperimentDialog);
        button_load->setObjectName(QString::fromUtf8("button_load"));

        horizontalLayout_3->addWidget(button_load);

        button_save = new QPushButton(QtKalmanFilterExperimentDialog);
        button_save->setObjectName(QString::fromUtf8("button_save"));

        horizontalLayout_3->addWidget(button_save);

        box_save = new QComboBox(QtKalmanFilterExperimentDialog);
        box_save->setObjectName(QString::fromUtf8("box_save"));

        horizontalLayout_3->addWidget(box_save);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_n_timesteps = new QLabel(QtKalmanFilterExperimentDialog);
        label_n_timesteps->setObjectName(QString::fromUtf8("label_n_timesteps"));

        horizontalLayout->addWidget(label_n_timesteps);

        box_n_timesteps = new QSpinBox(QtKalmanFilterExperimentDialog);
        box_n_timesteps->setObjectName(QString::fromUtf8("box_n_timesteps"));
        box_n_timesteps->setMinimum(1);
        box_n_timesteps->setMaximum(1000000000);
        box_n_timesteps->setValue(2);

        horizontalLayout->addWidget(box_n_timesteps);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_n_states = new QLabel(QtKalmanFilterExperimentDialog);
        label_n_states->setObjectName(QString::fromUtf8("label_n_states"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_n_states->sizePolicy().hasHeightForWidth());
        label_n_states->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_n_states);

        button_add_state = new QPushButton(QtKalmanFilterExperimentDialog);
        button_add_state->setObjectName(QString::fromUtf8("button_add_state"));

        horizontalLayout_2->addWidget(button_add_state);

        button_remove_state = new QPushButton(QtKalmanFilterExperimentDialog);
        button_remove_state->setObjectName(QString::fromUtf8("button_remove_state"));

        horizontalLayout_2->addWidget(button_remove_state);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);


        retranslateUi(QtKalmanFilterExperimentDialog);

        QMetaObject::connectSlotsByName(QtKalmanFilterExperimentDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFilterExperimentDialog)
    {
        QtKalmanFilterExperimentDialog->setWindowTitle(QApplication::translate("QtKalmanFilterExperimentDialog", "KalmanFilterer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "Experiment parameters", 0, QApplication::UnicodeUTF8));
        button_load->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "Load from", 0, QApplication::UnicodeUTF8));
        button_save->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "Save as", 0, QApplication::UnicodeUTF8));
        box_save->clear();
        box_save->insertItems(0, QStringList()
         << QApplication::translate("QtKalmanFilterExperimentDialog", "DokuWiki", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtKalmanFilterExperimentDialog", "HTML", 0, QApplication::UnicodeUTF8)
        );
        label_n_timesteps->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "Timesteps", 0, QApplication::UnicodeUTF8));
        label_n_states->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "States", 0, QApplication::UnicodeUTF8));
        button_add_state->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "Add", 0, QApplication::UnicodeUTF8));
        button_remove_state->setText(QApplication::translate("QtKalmanFilterExperimentDialog", "Remove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFilterExperimentDialog: public Ui_QtKalmanFilterExperimentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTEREXPERIMENTDIALOG_H
