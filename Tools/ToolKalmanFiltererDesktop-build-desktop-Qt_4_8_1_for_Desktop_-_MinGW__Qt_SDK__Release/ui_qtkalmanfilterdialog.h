/********************************************************************************
** Form generated from reading UI file 'qtkalmanfilterdialog.ui'
**
** Created: Fri 7. Jun 11:45:53 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTERDIALOG_H
#define UI_QTKALMANFILTERDIALOG_H

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

class Ui_QtKalmanFilterDialog
{
public:
    QGridLayout *gridLayout;
    QComboBox *box_filter_type;
    QHBoxLayout *horizontalLayout;
    QLabel *label_estimated_lag;
    QSpinBox *box_estimated_lag;
    QPushButton *button_calculate_optimal_kalman_gain_steady_state;

    void setupUi(QDialog *QtKalmanFilterDialog)
    {
        if (QtKalmanFilterDialog->objectName().isEmpty())
            QtKalmanFilterDialog->setObjectName(QString::fromUtf8("QtKalmanFilterDialog"));
        QtKalmanFilterDialog->resize(222, 106);
        gridLayout = new QGridLayout(QtKalmanFilterDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        box_filter_type = new QComboBox(QtKalmanFilterDialog);
        box_filter_type->setObjectName(QString::fromUtf8("box_filter_type"));

        gridLayout->addWidget(box_filter_type, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_estimated_lag = new QLabel(QtKalmanFilterDialog);
        label_estimated_lag->setObjectName(QString::fromUtf8("label_estimated_lag"));

        horizontalLayout->addWidget(label_estimated_lag);

        box_estimated_lag = new QSpinBox(QtKalmanFilterDialog);
        box_estimated_lag->setObjectName(QString::fromUtf8("box_estimated_lag"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(box_estimated_lag->sizePolicy().hasHeightForWidth());
        box_estimated_lag->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(box_estimated_lag);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        button_calculate_optimal_kalman_gain_steady_state = new QPushButton(QtKalmanFilterDialog);
        button_calculate_optimal_kalman_gain_steady_state->setObjectName(QString::fromUtf8("button_calculate_optimal_kalman_gain_steady_state"));

        gridLayout->addWidget(button_calculate_optimal_kalman_gain_steady_state, 2, 0, 1, 1);


        retranslateUi(QtKalmanFilterDialog);

        QMetaObject::connectSlotsByName(QtKalmanFilterDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFilterDialog)
    {
        QtKalmanFilterDialog->setWindowTitle(QApplication::translate("QtKalmanFilterDialog", "QtKalmanFilterDialog", 0, QApplication::UnicodeUTF8));
        box_filter_type->clear();
        box_filter_type->insertItems(0, QStringList()
         << QApplication::translate("QtKalmanFilterDialog", "Standard Kalman filter", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtKalmanFilterDialog", "Steady state Kalman filter", 0, QApplication::UnicodeUTF8)
        );
        label_estimated_lag->setText(QApplication::translate("QtKalmanFilterDialog", "Estimated lag", 0, QApplication::UnicodeUTF8));
        button_calculate_optimal_kalman_gain_steady_state->setText(QApplication::translate("QtKalmanFilterDialog", "Calculate optimal Kalman gain\n"
"(from standard Kalman filter parameters)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFilterDialog: public Ui_QtKalmanFilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTERDIALOG_H
