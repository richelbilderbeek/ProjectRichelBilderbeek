/********************************************************************************
** Form generated from reading UI file 'qtdialog.ui'
**
** Created: Wed May 29 16:58:44 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDIALOG_H
#define UI_QTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_QtDialog
{
public:
    QGridLayout *gridLayout_2;
    QwtPlot *plot;
    QGroupBox *groupBox_general;
    QGridLayout *gridLayout_6;
    QLabel *label_timesteps;
    QSpinBox *box_timesteps;
    QPushButton *button_rerun;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_noise_mean;
    QLineEdit *edit_noise;
    QGroupBox *groupbox_alpha;
    QGridLayout *gridLayout;
    QLabel *label_alpha_a;
    QDoubleSpinBox *box_alpha_a;
    QLabel *label_dt_a;
    QSpacerItem *verticalSpacer;
    QLabel *label_value_dt_a;
    QGroupBox *groupbox_beta;
    QGridLayout *gridLayout_4;
    QLabel *label_alpha_ab;
    QLabel *label_beta_ab;
    QLabel *label_dt_ab;
    QDoubleSpinBox *box_beta_ab;
    QLabel *label_value_dt_ab;
    QDoubleSpinBox *box_alpha_ab;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupbox_abg;
    QGridLayout *gridLayout_7;
    QLabel *label_alpha_abg;
    QLabel *label_beta_abg;
    QLabel *label_dt_abg;
    QDoubleSpinBox *box_beta_abg;
    QLabel *label_value_dt_abg;
    QDoubleSpinBox *box_alpha_abg;
    QDoubleSpinBox *box_gamma_abg;
    QLabel *label_gamma_ang;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_ma;
    QGridLayout *gridLayout_5;
    QLabel *label_ma_2;
    QDoubleSpinBox *box_ma_2;
    QDoubleSpinBox *box_ma_1;
    QLabel *label_ma_1;
    QLabel *label_dt_ma;
    QLabel *label_value_dt_ma;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupbox_lsq;
    QGridLayout *gridLayout_3;
    QLabel *label_title_shift;
    QLabel *label_value_shift;
    QSlider *slider_shift;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *QtDialog)
    {
        if (QtDialog->objectName().isEmpty())
            QtDialog->setObjectName(QString::fromUtf8("QtDialog"));
        QtDialog->resize(1191, 671);
        gridLayout_2 = new QGridLayout(QtDialog);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        plot = new QwtPlot(QtDialog);
        plot->setObjectName(QString::fromUtf8("plot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(3);
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(plot, 0, 0, 1, 6);

        groupBox_general = new QGroupBox(QtDialog);
        groupBox_general->setObjectName(QString::fromUtf8("groupBox_general"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_general->sizePolicy().hasHeightForWidth());
        groupBox_general->setSizePolicy(sizePolicy1);
        gridLayout_6 = new QGridLayout(groupBox_general);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_timesteps = new QLabel(groupBox_general);
        label_timesteps->setObjectName(QString::fromUtf8("label_timesteps"));

        gridLayout_6->addWidget(label_timesteps, 1, 0, 1, 1);

        box_timesteps = new QSpinBox(groupBox_general);
        box_timesteps->setObjectName(QString::fromUtf8("box_timesteps"));
        box_timesteps->setMaximum(1000000);
        box_timesteps->setValue(250);

        gridLayout_6->addWidget(box_timesteps, 1, 1, 1, 1);

        button_rerun = new QPushButton(groupBox_general);
        button_rerun->setObjectName(QString::fromUtf8("button_rerun"));

        gridLayout_6->addWidget(button_rerun, 0, 0, 1, 2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_5, 4, 1, 1, 1);

        label_noise_mean = new QLabel(groupBox_general);
        label_noise_mean->setObjectName(QString::fromUtf8("label_noise_mean"));

        gridLayout_6->addWidget(label_noise_mean, 2, 0, 1, 2);

        edit_noise = new QLineEdit(groupBox_general);
        edit_noise->setObjectName(QString::fromUtf8("edit_noise"));

        gridLayout_6->addWidget(edit_noise, 3, 0, 1, 2);


        gridLayout_2->addWidget(groupBox_general, 1, 0, 1, 1);

        groupbox_alpha = new QGroupBox(QtDialog);
        groupbox_alpha->setObjectName(QString::fromUtf8("groupbox_alpha"));
        sizePolicy1.setHeightForWidth(groupbox_alpha->sizePolicy().hasHeightForWidth());
        groupbox_alpha->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(groupbox_alpha);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_alpha_a = new QLabel(groupbox_alpha);
        label_alpha_a->setObjectName(QString::fromUtf8("label_alpha_a"));

        gridLayout->addWidget(label_alpha_a, 0, 0, 1, 1);

        box_alpha_a = new QDoubleSpinBox(groupbox_alpha);
        box_alpha_a->setObjectName(QString::fromUtf8("box_alpha_a"));
        box_alpha_a->setDecimals(10);
        box_alpha_a->setMaximum(1);
        box_alpha_a->setSingleStep(0.001);
        box_alpha_a->setValue(0.03);

        gridLayout->addWidget(box_alpha_a, 0, 1, 1, 1);

        label_dt_a = new QLabel(groupbox_alpha);
        label_dt_a->setObjectName(QString::fromUtf8("label_dt_a"));

        gridLayout->addWidget(label_dt_a, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        label_value_dt_a = new QLabel(groupbox_alpha);
        label_value_dt_a->setObjectName(QString::fromUtf8("label_value_dt_a"));

        gridLayout->addWidget(label_value_dt_a, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupbox_alpha, 1, 1, 1, 1);

        groupbox_beta = new QGroupBox(QtDialog);
        groupbox_beta->setObjectName(QString::fromUtf8("groupbox_beta"));
        sizePolicy1.setHeightForWidth(groupbox_beta->sizePolicy().hasHeightForWidth());
        groupbox_beta->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(groupbox_beta);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_alpha_ab = new QLabel(groupbox_beta);
        label_alpha_ab->setObjectName(QString::fromUtf8("label_alpha_ab"));

        gridLayout_4->addWidget(label_alpha_ab, 0, 0, 1, 1);

        label_beta_ab = new QLabel(groupbox_beta);
        label_beta_ab->setObjectName(QString::fromUtf8("label_beta_ab"));

        gridLayout_4->addWidget(label_beta_ab, 1, 0, 1, 1);

        label_dt_ab = new QLabel(groupbox_beta);
        label_dt_ab->setObjectName(QString::fromUtf8("label_dt_ab"));

        gridLayout_4->addWidget(label_dt_ab, 3, 0, 1, 1);

        box_beta_ab = new QDoubleSpinBox(groupbox_beta);
        box_beta_ab->setObjectName(QString::fromUtf8("box_beta_ab"));
        box_beta_ab->setDecimals(10);
        box_beta_ab->setMaximum(2);
        box_beta_ab->setSingleStep(0.0001);
        box_beta_ab->setValue(1e-05);

        gridLayout_4->addWidget(box_beta_ab, 1, 1, 1, 2);

        label_value_dt_ab = new QLabel(groupbox_beta);
        label_value_dt_ab->setObjectName(QString::fromUtf8("label_value_dt_ab"));

        gridLayout_4->addWidget(label_value_dt_ab, 3, 1, 1, 2);

        box_alpha_ab = new QDoubleSpinBox(groupbox_beta);
        box_alpha_ab->setObjectName(QString::fromUtf8("box_alpha_ab"));
        box_alpha_ab->setDecimals(10);
        box_alpha_ab->setMaximum(1);
        box_alpha_ab->setSingleStep(0.001);
        box_alpha_ab->setValue(0.03);

        gridLayout_4->addWidget(box_alpha_ab, 0, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupbox_beta, 1, 2, 1, 1);

        groupbox_abg = new QGroupBox(QtDialog);
        groupbox_abg->setObjectName(QString::fromUtf8("groupbox_abg"));
        sizePolicy1.setHeightForWidth(groupbox_abg->sizePolicy().hasHeightForWidth());
        groupbox_abg->setSizePolicy(sizePolicy1);
        gridLayout_7 = new QGridLayout(groupbox_abg);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_alpha_abg = new QLabel(groupbox_abg);
        label_alpha_abg->setObjectName(QString::fromUtf8("label_alpha_abg"));

        gridLayout_7->addWidget(label_alpha_abg, 0, 0, 1, 1);

        label_beta_abg = new QLabel(groupbox_abg);
        label_beta_abg->setObjectName(QString::fromUtf8("label_beta_abg"));

        gridLayout_7->addWidget(label_beta_abg, 1, 0, 1, 1);

        label_dt_abg = new QLabel(groupbox_abg);
        label_dt_abg->setObjectName(QString::fromUtf8("label_dt_abg"));

        gridLayout_7->addWidget(label_dt_abg, 4, 0, 1, 1);

        box_beta_abg = new QDoubleSpinBox(groupbox_abg);
        box_beta_abg->setObjectName(QString::fromUtf8("box_beta_abg"));
        box_beta_abg->setDecimals(10);
        box_beta_abg->setMaximum(2);
        box_beta_abg->setSingleStep(0.001);
        box_beta_abg->setValue(1e-05);

        gridLayout_7->addWidget(box_beta_abg, 1, 1, 1, 2);

        label_value_dt_abg = new QLabel(groupbox_abg);
        label_value_dt_abg->setObjectName(QString::fromUtf8("label_value_dt_abg"));

        gridLayout_7->addWidget(label_value_dt_abg, 4, 1, 1, 2);

        box_alpha_abg = new QDoubleSpinBox(groupbox_abg);
        box_alpha_abg->setObjectName(QString::fromUtf8("box_alpha_abg"));
        box_alpha_abg->setDecimals(10);
        box_alpha_abg->setMaximum(1);
        box_alpha_abg->setSingleStep(0.001);
        box_alpha_abg->setValue(0.03);

        gridLayout_7->addWidget(box_alpha_abg, 0, 1, 1, 2);

        box_gamma_abg = new QDoubleSpinBox(groupbox_abg);
        box_gamma_abg->setObjectName(QString::fromUtf8("box_gamma_abg"));
        box_gamma_abg->setDecimals(10);
        box_gamma_abg->setMaximum(2);
        box_gamma_abg->setSingleStep(0.0001);
        box_gamma_abg->setValue(1e-06);

        gridLayout_7->addWidget(box_gamma_abg, 2, 1, 1, 2);

        label_gamma_ang = new QLabel(groupbox_abg);
        label_gamma_ang->setObjectName(QString::fromUtf8("label_gamma_ang"));

        gridLayout_7->addWidget(label_gamma_ang, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_3, 3, 1, 1, 1);


        gridLayout_2->addWidget(groupbox_abg, 1, 3, 1, 1);

        groupBox_ma = new QGroupBox(QtDialog);
        groupBox_ma->setObjectName(QString::fromUtf8("groupBox_ma"));
        sizePolicy1.setHeightForWidth(groupBox_ma->sizePolicy().hasHeightForWidth());
        groupBox_ma->setSizePolicy(sizePolicy1);
        gridLayout_5 = new QGridLayout(groupBox_ma);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_ma_2 = new QLabel(groupBox_ma);
        label_ma_2->setObjectName(QString::fromUtf8("label_ma_2"));

        gridLayout_5->addWidget(label_ma_2, 1, 0, 1, 1);

        box_ma_2 = new QDoubleSpinBox(groupBox_ma);
        box_ma_2->setObjectName(QString::fromUtf8("box_ma_2"));
        box_ma_2->setDecimals(10);
        box_ma_2->setMaximum(1);
        box_ma_2->setSingleStep(0.01);
        box_ma_2->setValue(0.0625);

        gridLayout_5->addWidget(box_ma_2, 1, 1, 1, 1);

        box_ma_1 = new QDoubleSpinBox(groupBox_ma);
        box_ma_1->setObjectName(QString::fromUtf8("box_ma_1"));
        box_ma_1->setDecimals(10);
        box_ma_1->setMaximum(1);
        box_ma_1->setSingleStep(0.01);
        box_ma_1->setValue(0.0625);

        gridLayout_5->addWidget(box_ma_1, 0, 1, 1, 1);

        label_ma_1 = new QLabel(groupBox_ma);
        label_ma_1->setObjectName(QString::fromUtf8("label_ma_1"));

        gridLayout_5->addWidget(label_ma_1, 0, 0, 1, 1);

        label_dt_ma = new QLabel(groupBox_ma);
        label_dt_ma->setObjectName(QString::fromUtf8("label_dt_ma"));

        gridLayout_5->addWidget(label_dt_ma, 3, 0, 1, 1);

        label_value_dt_ma = new QLabel(groupBox_ma);
        label_value_dt_ma->setObjectName(QString::fromUtf8("label_value_dt_ma"));

        gridLayout_5->addWidget(label_value_dt_ma, 3, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_4, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_ma, 1, 4, 1, 1);

        groupbox_lsq = new QGroupBox(QtDialog);
        groupbox_lsq->setObjectName(QString::fromUtf8("groupbox_lsq"));
        sizePolicy1.setHeightForWidth(groupbox_lsq->sizePolicy().hasHeightForWidth());
        groupbox_lsq->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(groupbox_lsq);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_title_shift = new QLabel(groupbox_lsq);
        label_title_shift->setObjectName(QString::fromUtf8("label_title_shift"));

        gridLayout_3->addWidget(label_title_shift, 0, 0, 1, 1);

        label_value_shift = new QLabel(groupbox_lsq);
        label_value_shift->setObjectName(QString::fromUtf8("label_value_shift"));

        gridLayout_3->addWidget(label_value_shift, 0, 2, 1, 1);

        slider_shift = new QSlider(groupbox_lsq);
        slider_shift->setObjectName(QString::fromUtf8("slider_shift"));
        slider_shift->setMaximum(31);
        slider_shift->setValue(4);
        slider_shift->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(slider_shift, 0, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupbox_lsq, 1, 5, 1, 1);

        QWidget::setTabOrder(button_rerun, box_timesteps);
        QWidget::setTabOrder(box_timesteps, box_alpha_a);
        QWidget::setTabOrder(box_alpha_a, box_alpha_ab);
        QWidget::setTabOrder(box_alpha_ab, box_beta_ab);
        QWidget::setTabOrder(box_beta_ab, box_alpha_abg);
        QWidget::setTabOrder(box_alpha_abg, box_beta_abg);
        QWidget::setTabOrder(box_beta_abg, box_gamma_abg);
        QWidget::setTabOrder(box_gamma_abg, box_ma_1);
        QWidget::setTabOrder(box_ma_1, box_ma_2);
        QWidget::setTabOrder(box_ma_2, slider_shift);

        retranslateUi(QtDialog);

        QMetaObject::connectSlotsByName(QtDialog);
    } // setupUi

    void retranslateUi(QDialog *QtDialog)
    {
        QtDialog->setWindowTitle(QApplication::translate("QtDialog", "StateObservers", 0, QApplication::UnicodeUTF8));
        groupBox_general->setTitle(QApplication::translate("QtDialog", "General", 0, QApplication::UnicodeUTF8));
        label_timesteps->setText(QApplication::translate("QtDialog", "Timesteps", 0, QApplication::UnicodeUTF8));
        button_rerun->setText(QApplication::translate("QtDialog", "Rerun", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_noise_mean->setToolTip(QApplication::translate("QtDialog", "The value that would be measured without noise", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_noise_mean->setText(QApplication::translate("QtDialog", "Noise", 0, QApplication::UnicodeUTF8));
        edit_noise->setText(QApplication::translate("QtDialog", "100-(0.5*t)+rand(t)", 0, QApplication::UnicodeUTF8));
        groupbox_alpha->setTitle(QApplication::translate("QtDialog", "Alpha filter", 0, QApplication::UnicodeUTF8));
        label_alpha_a->setText(QApplication::translate("QtDialog", "Alpha", 0, QApplication::UnicodeUTF8));
        label_dt_a->setText(QApplication::translate("QtDialog", "dt", 0, QApplication::UnicodeUTF8));
        label_value_dt_a->setText(QApplication::translate("QtDialog", "1.0", 0, QApplication::UnicodeUTF8));
        groupbox_beta->setTitle(QApplication::translate("QtDialog", "Alpha beta filter", 0, QApplication::UnicodeUTF8));
        label_alpha_ab->setText(QApplication::translate("QtDialog", "Alpha", 0, QApplication::UnicodeUTF8));
        label_beta_ab->setText(QApplication::translate("QtDialog", "Beta", 0, QApplication::UnicodeUTF8));
        label_dt_ab->setText(QApplication::translate("QtDialog", "dt", 0, QApplication::UnicodeUTF8));
        label_value_dt_ab->setText(QApplication::translate("QtDialog", "as used in alpha filter", 0, QApplication::UnicodeUTF8));
        groupbox_abg->setTitle(QApplication::translate("QtDialog", "Alpha beta gamma filter", 0, QApplication::UnicodeUTF8));
        label_alpha_abg->setText(QApplication::translate("QtDialog", "Alpha", 0, QApplication::UnicodeUTF8));
        label_beta_abg->setText(QApplication::translate("QtDialog", "Beta", 0, QApplication::UnicodeUTF8));
        label_dt_abg->setText(QApplication::translate("QtDialog", "dt", 0, QApplication::UnicodeUTF8));
        label_value_dt_abg->setText(QApplication::translate("QtDialog", "as used in alpha filter", 0, QApplication::UnicodeUTF8));
        label_gamma_ang->setText(QApplication::translate("QtDialog", "Gamma", 0, QApplication::UnicodeUTF8));
        groupBox_ma->setTitle(QApplication::translate("QtDialog", "Multi alpha filter", 0, QApplication::UnicodeUTF8));
        label_ma_2->setText(QApplication::translate("QtDialog", "Alpha 2", 0, QApplication::UnicodeUTF8));
        label_ma_1->setText(QApplication::translate("QtDialog", "Alpha 1", 0, QApplication::UnicodeUTF8));
        label_dt_ma->setText(QApplication::translate("QtDialog", "dt", 0, QApplication::UnicodeUTF8));
        label_value_dt_ma->setText(QApplication::translate("QtDialog", "as used in alpha filter", 0, QApplication::UnicodeUTF8));
        groupbox_lsq->setTitle(QApplication::translate("QtDialog", "LSQ filter", 0, QApplication::UnicodeUTF8));
        label_title_shift->setText(QApplication::translate("QtDialog", "Shift", 0, QApplication::UnicodeUTF8));
        label_value_shift->setText(QApplication::translate("QtDialog", "0.0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtDialog: public Ui_QtDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDIALOG_H
