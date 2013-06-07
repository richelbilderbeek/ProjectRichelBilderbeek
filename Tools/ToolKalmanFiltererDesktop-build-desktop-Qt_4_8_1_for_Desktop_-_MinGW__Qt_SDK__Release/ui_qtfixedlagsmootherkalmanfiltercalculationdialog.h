/********************************************************************************
** Form generated from reading UI file 'qtfixedlagsmootherkalmanfiltercalculationdialog.ui'
**
** Created: Fri 7. Jun 11:45:52 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTFIXEDLAGSMOOTHERKALMANFILTERCALCULATIONDIALOG_H
#define UI_QTFIXEDLAGSMOOTHERKALMANFILTERCALCULATIONDIALOG_H

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

class Ui_QtFixedLagSmootherKalmanFilterCalculationDialog
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
    QLabel *label_top_8_1;
    QTableWidget *table_state_predicted;
    QLabel *label_math_1;
    QTableWidget *table_state_transition;
    QLabel *label_math_2;
    QTableWidget *table_gain_1;
    QTableWidget *table_observation_model;
    QTableWidget *table_previous_state_estimate;
    QLabel *label_math_5;
    QLabel *label_bottom_1_1;
    QLabel *label_bottom_2_1;
    QLabel *label_bottom_3_1;
    QLabel *label_bottom_4_1;
    QLabel *label_bottom_5_1;
    QLabel *label;
    QLabel *label_math_4;
    QLabel *label_3;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_title_2;
    QLabel *label_top_1_2;
    QLabel *label_top_2_2;
    QLabel *label_top_3_2;
    QLabel *label_top_4_2;
    QLabel *label_top_5_2;
    QLabel *label_top_6_2;
    QLabel *label_top_7_2;
    QLabel *label_top_8_2;
    QTableWidget *table_state_predicted_2;
    QLabel *label_math_6;
    QTableWidget *table_state_transition_2;
    QTableWidget *table_gain_3;
    QTableWidget *table_observation_model_2;
    QTableWidget *table_previous_state_estimate_2;
    QTableWidget *table_control_2;
    QTableWidget *table_input_2;
    QLabel *label_math_10;
    QLabel *label_bottom_1_2;
    QLabel *label_bottom_2_2;
    QLabel *label_bottom_3_2;
    QLabel *label_bottom_4_2;
    QLabel *label_bottom_5_2;
    QLabel *label_bottom_6_2;
    QLabel *label_bottom_7_2;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_7;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_title_3;
    QLabel *label_top_1_3;
    QLabel *label_top_3_3;
    QLabel *label_top_5_3;
    QLabel *label_top_6_3;
    QLabel *label_top_7_3;
    QTableWidget *table_state_predicted_3;
    QLabel *label_math_11;
    QTableWidget *table_state_transition_3;
    QTableWidget *table_gain_5;
    QTableWidget *table_observation_model_3;
    QTableWidget *table_previous_state_estimate_3;
    QLabel *label_math_14;
    QTableWidget *table_control_3;
    QTableWidget *table_input_3;
    QLabel *label_bottom_1_3;
    QLabel *label_bottom_2_3;
    QLabel *label_bottom_3_3;
    QLabel *label_bottom_5_3;
    QLabel *label_bottom_6_3;
    QLabel *label_bottom_7_3;
    QLabel *label_2;

    void setupUi(QDialog *QtFixedLagSmootherKalmanFilterCalculationDialog)
    {
        if (QtFixedLagSmootherKalmanFilterCalculationDialog->objectName().isEmpty())
            QtFixedLagSmootherKalmanFilterCalculationDialog->setObjectName(QString::fromUtf8("QtFixedLagSmootherKalmanFilterCalculationDialog"));
        QtFixedLagSmootherKalmanFilterCalculationDialog->resize(799, 521);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtFixedLagSmootherKalmanFilterCalculationDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(QtFixedLagSmootherKalmanFilterCalculationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_time = new QLabel(QtFixedLagSmootherKalmanFilterCalculationDialog);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout->addWidget(label_time);

        widget_1 = new QWidget(QtFixedLagSmootherKalmanFilterCalculationDialog);
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

        gridLayout->addWidget(label_top_4_1, 1, 6, 1, 1);

        label_top_5_1 = new QLabel(widget_1);
        label_top_5_1->setObjectName(QString::fromUtf8("label_top_5_1"));

        gridLayout->addWidget(label_top_5_1, 1, 7, 1, 1);

        label_top_8_1 = new QLabel(widget_1);
        label_top_8_1->setObjectName(QString::fromUtf8("label_top_8_1"));

        gridLayout->addWidget(label_top_8_1, 1, 11, 1, 1);

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

        gridLayout->addWidget(table_observation_model, 2, 6, 1, 1);

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

        label_math_5 = new QLabel(widget_1);
        label_math_5->setObjectName(QString::fromUtf8("label_math_5"));

        gridLayout->addWidget(label_math_5, 2, 10, 1, 1);

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

        gridLayout->addWidget(label_bottom_4_1, 3, 6, 1, 1);

        label_bottom_5_1 = new QLabel(widget_1);
        label_bottom_5_1->setObjectName(QString::fromUtf8("label_bottom_5_1"));

        gridLayout->addWidget(label_bottom_5_1, 3, 7, 1, 1);

        label = new QLabel(widget_1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 5, 1, 1);

        label_math_4 = new QLabel(widget_1);
        label_math_4->setObjectName(QString::fromUtf8("label_math_4"));

        gridLayout->addWidget(label_math_4, 1, 9, 1, 1);

        label_3 = new QLabel(widget_1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 8, 1, 1);


        verticalLayout->addWidget(widget_1);

        widget_2 = new QWidget(QtFixedLagSmootherKalmanFilterCalculationDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_title_2 = new QLabel(widget_2);
        label_title_2->setObjectName(QString::fromUtf8("label_title_2"));

        gridLayout_2->addWidget(label_title_2, 0, 0, 1, 2);

        label_top_1_2 = new QLabel(widget_2);
        label_top_1_2->setObjectName(QString::fromUtf8("label_top_1_2"));

        gridLayout_2->addWidget(label_top_1_2, 1, 0, 1, 1);

        label_top_2_2 = new QLabel(widget_2);
        label_top_2_2->setObjectName(QString::fromUtf8("label_top_2_2"));

        gridLayout_2->addWidget(label_top_2_2, 1, 2, 1, 1);

        label_top_3_2 = new QLabel(widget_2);
        label_top_3_2->setObjectName(QString::fromUtf8("label_top_3_2"));

        gridLayout_2->addWidget(label_top_3_2, 1, 3, 1, 1);

        label_top_4_2 = new QLabel(widget_2);
        label_top_4_2->setObjectName(QString::fromUtf8("label_top_4_2"));

        gridLayout_2->addWidget(label_top_4_2, 1, 5, 1, 1);

        label_top_5_2 = new QLabel(widget_2);
        label_top_5_2->setObjectName(QString::fromUtf8("label_top_5_2"));

        gridLayout_2->addWidget(label_top_5_2, 1, 6, 1, 1);

        label_top_6_2 = new QLabel(widget_2);
        label_top_6_2->setObjectName(QString::fromUtf8("label_top_6_2"));

        gridLayout_2->addWidget(label_top_6_2, 1, 7, 1, 1);

        label_top_7_2 = new QLabel(widget_2);
        label_top_7_2->setObjectName(QString::fromUtf8("label_top_7_2"));

        gridLayout_2->addWidget(label_top_7_2, 1, 10, 1, 1);

        label_top_8_2 = new QLabel(widget_2);
        label_top_8_2->setObjectName(QString::fromUtf8("label_top_8_2"));

        gridLayout_2->addWidget(label_top_8_2, 1, 12, 1, 1);

        table_state_predicted_2 = new QTableWidget(widget_2);
        if (table_state_predicted_2->columnCount() < 1)
            table_state_predicted_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        table_state_predicted_2->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        if (table_state_predicted_2->rowCount() < 1)
            table_state_predicted_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        table_state_predicted_2->setVerticalHeaderItem(0, __qtablewidgetitem11);
        table_state_predicted_2->setObjectName(QString::fromUtf8("table_state_predicted_2"));

        gridLayout_2->addWidget(table_state_predicted_2, 2, 0, 1, 1);

        label_math_6 = new QLabel(widget_2);
        label_math_6->setObjectName(QString::fromUtf8("label_math_6"));

        gridLayout_2->addWidget(label_math_6, 2, 1, 1, 1);

        table_state_transition_2 = new QTableWidget(widget_2);
        if (table_state_transition_2->columnCount() < 1)
            table_state_transition_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        table_state_transition_2->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        if (table_state_transition_2->rowCount() < 1)
            table_state_transition_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        table_state_transition_2->setVerticalHeaderItem(0, __qtablewidgetitem13);
        table_state_transition_2->setObjectName(QString::fromUtf8("table_state_transition_2"));

        gridLayout_2->addWidget(table_state_transition_2, 2, 2, 1, 1);

        table_gain_3 = new QTableWidget(widget_2);
        if (table_gain_3->columnCount() < 1)
            table_gain_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        table_gain_3->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        if (table_gain_3->rowCount() < 1)
            table_gain_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        table_gain_3->setVerticalHeaderItem(0, __qtablewidgetitem15);
        table_gain_3->setObjectName(QString::fromUtf8("table_gain_3"));

        gridLayout_2->addWidget(table_gain_3, 2, 3, 1, 1);

        table_observation_model_2 = new QTableWidget(widget_2);
        if (table_observation_model_2->columnCount() < 1)
            table_observation_model_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        table_observation_model_2->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        if (table_observation_model_2->rowCount() < 1)
            table_observation_model_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        table_observation_model_2->setVerticalHeaderItem(0, __qtablewidgetitem17);
        table_observation_model_2->setObjectName(QString::fromUtf8("table_observation_model_2"));

        gridLayout_2->addWidget(table_observation_model_2, 2, 5, 1, 1);

        table_previous_state_estimate_2 = new QTableWidget(widget_2);
        if (table_previous_state_estimate_2->columnCount() < 1)
            table_previous_state_estimate_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        table_previous_state_estimate_2->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        if (table_previous_state_estimate_2->rowCount() < 1)
            table_previous_state_estimate_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        table_previous_state_estimate_2->setVerticalHeaderItem(0, __qtablewidgetitem19);
        table_previous_state_estimate_2->setObjectName(QString::fromUtf8("table_previous_state_estimate_2"));

        gridLayout_2->addWidget(table_previous_state_estimate_2, 2, 6, 1, 1);

        table_control_2 = new QTableWidget(widget_2);
        if (table_control_2->columnCount() < 1)
            table_control_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        table_control_2->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        if (table_control_2->rowCount() < 1)
            table_control_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        table_control_2->setVerticalHeaderItem(0, __qtablewidgetitem21);
        table_control_2->setObjectName(QString::fromUtf8("table_control_2"));

        gridLayout_2->addWidget(table_control_2, 2, 7, 1, 1);

        table_input_2 = new QTableWidget(widget_2);
        if (table_input_2->columnCount() < 1)
            table_input_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        table_input_2->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        if (table_input_2->rowCount() < 1)
            table_input_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        table_input_2->setVerticalHeaderItem(0, __qtablewidgetitem23);
        table_input_2->setObjectName(QString::fromUtf8("table_input_2"));

        gridLayout_2->addWidget(table_input_2, 2, 10, 1, 1);

        label_math_10 = new QLabel(widget_2);
        label_math_10->setObjectName(QString::fromUtf8("label_math_10"));

        gridLayout_2->addWidget(label_math_10, 2, 11, 1, 1);

        label_bottom_1_2 = new QLabel(widget_2);
        label_bottom_1_2->setObjectName(QString::fromUtf8("label_bottom_1_2"));

        gridLayout_2->addWidget(label_bottom_1_2, 3, 0, 1, 1);

        label_bottom_2_2 = new QLabel(widget_2);
        label_bottom_2_2->setObjectName(QString::fromUtf8("label_bottom_2_2"));

        gridLayout_2->addWidget(label_bottom_2_2, 3, 2, 1, 1);

        label_bottom_3_2 = new QLabel(widget_2);
        label_bottom_3_2->setObjectName(QString::fromUtf8("label_bottom_3_2"));

        gridLayout_2->addWidget(label_bottom_3_2, 3, 3, 1, 1);

        label_bottom_4_2 = new QLabel(widget_2);
        label_bottom_4_2->setObjectName(QString::fromUtf8("label_bottom_4_2"));

        gridLayout_2->addWidget(label_bottom_4_2, 3, 5, 1, 1);

        label_bottom_5_2 = new QLabel(widget_2);
        label_bottom_5_2->setObjectName(QString::fromUtf8("label_bottom_5_2"));

        gridLayout_2->addWidget(label_bottom_5_2, 3, 6, 1, 1);

        label_bottom_6_2 = new QLabel(widget_2);
        label_bottom_6_2->setObjectName(QString::fromUtf8("label_bottom_6_2"));

        gridLayout_2->addWidget(label_bottom_6_2, 3, 7, 1, 1);

        label_bottom_7_2 = new QLabel(widget_2);
        label_bottom_7_2->setObjectName(QString::fromUtf8("label_bottom_7_2"));

        gridLayout_2->addWidget(label_bottom_7_2, 3, 10, 1, 1);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 4, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 8, 1, 1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 9, 1, 1);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(QtFixedLagSmootherKalmanFilterCalculationDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_title_3 = new QLabel(widget_3);
        label_title_3->setObjectName(QString::fromUtf8("label_title_3"));

        gridLayout_3->addWidget(label_title_3, 0, 0, 1, 2);

        label_top_1_3 = new QLabel(widget_3);
        label_top_1_3->setObjectName(QString::fromUtf8("label_top_1_3"));

        gridLayout_3->addWidget(label_top_1_3, 1, 0, 1, 1);

        label_top_3_3 = new QLabel(widget_3);
        label_top_3_3->setObjectName(QString::fromUtf8("label_top_3_3"));

        gridLayout_3->addWidget(label_top_3_3, 1, 3, 1, 1);

        label_top_5_3 = new QLabel(widget_3);
        label_top_5_3->setObjectName(QString::fromUtf8("label_top_5_3"));

        gridLayout_3->addWidget(label_top_5_3, 1, 6, 1, 1);

        label_top_6_3 = new QLabel(widget_3);
        label_top_6_3->setObjectName(QString::fromUtf8("label_top_6_3"));

        gridLayout_3->addWidget(label_top_6_3, 1, 8, 1, 1);

        label_top_7_3 = new QLabel(widget_3);
        label_top_7_3->setObjectName(QString::fromUtf8("label_top_7_3"));

        gridLayout_3->addWidget(label_top_7_3, 1, 9, 1, 1);

        table_state_predicted_3 = new QTableWidget(widget_3);
        if (table_state_predicted_3->columnCount() < 1)
            table_state_predicted_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        table_state_predicted_3->setHorizontalHeaderItem(0, __qtablewidgetitem24);
        if (table_state_predicted_3->rowCount() < 1)
            table_state_predicted_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        table_state_predicted_3->setVerticalHeaderItem(0, __qtablewidgetitem25);
        table_state_predicted_3->setObjectName(QString::fromUtf8("table_state_predicted_3"));

        gridLayout_3->addWidget(table_state_predicted_3, 2, 0, 1, 1);

        label_math_11 = new QLabel(widget_3);
        label_math_11->setObjectName(QString::fromUtf8("label_math_11"));

        gridLayout_3->addWidget(label_math_11, 2, 1, 1, 1);

        table_state_transition_3 = new QTableWidget(widget_3);
        if (table_state_transition_3->columnCount() < 1)
            table_state_transition_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        table_state_transition_3->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        if (table_state_transition_3->rowCount() < 1)
            table_state_transition_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        table_state_transition_3->setVerticalHeaderItem(0, __qtablewidgetitem27);
        table_state_transition_3->setObjectName(QString::fromUtf8("table_state_transition_3"));

        gridLayout_3->addWidget(table_state_transition_3, 2, 2, 1, 1);

        table_gain_5 = new QTableWidget(widget_3);
        if (table_gain_5->columnCount() < 1)
            table_gain_5->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        table_gain_5->setHorizontalHeaderItem(0, __qtablewidgetitem28);
        if (table_gain_5->rowCount() < 1)
            table_gain_5->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        table_gain_5->setVerticalHeaderItem(0, __qtablewidgetitem29);
        table_gain_5->setObjectName(QString::fromUtf8("table_gain_5"));

        gridLayout_3->addWidget(table_gain_5, 2, 3, 1, 1);

        table_observation_model_3 = new QTableWidget(widget_3);
        if (table_observation_model_3->columnCount() < 1)
            table_observation_model_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        table_observation_model_3->setHorizontalHeaderItem(0, __qtablewidgetitem30);
        if (table_observation_model_3->rowCount() < 1)
            table_observation_model_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        table_observation_model_3->setVerticalHeaderItem(0, __qtablewidgetitem31);
        table_observation_model_3->setObjectName(QString::fromUtf8("table_observation_model_3"));

        gridLayout_3->addWidget(table_observation_model_3, 2, 5, 1, 1);

        table_previous_state_estimate_3 = new QTableWidget(widget_3);
        if (table_previous_state_estimate_3->columnCount() < 1)
            table_previous_state_estimate_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        table_previous_state_estimate_3->setHorizontalHeaderItem(0, __qtablewidgetitem32);
        if (table_previous_state_estimate_3->rowCount() < 1)
            table_previous_state_estimate_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        table_previous_state_estimate_3->setVerticalHeaderItem(0, __qtablewidgetitem33);
        table_previous_state_estimate_3->setObjectName(QString::fromUtf8("table_previous_state_estimate_3"));

        gridLayout_3->addWidget(table_previous_state_estimate_3, 2, 6, 1, 1);

        label_math_14 = new QLabel(widget_3);
        label_math_14->setObjectName(QString::fromUtf8("label_math_14"));

        gridLayout_3->addWidget(label_math_14, 2, 7, 1, 1);

        table_control_3 = new QTableWidget(widget_3);
        if (table_control_3->columnCount() < 1)
            table_control_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        table_control_3->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        if (table_control_3->rowCount() < 1)
            table_control_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        table_control_3->setVerticalHeaderItem(0, __qtablewidgetitem35);
        table_control_3->setObjectName(QString::fromUtf8("table_control_3"));

        gridLayout_3->addWidget(table_control_3, 2, 8, 1, 1);

        table_input_3 = new QTableWidget(widget_3);
        if (table_input_3->columnCount() < 1)
            table_input_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        table_input_3->setHorizontalHeaderItem(0, __qtablewidgetitem36);
        if (table_input_3->rowCount() < 1)
            table_input_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        table_input_3->setVerticalHeaderItem(0, __qtablewidgetitem37);
        table_input_3->setObjectName(QString::fromUtf8("table_input_3"));

        gridLayout_3->addWidget(table_input_3, 2, 9, 1, 1);

        label_bottom_1_3 = new QLabel(widget_3);
        label_bottom_1_3->setObjectName(QString::fromUtf8("label_bottom_1_3"));

        gridLayout_3->addWidget(label_bottom_1_3, 3, 0, 1, 1);

        label_bottom_2_3 = new QLabel(widget_3);
        label_bottom_2_3->setObjectName(QString::fromUtf8("label_bottom_2_3"));

        gridLayout_3->addWidget(label_bottom_2_3, 3, 2, 1, 1);

        label_bottom_3_3 = new QLabel(widget_3);
        label_bottom_3_3->setObjectName(QString::fromUtf8("label_bottom_3_3"));

        gridLayout_3->addWidget(label_bottom_3_3, 3, 3, 1, 1);

        label_bottom_5_3 = new QLabel(widget_3);
        label_bottom_5_3->setObjectName(QString::fromUtf8("label_bottom_5_3"));

        gridLayout_3->addWidget(label_bottom_5_3, 3, 6, 1, 1);

        label_bottom_6_3 = new QLabel(widget_3);
        label_bottom_6_3->setObjectName(QString::fromUtf8("label_bottom_6_3"));

        gridLayout_3->addWidget(label_bottom_6_3, 3, 8, 1, 1);

        label_bottom_7_3 = new QLabel(widget_3);
        label_bottom_7_3->setObjectName(QString::fromUtf8("label_bottom_7_3"));

        gridLayout_3->addWidget(label_bottom_7_3, 3, 9, 1, 1);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 2, 4, 1, 1);


        verticalLayout->addWidget(widget_3);


        retranslateUi(QtFixedLagSmootherKalmanFilterCalculationDialog);

        QMetaObject::connectSlotsByName(QtFixedLagSmootherKalmanFilterCalculationDialog);
    } // setupUi

    void retranslateUi(QDialog *QtFixedLagSmootherKalmanFilterCalculationDialog)
    {
        QtFixedLagSmootherKalmanFilterCalculationDialog->setWindowTitle(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Time: ?", 0, QApplication::UnicodeUTF8));
        label_title_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "1) Prediction error covariances", 0, QApplication::UnicodeUTF8));
        label_top_1_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "P(i)'s", 0, QApplication::UnicodeUTF8));
        label_top_2_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "P", 0, QApplication::UnicodeUTF8));
        label_top_3_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "A", 0, QApplication::UnicodeUTF8));
        label_top_4_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "K", 0, QApplication::UnicodeUTF8));
        label_top_5_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "H", 0, QApplication::UnicodeUTF8));
        label_top_8_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "i", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = table_state_predicted->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = table_state_predicted->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "= ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = table_state_transition->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = table_state_transition->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "( (", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = table_gain_1->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = table_gain_1->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = table_observation_model->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = table_observation_model->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = table_previous_state_estimate->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = table_previous_state_estimate->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_5->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", ")", 0, QApplication::UnicodeUTF8));
        label_bottom_1_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Augmented predicted\n"
"error covariances", 0, QApplication::UnicodeUTF8));
        label_bottom_2_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Prediction error covariance", 0, QApplication::UnicodeUTF8));
        label_bottom_3_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "State transition matrix", 0, QApplication::UnicodeUTF8));
        label_bottom_4_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Observation\n"
"model", 0, QApplication::UnicodeUTF8));
        label_bottom_5_1->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Previous\n"
"state estimate", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "-", 0, QApplication::UnicodeUTF8));
        label_math_4->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "T", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", ")", 0, QApplication::UnicodeUTF8));
        label_title_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "2) Augmented Kalman gains", 0, QApplication::UnicodeUTF8));
        label_top_1_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "K(i)'s", 0, QApplication::UnicodeUTF8));
        label_top_2_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "P(i)'s", 0, QApplication::UnicodeUTF8));
        label_top_3_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "H^T", 0, QApplication::UnicodeUTF8));
        label_top_4_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "H", 0, QApplication::UnicodeUTF8));
        label_top_5_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "P", 0, QApplication::UnicodeUTF8));
        label_top_6_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "H^T", 0, QApplication::UnicodeUTF8));
        label_top_7_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "R", 0, QApplication::UnicodeUTF8));
        label_top_8_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "-1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = table_state_predicted_2->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = table_state_predicted_2->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_6->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = table_state_transition_2->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = table_state_transition_2->verticalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = table_gain_3->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = table_gain_3->verticalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = table_observation_model_2->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = table_observation_model_2->verticalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = table_previous_state_estimate_2->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = table_previous_state_estimate_2->verticalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = table_control_2->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = table_control_2->verticalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = table_input_2->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = table_input_2->verticalHeaderItem(0);
        ___qtablewidgetitem23->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_10->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", ")", 0, QApplication::UnicodeUTF8));
        label_bottom_1_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Augmented Kalman\n"
"gains", 0, QApplication::UnicodeUTF8));
        label_bottom_2_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Augmented predicted\n"
"error covariances", 0, QApplication::UnicodeUTF8));
        label_bottom_3_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Observation", 0, QApplication::UnicodeUTF8));
        label_bottom_4_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Observation", 0, QApplication::UnicodeUTF8));
        label_bottom_5_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Prediction error covariance", 0, QApplication::UnicodeUTF8));
        label_bottom_6_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Observation", 0, QApplication::UnicodeUTF8));
        label_bottom_7_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Estimated measurement\n"
"error covariance", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "(", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        label_7->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        label_title_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "3) Augmented state estimate", 0, QApplication::UnicodeUTF8));
        label_top_1_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "x_predicteds", 0, QApplication::UnicodeUTF8));
        label_top_3_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "x_predicted", 0, QApplication::UnicodeUTF8));
        label_top_5_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "x_predicteds_prev", 0, QApplication::UnicodeUTF8));
        label_top_6_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Augmented Kalman\n"
"gains", 0, QApplication::UnicodeUTF8));
        label_top_7_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Innovation", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = table_state_predicted_3->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = table_state_predicted_3->verticalHeaderItem(0);
        ___qtablewidgetitem25->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_11->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = table_state_transition_3->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = table_state_transition_3->verticalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = table_gain_5->horizontalHeaderItem(0);
        ___qtablewidgetitem28->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = table_gain_5->verticalHeaderItem(0);
        ___qtablewidgetitem29->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = table_observation_model_3->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = table_observation_model_3->verticalHeaderItem(0);
        ___qtablewidgetitem31->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = table_previous_state_estimate_3->horizontalHeaderItem(0);
        ___qtablewidgetitem32->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = table_previous_state_estimate_3->verticalHeaderItem(0);
        ___qtablewidgetitem33->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_math_14->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = table_control_3->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = table_control_3->verticalHeaderItem(0);
        ___qtablewidgetitem35->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = table_input_3->horizontalHeaderItem(0);
        ___qtablewidgetitem36->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = table_input_3->verticalHeaderItem(0);
        ___qtablewidgetitem37->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_bottom_1_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Augmented predicted\n"
" states", 0, QApplication::UnicodeUTF8));
        label_bottom_2_3->setText(QString());
        label_bottom_3_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Predicted state", 0, QApplication::UnicodeUTF8));
        label_bottom_5_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "Previous augmented\n"
"predicted states", 0, QApplication::UnicodeUTF8));
        label_bottom_6_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "K(i)'s", 0, QApplication::UnicodeUTF8));
        label_bottom_7_3->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "y", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QtFixedLagSmootherKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtFixedLagSmootherKalmanFilterCalculationDialog: public Ui_QtFixedLagSmootherKalmanFilterCalculationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTFIXEDLAGSMOOTHERKALMANFILTERCALCULATIONDIALOG_H
