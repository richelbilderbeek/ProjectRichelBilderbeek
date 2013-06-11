/********************************************************************************
** Form generated from reading UI file 'qtsteadystatekalmanfiltercalculationdialog.ui'
**
** Created: Mon 10. Jun 14:15:15 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H
#define UI_QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtSteadyStateKalmanFilterCalculationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_time;
    QWidget *widget_1;
    QGridLayout *gridLayout;
    QLabel *label_title_1;
    QLabel *label_top_1_1;
    QLabel *label_top_2_1;
    QLabel *label_top_3_1;
    QLabel *label_top_4_1;
    QLabel *label_top_5_1;
    QLabel *label_top_6_1;
    QLabel *label_top_7_1;
    QLabel *label_top_8_1;
    QLabel *label_top_9_1;
    QTableWidget *table_state_predicted;
    QLabel *label_math_1;
    QTableWidget *table_state_transition;
    QLabel *label_math_2;
    QTableWidget *table_gain_1;
    QTableWidget *table_observation_model;
    QLabel *label_math_3;
    QTableWidget *table_previous_state_estimate;
    QLabel *label_math_4;
    QTableWidget *table_control;
    QTableWidget *table_input;
    QLabel *label_math_5;
    QTableWidget *table_gain_2;
    QTableWidget *table_measurement;
    QLabel *label_bottom_1_1;
    QLabel *label_bottom_2_1;
    QLabel *label_bottom_3_1;
    QLabel *label_bottom_4_1;
    QLabel *label_bottom_5_1;
    QLabel *label_bottom_6_1;
    QLabel *label_bottom_7_1;
    QLabel *label_bottom_8;
    QLabel *label_bottom_9;

    void setupUi(QDialog *QtSteadyStateKalmanFilterCalculationDialog)
    {
        if (QtSteadyStateKalmanFilterCalculationDialog->objectName().isEmpty())
            QtSteadyStateKalmanFilterCalculationDialog->setObjectName(QString::fromUtf8("QtSteadyStateKalmanFilterCalculationDialog"));
        QtSteadyStateKalmanFilterCalculationDialog->resize(1172, 187);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtSteadyStateKalmanFilterCalculationDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(QtSteadyStateKalmanFilterCalculationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_time = new QLabel(QtSteadyStateKalmanFilterCalculationDialog);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout->addWidget(label_time);

        widget_1 = new QWidget(QtSteadyStateKalmanFilterCalculationDialog);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        gridLayout = new QGridLayout(widget_1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_title_1 = new QLabel(widget_1);
        label_title_1->setObjectName(QString::fromUtf8("label_title_1"));

        gridLayout->addWidget(label_title_1, 0, 0, 1, 2);

        label_top_1_1 = new QLabel(widget_1);
        label_top_1_1->setObjectName(QString::fromUtf8("label_top_1_1"));

        gridLayout->addWidget(label_top_1_1, 1, 0, 1, 1);

        label_top_2_1 = new QLabel(widget_1);
        label_top_2_1->setObjectName(QString::fromUtf8("label_top_2_1"));

        gridLayout->addWidget(label_top_2_1, 1, 2, 1, 1);

        label_top_3_1 = new QLabel(widget_1);
        label_top_3_1->setObjectName(QString::fromUtf8("label_top_3_1"));

        gridLayout->addWidget(label_top_3_1, 1, 4, 1, 1);

        label_top_4_1 = new QLabel(widget_1);
        label_top_4_1->setObjectName(QString::fromUtf8("label_top_4_1"));

        gridLayout->addWidget(label_top_4_1, 1, 5, 1, 1);

        label_top_5_1 = new QLabel(widget_1);
        label_top_5_1->setObjectName(QString::fromUtf8("label_top_5_1"));

        gridLayout->addWidget(label_top_5_1, 1, 7, 1, 1);

        label_top_6_1 = new QLabel(widget_1);
        label_top_6_1->setObjectName(QString::fromUtf8("label_top_6_1"));

        gridLayout->addWidget(label_top_6_1, 1, 9, 1, 1);

        label_top_7_1 = new QLabel(widget_1);
        label_top_7_1->setObjectName(QString::fromUtf8("label_top_7_1"));

        gridLayout->addWidget(label_top_7_1, 1, 10, 1, 1);

        label_top_8_1 = new QLabel(widget_1);
        label_top_8_1->setObjectName(QString::fromUtf8("label_top_8_1"));

        gridLayout->addWidget(label_top_8_1, 1, 12, 1, 1);

        label_top_9_1 = new QLabel(widget_1);
        label_top_9_1->setObjectName(QString::fromUtf8("label_top_9_1"));

        gridLayout->addWidget(label_top_9_1, 1, 13, 1, 1);

        table_state_predicted = new QTableWidget(widget_1);
        if (table_state_predicted->columnCount() < 1)
            table_state_predicted->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_state_predicted->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (table_state_predicted->rowCount() < 1)
            table_state_predicted->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_state_predicted->setVerticalHeaderItem(0, __qtablewidgetitem1);
        table_state_predicted->setObjectName(QString::fromUtf8("table_state_predicted"));

        gridLayout->addWidget(table_state_predicted, 2, 0, 1, 1);

        label_math_1 = new QLabel(widget_1);
        label_math_1->setObjectName(QString::fromUtf8("label_math_1"));

        gridLayout->addWidget(label_math_1, 2, 1, 1, 1);

        table_state_transition = new QTableWidget(widget_1);
        if (table_state_transition->columnCount() < 1)
            table_state_transition->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_state_transition->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        if (table_state_transition->rowCount() < 1)
            table_state_transition->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_state_transition->setVerticalHeaderItem(0, __qtablewidgetitem3);
        table_state_transition->setObjectName(QString::fromUtf8("table_state_transition"));

        gridLayout->addWidget(table_state_transition, 2, 2, 1, 1);

        label_math_2 = new QLabel(widget_1);
        label_math_2->setObjectName(QString::fromUtf8("label_math_2"));

        gridLayout->addWidget(label_math_2, 2, 3, 1, 1);

        table_gain_1 = new QTableWidget(widget_1);
        if (table_gain_1->columnCount() < 1)
            table_gain_1->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_gain_1->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        if (table_gain_1->rowCount() < 1)
            table_gain_1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table_gain_1->setVerticalHeaderItem(0, __qtablewidgetitem5);
        table_gain_1->setObjectName(QString::fromUtf8("table_gain_1"));

        gridLayout->addWidget(table_gain_1, 2, 4, 1, 1);

        table_observation_model = new QTableWidget(widget_1);
        if (table_observation_model->columnCount() < 1)
            table_observation_model->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table_observation_model->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        if (table_observation_model->rowCount() < 1)
            table_observation_model->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        table_observation_model->setVerticalHeaderItem(0, __qtablewidgetitem7);
        table_observation_model->setObjectName(QString::fromUtf8("table_observation_model"));

        gridLayout->addWidget(table_observation_model, 2, 5, 1, 1);

        label_math_3 = new QLabel(widget_1);
        label_math_3->setObjectName(QString::fromUtf8("label_math_3"));

        gridLayout->addWidget(label_math_3, 2, 6, 1, 1);

        table_previous_state_estimate = new QTableWidget(widget_1);
        if (table_previous_state_estimate->columnCount() < 1)
            table_previous_state_estimate->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        table_previous_state_estimate->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        if (table_previous_state_estimate->rowCount() < 1)
            table_previous_state_estimate->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        table_previous_state_estimate->setVerticalHeaderItem(0, __qtablewidgetitem9);
        table_previous_state_estimate->setObjectName(QString::fromUtf8("table_previous_state_estimate"));

        gridLayout->addWidget(table_previous_state_estimate, 2, 7, 1, 1);

        label_math_4 = new QLabel(widget_1);
        label_math_4->setObjectName(QString::fromUtf8("label_math_4"));

        gridLayout->addWidget(label_math_4, 2, 8, 1, 1);

        table_control = new QTableWidget(widget_1);
        if (table_control->columnCount() < 1)
            table_control->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        table_control->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        if (table_control->rowCount() < 1)
            table_control->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        table_control->setVerticalHeaderItem(0, __qtablewidgetitem11);
        table_control->setObjectName(QString::fromUtf8("table_control"));

        gridLayout->addWidget(table_control, 2, 9, 1, 1);

        table_input = new QTableWidget(widget_1);
        if (table_input->columnCount() < 1)
            table_input->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        table_input->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        if (table_input->rowCount() < 1)
            table_input->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        table_input->setVerticalHeaderItem(0, __qtablewidgetitem13);
        table_input->setObjectName(QString::fromUtf8("table_input"));

        gridLayout->addWidget(table_input, 2, 10, 1, 1);

        label_math_5 = new QLabel(widget_1);
        label_math_5->setObjectName(QString::fromUtf8("label_math_5"));

        gridLayout->addWidget(label_math_5, 2, 11, 1, 1);

        table_gain_2 = new QTableWidget(widget_1);
        if (table_gain_2->columnCount() < 1)
            table_gain_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        table_gain_2->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        if (table_gain_2->rowCount() < 1)
            table_gain_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        table_gain_2->setVerticalHeaderItem(0, __qtablewidgetitem15);
        table_gain_2->setObjectName(QString::fromUtf8("table_gain_2"));

        gridLayout->addWidget(table_gain_2, 2, 12, 1, 1);

        table_measurement = new QTableWidget(widget_1);
        if (table_measurement->columnCount() < 1)
            table_measurement->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        table_measurement->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        if (table_measurement->rowCount() < 1)
            table_measurement->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        table_measurement->setVerticalHeaderItem(0, __qtablewidgetitem17);
        table_measurement->setObjectName(QString::fromUtf8("table_measurement"));

        gridLayout->addWidget(table_measurement, 2, 13, 1, 1);

        label_bottom_1_1 = new QLabel(widget_1);
        label_bottom_1_1->setObjectName(QString::fromUtf8("label_bottom_1_1"));

        gridLayout->addWidget(label_bottom_1_1, 3, 0, 1, 1);

        label_bottom_2_1 = new QLabel(widget_1);
        label_bottom_2_1->setObjectName(QString::fromUtf8("label_bottom_2_1"));

        gridLayout->addWidget(label_bottom_2_1, 3, 2, 1, 1);

        label_bottom_3_1 = new QLabel(widget_1);
        label_bottom_3_1->setObjectName(QString::fromUtf8("label_bottom_3_1"));

        gridLayout->addWidget(label_bottom_3_1, 3, 4, 1, 1);

        label_bottom_4_1 = new QLabel(widget_1);
        label_bottom_4_1->setObjectName(QString::fromUtf8("label_bottom_4_1"));

        gridLayout->addWidget(label_bottom_4_1, 3, 5, 1, 1);

        label_bottom_5_1 = new QLabel(widget_1);
        label_bottom_5_1->setObjectName(QString::fromUtf8("label_bottom_5_1"));

        gridLayout->addWidget(label_bottom_5_1, 3, 7, 1, 1);

        label_bottom_6_1 = new QLabel(widget_1);
        label_bottom_6_1->setObjectName(QString::fromUtf8("label_bottom_6_1"));

        gridLayout->addWidget(label_bottom_6_1, 3, 9, 1, 1);

        label_bottom_7_1 = new QLabel(widget_1);
        label_bottom_7_1->setObjectName(QString::fromUtf8("label_bottom_7_1"));

        gridLayout->addWidget(label_bottom_7_1, 3, 10, 1, 1);

        label_bottom_8 = new QLabel(widget_1);
        label_bottom_8->setObjectName(QString::fromUtf8("label_bottom_8"));

        gridLayout->addWidget(label_bottom_8, 3, 12, 1, 1);

        label_bottom_9 = new QLabel(widget_1);
        label_bottom_9->setObjectName(QString::fromUtf8("label_bottom_9"));

        gridLayout->addWidget(label_bottom_9, 3, 13, 1, 1);


        verticalLayout->addWidget(widget_1);


        retranslateUi(QtSteadyStateKalmanFilterCalculationDialog);

        QMetaObject::connectSlotsByName(QtSteadyStateKalmanFilterCalculationDialog);
    } // setupUi

    void retranslateUi(QDialog *QtSteadyStateKalmanFilterCalculationDialog)
    {
        QtSteadyStateKalmanFilterCalculationDialog->setWindowTitle(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Time: ?", 0, QApplication::UnicodeUTF8));
        label_title_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "1) State prediction", 0, QApplication::UnicodeUTF8));
        label_top_1_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "x_predicted", 0, QApplication::UnicodeUTF8));
        label_top_2_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "A", 0, QApplication::UnicodeUTF8));
        label_top_3_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "K", 0, QApplication::UnicodeUTF8));
        label_top_4_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "C", 0, QApplication::UnicodeUTF8));
        label_top_5_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "x_n-1", 0, QApplication::UnicodeUTF8));
        label_top_6_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "B", 0, QApplication::UnicodeUTF8));
        label_top_7_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "u_n", 0, QApplication::UnicodeUTF8));
        label_top_8_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "K", 0, QApplication::UnicodeUTF8));
        label_top_9_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "y", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = table_state_predicted->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = table_state_predicted->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "= (", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = table_state_transition->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = table_state_transition->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_2->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = table_gain_1->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = table_gain_1->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = table_observation_model->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = table_observation_model->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_3->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", ").", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = table_previous_state_estimate->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = table_previous_state_estimate->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_4->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = table_control->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = table_control->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = table_input->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = table_input->verticalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_5->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = table_gain_2->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = table_gain_2->verticalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = table_measurement->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = table_measurement->verticalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_bottom_1_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Predicted state", 0, QApplication::UnicodeUTF8));
        label_bottom_2_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "State transition matrix", 0, QApplication::UnicodeUTF8));
        label_bottom_3_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Estimated optimal\n"
"Kalman gain", 0, QApplication::UnicodeUTF8));
        label_bottom_4_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Observation\n"
"model", 0, QApplication::UnicodeUTF8));
        label_bottom_5_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Previous\n"
"state estimate", 0, QApplication::UnicodeUTF8));
        label_bottom_6_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Control", 0, QApplication::UnicodeUTF8));
        label_bottom_7_1->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Input", 0, QApplication::UnicodeUTF8));
        label_bottom_8->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Estimated optimal\n"
"Kalman gain", 0, QApplication::UnicodeUTF8));
        label_bottom_9->setText(QApplication::translate("QtSteadyStateKalmanFilterCalculationDialog", "Measurement", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtSteadyStateKalmanFilterCalculationDialog: public Ui_QtSteadyStateKalmanFilterCalculationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H
