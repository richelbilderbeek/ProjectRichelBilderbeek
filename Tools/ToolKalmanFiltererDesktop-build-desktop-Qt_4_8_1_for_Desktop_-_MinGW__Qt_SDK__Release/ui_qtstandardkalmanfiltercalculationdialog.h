/********************************************************************************
** Form generated from reading UI file 'qtstandardkalmanfiltercalculationdialog.ui'
**
** Created: Fri 7. Jun 11:45:53 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSTANDARDKALMANFILTERCALCULATIONDIALOG_H
#define UI_QTSTANDARDKALMANFILTERCALCULATIONDIALOG_H

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

class Ui_QtStandardKalmanFilterCalculationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_time;
    QWidget *widget_1;
    QGridLayout *gridLayout;
    QLabel *label_top_1_1;
    QLabel *label_top_2_1;
    QTableWidget *table_state_predicted_1;
    QLabel *label_equals_1;
    QTableWidget *table_state_transition_1;
    QLabel *label_dot_2_1;
    QTableWidget *table_previous_state_estimate;
    QLabel *label_plus_1;
    QTableWidget *table_control_1;
    QTableWidget *table_input;
    QLabel *label_dot_1_1;
    QLabel *label_top_3_1;
    QLabel *label_top_4_1;
    QLabel *label_top_5_1;
    QLabel *label_bottom_1_1;
    QLabel *label_bottom_2_1;
    QLabel *label_bottom_3_1;
    QLabel *label_bottom_4_1;
    QLabel *label_bottom_5_1;
    QLabel *label_title_1;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_27;
    QTableWidget *table_covariance_predicted_2;
    QLabel *label_equals_2;
    QTableWidget *table_state_transition_1_2;
    QLabel *label_25;
    QTableWidget *table_previous_covariance_estimate;
    QLabel *label_26;
    QTableWidget *table_state_transition_2_transposed;
    QLabel *label_28;
    QLabel *label_29;
    QTableWidget *table_estimated_process_noise;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_17;
    QTableWidget *table_innovation_3;
    QLabel *label_36;
    QTableWidget *table_measurement;
    QLabel *label_38;
    QTableWidget *table_observation_3;
    QLabel *label_37;
    QTableWidget *table_state_predicted_3;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_43;
    QLabel *label_44;
    QLabel *label_45;
    QLabel *label_46;
    QWidget *widget_4;
    QGridLayout *gridLayout_4;
    QLabel *label_47;
    QTableWidget *table_innovation_covariance_4;
    QLabel *label_48;
    QTableWidget *table_observation_4;
    QLabel *label_49;
    QTableWidget *table_covariance_predicted_4;
    QLabel *label_50;
    QTableWidget *table_observation_4_transposed;
    QLabel *label_51;
    QLabel *label_52;
    QLabel *label_53;
    QLabel *label_54;
    QLabel *label_55;
    QLabel *label_56;
    QLabel *label_57;
    QLabel *label_58;
    QLabel *label_59;
    QTableWidget *table_estimated_measurement_noise;
    QLabel *label_19;
    QLabel *label_18;
    QWidget *widget_5;
    QGridLayout *gridLayout_5;
    QLabel *label_60;
    QTableWidget *table_kalman_gain_5;
    QLabel *label_61;
    QTableWidget *table_covariance_predicted_5;
    QLabel *label_62;
    QTableWidget *table_observation_5_transposed;
    QLabel *label_63;
    QTableWidget *table_innovation_covariance_5_inverted;
    QLabel *label_64;
    QLabel *label_65;
    QLabel *label_66;
    QLabel *label_67;
    QLabel *label_68;
    QLabel *label_69;
    QLabel *label_70;
    QLabel *label_71;
    QWidget *widget_6;
    QGridLayout *gridLayout_6;
    QLabel *label_72;
    QTableWidget *table_new_state_estimate;
    QLabel *label_73;
    QTableWidget *table_state_predicted_6;
    QLabel *label_74;
    QTableWidget *table_kalman_gain_6;
    QLabel *label_75;
    QTableWidget *table_innovation_6;
    QLabel *label_76;
    QLabel *label_77;
    QLabel *label_78;
    QLabel *label_79;
    QLabel *label_80;
    QLabel *label_81;
    QLabel *label_82;
    QLabel *label_83;
    QWidget *widget_7;
    QGridLayout *gridLayout_7;
    QLabel *label_20;
    QLabel *label_84;
    QLabel *label_85;
    QLabel *label_86;
    QTableWidget *table_new_covariance;
    QLabel *label_87;
    QTableWidget *table_identity_matrix;
    QLabel *label_88;
    QTableWidget *table_kalman_gain_7;
    QLabel *label_89;
    QTableWidget *table_observation_7;
    QLabel *label_90;
    QLabel *label_91;
    QTableWidget *table_covariance_predicted_7;
    QLabel *label_93;
    QLabel *label_bottom_2;
    QLabel *label_112;
    QLabel *label_98;
    QLabel *label_107;
    QLabel *label_92;
    QLabel *label_95;

    void setupUi(QDialog *QtStandardKalmanFilterCalculationDialog)
    {
        if (QtStandardKalmanFilterCalculationDialog->objectName().isEmpty())
            QtStandardKalmanFilterCalculationDialog->setObjectName(QString::fromUtf8("QtStandardKalmanFilterCalculationDialog"));
        QtStandardKalmanFilterCalculationDialog->resize(631, 1097);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtStandardKalmanFilterCalculationDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(QtStandardKalmanFilterCalculationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_time = new QLabel(QtStandardKalmanFilterCalculationDialog);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout->addWidget(label_time);

        widget_1 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        gridLayout = new QGridLayout(widget_1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_top_1_1 = new QLabel(widget_1);
        label_top_1_1->setObjectName(QString::fromUtf8("label_top_1_1"));

        gridLayout->addWidget(label_top_1_1, 1, 0, 1, 1);

        label_top_2_1 = new QLabel(widget_1);
        label_top_2_1->setObjectName(QString::fromUtf8("label_top_2_1"));

        gridLayout->addWidget(label_top_2_1, 1, 2, 1, 1);

        table_state_predicted_1 = new QTableWidget(widget_1);
        if (table_state_predicted_1->columnCount() < 1)
            table_state_predicted_1->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_state_predicted_1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (table_state_predicted_1->rowCount() < 1)
            table_state_predicted_1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_state_predicted_1->setVerticalHeaderItem(0, __qtablewidgetitem1);
        table_state_predicted_1->setObjectName(QString::fromUtf8("table_state_predicted_1"));

        gridLayout->addWidget(table_state_predicted_1, 2, 0, 1, 1);

        label_equals_1 = new QLabel(widget_1);
        label_equals_1->setObjectName(QString::fromUtf8("label_equals_1"));

        gridLayout->addWidget(label_equals_1, 2, 1, 1, 1);

        table_state_transition_1 = new QTableWidget(widget_1);
        if (table_state_transition_1->columnCount() < 1)
            table_state_transition_1->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_state_transition_1->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        if (table_state_transition_1->rowCount() < 1)
            table_state_transition_1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_state_transition_1->setVerticalHeaderItem(0, __qtablewidgetitem3);
        table_state_transition_1->setObjectName(QString::fromUtf8("table_state_transition_1"));

        gridLayout->addWidget(table_state_transition_1, 2, 2, 1, 1);

        label_dot_2_1 = new QLabel(widget_1);
        label_dot_2_1->setObjectName(QString::fromUtf8("label_dot_2_1"));

        gridLayout->addWidget(label_dot_2_1, 2, 3, 1, 1);

        table_previous_state_estimate = new QTableWidget(widget_1);
        if (table_previous_state_estimate->columnCount() < 1)
            table_previous_state_estimate->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_previous_state_estimate->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        if (table_previous_state_estimate->rowCount() < 1)
            table_previous_state_estimate->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table_previous_state_estimate->setVerticalHeaderItem(0, __qtablewidgetitem5);
        table_previous_state_estimate->setObjectName(QString::fromUtf8("table_previous_state_estimate"));

        gridLayout->addWidget(table_previous_state_estimate, 2, 4, 1, 1);

        label_plus_1 = new QLabel(widget_1);
        label_plus_1->setObjectName(QString::fromUtf8("label_plus_1"));

        gridLayout->addWidget(label_plus_1, 2, 5, 1, 1);

        table_control_1 = new QTableWidget(widget_1);
        if (table_control_1->columnCount() < 1)
            table_control_1->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table_control_1->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        if (table_control_1->rowCount() < 1)
            table_control_1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        table_control_1->setVerticalHeaderItem(0, __qtablewidgetitem7);
        table_control_1->setObjectName(QString::fromUtf8("table_control_1"));

        gridLayout->addWidget(table_control_1, 2, 6, 1, 1);

        table_input = new QTableWidget(widget_1);
        if (table_input->columnCount() < 1)
            table_input->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        table_input->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        if (table_input->rowCount() < 1)
            table_input->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        table_input->setVerticalHeaderItem(0, __qtablewidgetitem9);
        table_input->setObjectName(QString::fromUtf8("table_input"));

        gridLayout->addWidget(table_input, 2, 8, 1, 1);

        label_dot_1_1 = new QLabel(widget_1);
        label_dot_1_1->setObjectName(QString::fromUtf8("label_dot_1_1"));

        gridLayout->addWidget(label_dot_1_1, 2, 7, 1, 1);

        label_top_3_1 = new QLabel(widget_1);
        label_top_3_1->setObjectName(QString::fromUtf8("label_top_3_1"));

        gridLayout->addWidget(label_top_3_1, 1, 4, 1, 1);

        label_top_4_1 = new QLabel(widget_1);
        label_top_4_1->setObjectName(QString::fromUtf8("label_top_4_1"));

        gridLayout->addWidget(label_top_4_1, 1, 6, 1, 1);

        label_top_5_1 = new QLabel(widget_1);
        label_top_5_1->setObjectName(QString::fromUtf8("label_top_5_1"));

        gridLayout->addWidget(label_top_5_1, 1, 8, 1, 1);

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

        gridLayout->addWidget(label_bottom_5_1, 3, 8, 1, 1);

        label_title_1 = new QLabel(widget_1);
        label_title_1->setObjectName(QString::fromUtf8("label_title_1"));

        gridLayout->addWidget(label_title_1, 0, 0, 1, 2);


        verticalLayout->addWidget(widget_1);

        widget_2 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 4);

        label_22 = new QLabel(widget_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 1, 0, 1, 1);

        label_23 = new QLabel(widget_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_2->addWidget(label_23, 1, 2, 1, 1);

        label_27 = new QLabel(widget_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_2->addWidget(label_27, 1, 4, 1, 1);

        table_covariance_predicted_2 = new QTableWidget(widget_2);
        if (table_covariance_predicted_2->columnCount() < 1)
            table_covariance_predicted_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        table_covariance_predicted_2->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        if (table_covariance_predicted_2->rowCount() < 1)
            table_covariance_predicted_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        table_covariance_predicted_2->setVerticalHeaderItem(0, __qtablewidgetitem11);
        table_covariance_predicted_2->setObjectName(QString::fromUtf8("table_covariance_predicted_2"));

        gridLayout_2->addWidget(table_covariance_predicted_2, 2, 0, 1, 1);

        label_equals_2 = new QLabel(widget_2);
        label_equals_2->setObjectName(QString::fromUtf8("label_equals_2"));

        gridLayout_2->addWidget(label_equals_2, 2, 1, 1, 1);

        table_state_transition_1_2 = new QTableWidget(widget_2);
        if (table_state_transition_1_2->columnCount() < 1)
            table_state_transition_1_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        table_state_transition_1_2->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        if (table_state_transition_1_2->rowCount() < 1)
            table_state_transition_1_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        table_state_transition_1_2->setVerticalHeaderItem(0, __qtablewidgetitem13);
        table_state_transition_1_2->setObjectName(QString::fromUtf8("table_state_transition_1_2"));

        gridLayout_2->addWidget(table_state_transition_1_2, 2, 2, 1, 1);

        label_25 = new QLabel(widget_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_2->addWidget(label_25, 2, 3, 1, 1);

        table_previous_covariance_estimate = new QTableWidget(widget_2);
        if (table_previous_covariance_estimate->columnCount() < 1)
            table_previous_covariance_estimate->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        table_previous_covariance_estimate->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        if (table_previous_covariance_estimate->rowCount() < 1)
            table_previous_covariance_estimate->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        table_previous_covariance_estimate->setVerticalHeaderItem(0, __qtablewidgetitem15);
        table_previous_covariance_estimate->setObjectName(QString::fromUtf8("table_previous_covariance_estimate"));

        gridLayout_2->addWidget(table_previous_covariance_estimate, 2, 4, 1, 1);

        label_26 = new QLabel(widget_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_2->addWidget(label_26, 2, 5, 1, 1);

        table_state_transition_2_transposed = new QTableWidget(widget_2);
        if (table_state_transition_2_transposed->columnCount() < 1)
            table_state_transition_2_transposed->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        table_state_transition_2_transposed->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        if (table_state_transition_2_transposed->rowCount() < 1)
            table_state_transition_2_transposed->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        table_state_transition_2_transposed->setVerticalHeaderItem(0, __qtablewidgetitem17);
        table_state_transition_2_transposed->setObjectName(QString::fromUtf8("table_state_transition_2_transposed"));

        gridLayout_2->addWidget(table_state_transition_2_transposed, 2, 6, 1, 1);

        label_28 = new QLabel(widget_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_2->addWidget(label_28, 1, 6, 1, 1);

        label_29 = new QLabel(widget_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_2->addWidget(label_29, 2, 7, 1, 1);

        table_estimated_process_noise = new QTableWidget(widget_2);
        if (table_estimated_process_noise->columnCount() < 1)
            table_estimated_process_noise->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        table_estimated_process_noise->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        if (table_estimated_process_noise->rowCount() < 1)
            table_estimated_process_noise->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        table_estimated_process_noise->setVerticalHeaderItem(0, __qtablewidgetitem19);
        table_estimated_process_noise->setObjectName(QString::fromUtf8("table_estimated_process_noise"));

        gridLayout_2->addWidget(table_estimated_process_noise, 2, 8, 1, 1);

        label_30 = new QLabel(widget_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_2->addWidget(label_30, 1, 8, 1, 1);

        label_31 = new QLabel(widget_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_2->addWidget(label_31, 3, 0, 1, 1);

        label_32 = new QLabel(widget_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_2->addWidget(label_32, 3, 2, 1, 1);

        label_33 = new QLabel(widget_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_2->addWidget(label_33, 3, 4, 1, 1);

        label_34 = new QLabel(widget_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_2->addWidget(label_34, 3, 6, 1, 1);

        label_35 = new QLabel(widget_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_2->addWidget(label_35, 3, 8, 1, 1);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_17 = new QLabel(widget_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_3->addWidget(label_17, 0, 0, 1, 2);

        table_innovation_3 = new QTableWidget(widget_3);
        if (table_innovation_3->columnCount() < 1)
            table_innovation_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        table_innovation_3->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        if (table_innovation_3->rowCount() < 1)
            table_innovation_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        table_innovation_3->setVerticalHeaderItem(0, __qtablewidgetitem21);
        table_innovation_3->setObjectName(QString::fromUtf8("table_innovation_3"));

        gridLayout_3->addWidget(table_innovation_3, 2, 0, 1, 1);

        label_36 = new QLabel(widget_3);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_3->addWidget(label_36, 2, 1, 1, 1);

        table_measurement = new QTableWidget(widget_3);
        if (table_measurement->columnCount() < 1)
            table_measurement->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        table_measurement->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        if (table_measurement->rowCount() < 1)
            table_measurement->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        table_measurement->setVerticalHeaderItem(0, __qtablewidgetitem23);
        table_measurement->setObjectName(QString::fromUtf8("table_measurement"));

        gridLayout_3->addWidget(table_measurement, 2, 2, 1, 1);

        label_38 = new QLabel(widget_3);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout_3->addWidget(label_38, 2, 3, 1, 1);

        table_observation_3 = new QTableWidget(widget_3);
        if (table_observation_3->columnCount() < 1)
            table_observation_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        table_observation_3->setHorizontalHeaderItem(0, __qtablewidgetitem24);
        if (table_observation_3->rowCount() < 1)
            table_observation_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        table_observation_3->setVerticalHeaderItem(0, __qtablewidgetitem25);
        table_observation_3->setObjectName(QString::fromUtf8("table_observation_3"));

        gridLayout_3->addWidget(table_observation_3, 2, 4, 1, 1);

        label_37 = new QLabel(widget_3);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_3->addWidget(label_37, 2, 5, 1, 1);

        table_state_predicted_3 = new QTableWidget(widget_3);
        if (table_state_predicted_3->columnCount() < 1)
            table_state_predicted_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        table_state_predicted_3->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        if (table_state_predicted_3->rowCount() < 1)
            table_state_predicted_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        table_state_predicted_3->setVerticalHeaderItem(0, __qtablewidgetitem27);
        table_state_predicted_3->setObjectName(QString::fromUtf8("table_state_predicted_3"));

        gridLayout_3->addWidget(table_state_predicted_3, 2, 6, 1, 1);

        label_39 = new QLabel(widget_3);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        gridLayout_3->addWidget(label_39, 1, 0, 1, 1);

        label_40 = new QLabel(widget_3);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        gridLayout_3->addWidget(label_40, 3, 0, 1, 1);

        label_41 = new QLabel(widget_3);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_3->addWidget(label_41, 1, 2, 1, 1);

        label_42 = new QLabel(widget_3);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_3->addWidget(label_42, 3, 2, 1, 1);

        label_43 = new QLabel(widget_3);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout_3->addWidget(label_43, 1, 4, 1, 1);

        label_44 = new QLabel(widget_3);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_3->addWidget(label_44, 1, 6, 1, 1);

        label_45 = new QLabel(widget_3);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout_3->addWidget(label_45, 3, 4, 1, 1);

        label_46 = new QLabel(widget_3);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_3->addWidget(label_46, 3, 6, 1, 1);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_4 = new QGridLayout(widget_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_47 = new QLabel(widget_4);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_4->addWidget(label_47, 0, 0, 1, 2);

        table_innovation_covariance_4 = new QTableWidget(widget_4);
        if (table_innovation_covariance_4->columnCount() < 1)
            table_innovation_covariance_4->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        table_innovation_covariance_4->setHorizontalHeaderItem(0, __qtablewidgetitem28);
        if (table_innovation_covariance_4->rowCount() < 1)
            table_innovation_covariance_4->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        table_innovation_covariance_4->setVerticalHeaderItem(0, __qtablewidgetitem29);
        table_innovation_covariance_4->setObjectName(QString::fromUtf8("table_innovation_covariance_4"));

        gridLayout_4->addWidget(table_innovation_covariance_4, 2, 0, 1, 1);

        label_48 = new QLabel(widget_4);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_4->addWidget(label_48, 2, 1, 1, 1);

        table_observation_4 = new QTableWidget(widget_4);
        if (table_observation_4->columnCount() < 1)
            table_observation_4->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        table_observation_4->setHorizontalHeaderItem(0, __qtablewidgetitem30);
        if (table_observation_4->rowCount() < 1)
            table_observation_4->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        table_observation_4->setVerticalHeaderItem(0, __qtablewidgetitem31);
        table_observation_4->setObjectName(QString::fromUtf8("table_observation_4"));

        gridLayout_4->addWidget(table_observation_4, 2, 2, 1, 1);

        label_49 = new QLabel(widget_4);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout_4->addWidget(label_49, 2, 3, 1, 1);

        table_covariance_predicted_4 = new QTableWidget(widget_4);
        if (table_covariance_predicted_4->columnCount() < 1)
            table_covariance_predicted_4->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        table_covariance_predicted_4->setHorizontalHeaderItem(0, __qtablewidgetitem32);
        if (table_covariance_predicted_4->rowCount() < 1)
            table_covariance_predicted_4->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        table_covariance_predicted_4->setVerticalHeaderItem(0, __qtablewidgetitem33);
        table_covariance_predicted_4->setObjectName(QString::fromUtf8("table_covariance_predicted_4"));

        gridLayout_4->addWidget(table_covariance_predicted_4, 2, 4, 1, 1);

        label_50 = new QLabel(widget_4);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout_4->addWidget(label_50, 2, 5, 1, 1);

        table_observation_4_transposed = new QTableWidget(widget_4);
        if (table_observation_4_transposed->columnCount() < 1)
            table_observation_4_transposed->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        table_observation_4_transposed->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        if (table_observation_4_transposed->rowCount() < 1)
            table_observation_4_transposed->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        table_observation_4_transposed->setVerticalHeaderItem(0, __qtablewidgetitem35);
        table_observation_4_transposed->setObjectName(QString::fromUtf8("table_observation_4_transposed"));

        gridLayout_4->addWidget(table_observation_4_transposed, 2, 6, 1, 1);

        label_51 = new QLabel(widget_4);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_4->addWidget(label_51, 1, 0, 1, 1);

        label_52 = new QLabel(widget_4);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout_4->addWidget(label_52, 3, 0, 1, 1);

        label_53 = new QLabel(widget_4);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        gridLayout_4->addWidget(label_53, 1, 2, 1, 1);

        label_54 = new QLabel(widget_4);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_4->addWidget(label_54, 3, 2, 1, 1);

        label_55 = new QLabel(widget_4);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        gridLayout_4->addWidget(label_55, 1, 4, 1, 1);

        label_56 = new QLabel(widget_4);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_4->addWidget(label_56, 1, 6, 1, 1);

        label_57 = new QLabel(widget_4);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_4->addWidget(label_57, 3, 4, 1, 1);

        label_58 = new QLabel(widget_4);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        gridLayout_4->addWidget(label_58, 3, 6, 1, 1);

        label_59 = new QLabel(widget_4);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout_4->addWidget(label_59, 2, 7, 1, 1);

        table_estimated_measurement_noise = new QTableWidget(widget_4);
        if (table_estimated_measurement_noise->columnCount() < 1)
            table_estimated_measurement_noise->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        table_estimated_measurement_noise->setHorizontalHeaderItem(0, __qtablewidgetitem36);
        if (table_estimated_measurement_noise->rowCount() < 1)
            table_estimated_measurement_noise->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        table_estimated_measurement_noise->setVerticalHeaderItem(0, __qtablewidgetitem37);
        table_estimated_measurement_noise->setObjectName(QString::fromUtf8("table_estimated_measurement_noise"));

        gridLayout_4->addWidget(table_estimated_measurement_noise, 2, 8, 1, 1);

        label_19 = new QLabel(widget_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_4->addWidget(label_19, 3, 8, 1, 1);

        label_18 = new QLabel(widget_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_4->addWidget(label_18, 1, 8, 1, 1);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_5 = new QGridLayout(widget_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_60 = new QLabel(widget_5);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_5->addWidget(label_60, 0, 0, 1, 2);

        table_kalman_gain_5 = new QTableWidget(widget_5);
        if (table_kalman_gain_5->columnCount() < 1)
            table_kalman_gain_5->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        table_kalman_gain_5->setHorizontalHeaderItem(0, __qtablewidgetitem38);
        if (table_kalman_gain_5->rowCount() < 1)
            table_kalman_gain_5->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        table_kalman_gain_5->setVerticalHeaderItem(0, __qtablewidgetitem39);
        table_kalman_gain_5->setObjectName(QString::fromUtf8("table_kalman_gain_5"));

        gridLayout_5->addWidget(table_kalman_gain_5, 2, 0, 1, 1);

        label_61 = new QLabel(widget_5);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayout_5->addWidget(label_61, 2, 1, 1, 1);

        table_covariance_predicted_5 = new QTableWidget(widget_5);
        if (table_covariance_predicted_5->columnCount() < 1)
            table_covariance_predicted_5->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        table_covariance_predicted_5->setHorizontalHeaderItem(0, __qtablewidgetitem40);
        if (table_covariance_predicted_5->rowCount() < 1)
            table_covariance_predicted_5->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        table_covariance_predicted_5->setVerticalHeaderItem(0, __qtablewidgetitem41);
        table_covariance_predicted_5->setObjectName(QString::fromUtf8("table_covariance_predicted_5"));

        gridLayout_5->addWidget(table_covariance_predicted_5, 2, 2, 1, 1);

        label_62 = new QLabel(widget_5);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        gridLayout_5->addWidget(label_62, 2, 3, 1, 1);

        table_observation_5_transposed = new QTableWidget(widget_5);
        if (table_observation_5_transposed->columnCount() < 1)
            table_observation_5_transposed->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        table_observation_5_transposed->setHorizontalHeaderItem(0, __qtablewidgetitem42);
        if (table_observation_5_transposed->rowCount() < 1)
            table_observation_5_transposed->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        table_observation_5_transposed->setVerticalHeaderItem(0, __qtablewidgetitem43);
        table_observation_5_transposed->setObjectName(QString::fromUtf8("table_observation_5_transposed"));

        gridLayout_5->addWidget(table_observation_5_transposed, 2, 4, 1, 1);

        label_63 = new QLabel(widget_5);
        label_63->setObjectName(QString::fromUtf8("label_63"));

        gridLayout_5->addWidget(label_63, 2, 5, 1, 1);

        table_innovation_covariance_5_inverted = new QTableWidget(widget_5);
        if (table_innovation_covariance_5_inverted->columnCount() < 1)
            table_innovation_covariance_5_inverted->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        table_innovation_covariance_5_inverted->setHorizontalHeaderItem(0, __qtablewidgetitem44);
        if (table_innovation_covariance_5_inverted->rowCount() < 1)
            table_innovation_covariance_5_inverted->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        table_innovation_covariance_5_inverted->setVerticalHeaderItem(0, __qtablewidgetitem45);
        table_innovation_covariance_5_inverted->setObjectName(QString::fromUtf8("table_innovation_covariance_5_inverted"));

        gridLayout_5->addWidget(table_innovation_covariance_5_inverted, 2, 6, 1, 1);

        label_64 = new QLabel(widget_5);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        gridLayout_5->addWidget(label_64, 1, 0, 1, 1);

        label_65 = new QLabel(widget_5);
        label_65->setObjectName(QString::fromUtf8("label_65"));

        gridLayout_5->addWidget(label_65, 3, 0, 1, 1);

        label_66 = new QLabel(widget_5);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        gridLayout_5->addWidget(label_66, 1, 2, 1, 1);

        label_67 = new QLabel(widget_5);
        label_67->setObjectName(QString::fromUtf8("label_67"));

        gridLayout_5->addWidget(label_67, 3, 2, 1, 1);

        label_68 = new QLabel(widget_5);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        gridLayout_5->addWidget(label_68, 1, 4, 1, 1);

        label_69 = new QLabel(widget_5);
        label_69->setObjectName(QString::fromUtf8("label_69"));

        gridLayout_5->addWidget(label_69, 1, 6, 1, 1);

        label_70 = new QLabel(widget_5);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        gridLayout_5->addWidget(label_70, 3, 4, 1, 1);

        label_71 = new QLabel(widget_5);
        label_71->setObjectName(QString::fromUtf8("label_71"));

        gridLayout_5->addWidget(label_71, 3, 6, 1, 1);


        verticalLayout->addWidget(widget_5);

        widget_6 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_6 = new QGridLayout(widget_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_72 = new QLabel(widget_6);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        gridLayout_6->addWidget(label_72, 0, 0, 1, 2);

        table_new_state_estimate = new QTableWidget(widget_6);
        if (table_new_state_estimate->columnCount() < 1)
            table_new_state_estimate->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        table_new_state_estimate->setHorizontalHeaderItem(0, __qtablewidgetitem46);
        if (table_new_state_estimate->rowCount() < 1)
            table_new_state_estimate->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        table_new_state_estimate->setVerticalHeaderItem(0, __qtablewidgetitem47);
        table_new_state_estimate->setObjectName(QString::fromUtf8("table_new_state_estimate"));

        gridLayout_6->addWidget(table_new_state_estimate, 2, 0, 1, 1);

        label_73 = new QLabel(widget_6);
        label_73->setObjectName(QString::fromUtf8("label_73"));

        gridLayout_6->addWidget(label_73, 2, 1, 1, 1);

        table_state_predicted_6 = new QTableWidget(widget_6);
        if (table_state_predicted_6->columnCount() < 1)
            table_state_predicted_6->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        table_state_predicted_6->setHorizontalHeaderItem(0, __qtablewidgetitem48);
        if (table_state_predicted_6->rowCount() < 1)
            table_state_predicted_6->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        table_state_predicted_6->setVerticalHeaderItem(0, __qtablewidgetitem49);
        table_state_predicted_6->setObjectName(QString::fromUtf8("table_state_predicted_6"));

        gridLayout_6->addWidget(table_state_predicted_6, 2, 2, 1, 1);

        label_74 = new QLabel(widget_6);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        gridLayout_6->addWidget(label_74, 2, 3, 1, 1);

        table_kalman_gain_6 = new QTableWidget(widget_6);
        if (table_kalman_gain_6->columnCount() < 1)
            table_kalman_gain_6->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        table_kalman_gain_6->setHorizontalHeaderItem(0, __qtablewidgetitem50);
        if (table_kalman_gain_6->rowCount() < 1)
            table_kalman_gain_6->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        table_kalman_gain_6->setVerticalHeaderItem(0, __qtablewidgetitem51);
        table_kalman_gain_6->setObjectName(QString::fromUtf8("table_kalman_gain_6"));

        gridLayout_6->addWidget(table_kalman_gain_6, 2, 4, 1, 1);

        label_75 = new QLabel(widget_6);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        gridLayout_6->addWidget(label_75, 2, 5, 1, 1);

        table_innovation_6 = new QTableWidget(widget_6);
        if (table_innovation_6->columnCount() < 1)
            table_innovation_6->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        table_innovation_6->setHorizontalHeaderItem(0, __qtablewidgetitem52);
        if (table_innovation_6->rowCount() < 1)
            table_innovation_6->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        table_innovation_6->setVerticalHeaderItem(0, __qtablewidgetitem53);
        table_innovation_6->setObjectName(QString::fromUtf8("table_innovation_6"));

        gridLayout_6->addWidget(table_innovation_6, 2, 6, 1, 1);

        label_76 = new QLabel(widget_6);
        label_76->setObjectName(QString::fromUtf8("label_76"));

        gridLayout_6->addWidget(label_76, 1, 0, 1, 1);

        label_77 = new QLabel(widget_6);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        gridLayout_6->addWidget(label_77, 3, 0, 1, 1);

        label_78 = new QLabel(widget_6);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        gridLayout_6->addWidget(label_78, 1, 2, 1, 1);

        label_79 = new QLabel(widget_6);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_6->addWidget(label_79, 3, 2, 1, 1);

        label_80 = new QLabel(widget_6);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        gridLayout_6->addWidget(label_80, 1, 4, 1, 1);

        label_81 = new QLabel(widget_6);
        label_81->setObjectName(QString::fromUtf8("label_81"));

        gridLayout_6->addWidget(label_81, 1, 6, 1, 1);

        label_82 = new QLabel(widget_6);
        label_82->setObjectName(QString::fromUtf8("label_82"));

        gridLayout_6->addWidget(label_82, 3, 4, 1, 1);

        label_83 = new QLabel(widget_6);
        label_83->setObjectName(QString::fromUtf8("label_83"));

        gridLayout_6->addWidget(label_83, 3, 6, 1, 1);


        verticalLayout->addWidget(widget_6);

        widget_7 = new QWidget(QtStandardKalmanFilterCalculationDialog);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        gridLayout_7 = new QGridLayout(widget_7);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_20 = new QLabel(widget_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_7->addWidget(label_20, 0, 0, 1, 5);

        label_84 = new QLabel(widget_7);
        label_84->setObjectName(QString::fromUtf8("label_84"));

        gridLayout_7->addWidget(label_84, 1, 0, 1, 1);

        label_85 = new QLabel(widget_7);
        label_85->setObjectName(QString::fromUtf8("label_85"));

        gridLayout_7->addWidget(label_85, 1, 3, 1, 1);

        label_86 = new QLabel(widget_7);
        label_86->setObjectName(QString::fromUtf8("label_86"));

        gridLayout_7->addWidget(label_86, 1, 5, 1, 1);

        table_new_covariance = new QTableWidget(widget_7);
        if (table_new_covariance->columnCount() < 1)
            table_new_covariance->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        table_new_covariance->setHorizontalHeaderItem(0, __qtablewidgetitem54);
        if (table_new_covariance->rowCount() < 1)
            table_new_covariance->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        table_new_covariance->setVerticalHeaderItem(0, __qtablewidgetitem55);
        table_new_covariance->setObjectName(QString::fromUtf8("table_new_covariance"));

        gridLayout_7->addWidget(table_new_covariance, 2, 0, 1, 1);

        label_87 = new QLabel(widget_7);
        label_87->setObjectName(QString::fromUtf8("label_87"));

        gridLayout_7->addWidget(label_87, 2, 1, 1, 1);

        table_identity_matrix = new QTableWidget(widget_7);
        if (table_identity_matrix->columnCount() < 1)
            table_identity_matrix->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        table_identity_matrix->setHorizontalHeaderItem(0, __qtablewidgetitem56);
        if (table_identity_matrix->rowCount() < 1)
            table_identity_matrix->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        table_identity_matrix->setVerticalHeaderItem(0, __qtablewidgetitem57);
        table_identity_matrix->setObjectName(QString::fromUtf8("table_identity_matrix"));

        gridLayout_7->addWidget(table_identity_matrix, 2, 3, 1, 1);

        label_88 = new QLabel(widget_7);
        label_88->setObjectName(QString::fromUtf8("label_88"));

        gridLayout_7->addWidget(label_88, 2, 4, 1, 1);

        table_kalman_gain_7 = new QTableWidget(widget_7);
        if (table_kalman_gain_7->columnCount() < 1)
            table_kalman_gain_7->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        table_kalman_gain_7->setHorizontalHeaderItem(0, __qtablewidgetitem58);
        if (table_kalman_gain_7->rowCount() < 1)
            table_kalman_gain_7->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        table_kalman_gain_7->setVerticalHeaderItem(0, __qtablewidgetitem59);
        table_kalman_gain_7->setObjectName(QString::fromUtf8("table_kalman_gain_7"));

        gridLayout_7->addWidget(table_kalman_gain_7, 2, 5, 1, 1);

        label_89 = new QLabel(widget_7);
        label_89->setObjectName(QString::fromUtf8("label_89"));

        gridLayout_7->addWidget(label_89, 2, 6, 1, 1);

        table_observation_7 = new QTableWidget(widget_7);
        if (table_observation_7->columnCount() < 1)
            table_observation_7->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        table_observation_7->setHorizontalHeaderItem(0, __qtablewidgetitem60);
        if (table_observation_7->rowCount() < 1)
            table_observation_7->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        table_observation_7->setVerticalHeaderItem(0, __qtablewidgetitem61);
        table_observation_7->setObjectName(QString::fromUtf8("table_observation_7"));

        gridLayout_7->addWidget(table_observation_7, 2, 7, 1, 1);

        label_90 = new QLabel(widget_7);
        label_90->setObjectName(QString::fromUtf8("label_90"));

        gridLayout_7->addWidget(label_90, 1, 7, 1, 1);

        label_91 = new QLabel(widget_7);
        label_91->setObjectName(QString::fromUtf8("label_91"));

        gridLayout_7->addWidget(label_91, 2, 8, 1, 1);

        table_covariance_predicted_7 = new QTableWidget(widget_7);
        if (table_covariance_predicted_7->columnCount() < 1)
            table_covariance_predicted_7->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        table_covariance_predicted_7->setHorizontalHeaderItem(0, __qtablewidgetitem62);
        if (table_covariance_predicted_7->rowCount() < 1)
            table_covariance_predicted_7->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        table_covariance_predicted_7->setVerticalHeaderItem(0, __qtablewidgetitem63);
        table_covariance_predicted_7->setObjectName(QString::fromUtf8("table_covariance_predicted_7"));

        gridLayout_7->addWidget(table_covariance_predicted_7, 2, 9, 1, 1);

        label_93 = new QLabel(widget_7);
        label_93->setObjectName(QString::fromUtf8("label_93"));

        gridLayout_7->addWidget(label_93, 3, 0, 1, 1);

        label_bottom_2 = new QLabel(widget_7);
        label_bottom_2->setObjectName(QString::fromUtf8("label_bottom_2"));

        gridLayout_7->addWidget(label_bottom_2, 3, 3, 1, 1);

        label_112 = new QLabel(widget_7);
        label_112->setObjectName(QString::fromUtf8("label_112"));

        gridLayout_7->addWidget(label_112, 2, 2, 1, 1);

        label_98 = new QLabel(widget_7);
        label_98->setObjectName(QString::fromUtf8("label_98"));

        gridLayout_7->addWidget(label_98, 1, 9, 1, 1);

        label_107 = new QLabel(widget_7);
        label_107->setObjectName(QString::fromUtf8("label_107"));

        gridLayout_7->addWidget(label_107, 3, 9, 1, 1);

        label_92 = new QLabel(widget_7);
        label_92->setObjectName(QString::fromUtf8("label_92"));

        gridLayout_7->addWidget(label_92, 3, 5, 1, 1);

        label_95 = new QLabel(widget_7);
        label_95->setObjectName(QString::fromUtf8("label_95"));

        gridLayout_7->addWidget(label_95, 3, 7, 1, 1);


        verticalLayout->addWidget(widget_7);


        retranslateUi(QtStandardKalmanFilterCalculationDialog);

        QMetaObject::connectSlotsByName(QtStandardKalmanFilterCalculationDialog);
    } // setupUi

    void retranslateUi(QDialog *QtStandardKalmanFilterCalculationDialog)
    {
        QtStandardKalmanFilterCalculationDialog->setWindowTitle(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Time: ?", 0, QApplication::UnicodeUTF8));
        label_top_1_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "x_predicted", 0, QApplication::UnicodeUTF8));
        label_top_2_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = table_state_predicted_1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = table_state_predicted_1->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_equals_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = table_state_transition_1->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = table_state_transition_1->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_dot_2_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = table_previous_state_estimate->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = table_previous_state_estimate->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_plus_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = table_control_1->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = table_control_1->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = table_input->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = table_input->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_dot_1_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        label_top_3_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "x_n-1", 0, QApplication::UnicodeUTF8));
        label_top_4_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "B", 0, QApplication::UnicodeUTF8));
        label_top_5_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "u_n", 0, QApplication::UnicodeUTF8));
        label_bottom_1_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Predicted state", 0, QApplication::UnicodeUTF8));
        label_bottom_2_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "State transition matrix", 0, QApplication::UnicodeUTF8));
        label_bottom_3_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Previous\n"
"state estimate", 0, QApplication::UnicodeUTF8));
        label_bottom_4_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Control", 0, QApplication::UnicodeUTF8));
        label_bottom_5_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Input", 0, QApplication::UnicodeUTF8));
        label_title_1->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "1) State prediction", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "2) Covariance prediction", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "P_predicted", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "A", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "P_n-1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = table_covariance_predicted_2->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = table_covariance_predicted_2->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_equals_2->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = table_state_transition_1_2->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = table_state_transition_1_2->verticalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = table_previous_covariance_estimate->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = table_previous_covariance_estimate->verticalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = table_state_transition_2_transposed->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = table_state_transition_2_transposed->verticalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "A^T", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = table_estimated_process_noise->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = table_estimated_process_noise->verticalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Q", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Error estimation\n"
"covariance prediction", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "State transition matrix", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Previous error estimation\n"
"covariance prediction", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "State transition matrix\n"
"(transposed)", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Estimated process\n"
"error covariance", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "3) Innovation", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = table_innovation_3->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = table_innovation_3->verticalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = table_measurement->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = table_measurement->verticalHeaderItem(0);
        ___qtablewidgetitem23->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = table_observation_3->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = table_observation_3->verticalHeaderItem(0);
        ___qtablewidgetitem25->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = table_state_predicted_3->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = table_state_predicted_3->verticalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "y_squiggle", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Innovation", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "z_n", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Measurements", 0, QApplication::UnicodeUTF8));
        label_43->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "H", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "x_predicted", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Observation", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Predicted state", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "4) Innovation covariance", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = table_innovation_covariance_4->horizontalHeaderItem(0);
        ___qtablewidgetitem28->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = table_innovation_covariance_4->verticalHeaderItem(0);
        ___qtablewidgetitem29->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_48->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = table_observation_4->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = table_observation_4->verticalHeaderItem(0);
        ___qtablewidgetitem31->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_49->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = table_covariance_predicted_4->horizontalHeaderItem(0);
        ___qtablewidgetitem32->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = table_covariance_predicted_4->verticalHeaderItem(0);
        ___qtablewidgetitem33->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = table_observation_4_transposed->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = table_observation_4_transposed->verticalHeaderItem(0);
        ___qtablewidgetitem35->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "S", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Innovation covariance", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "H", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Observation", 0, QApplication::UnicodeUTF8));
        label_55->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "P_predicted", 0, QApplication::UnicodeUTF8));
        label_56->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "H^T", 0, QApplication::UnicodeUTF8));
        label_57->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Error estimation\n"
"covariance prediction", 0, QApplication::UnicodeUTF8));
        label_58->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Observation\n"
"(transposed)", 0, QApplication::UnicodeUTF8));
        label_59->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = table_estimated_measurement_noise->horizontalHeaderItem(0);
        ___qtablewidgetitem36->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = table_estimated_measurement_noise->verticalHeaderItem(0);
        ___qtablewidgetitem37->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Estimated measurement\n"
"error covariance", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "R", 0, QApplication::UnicodeUTF8));
        label_60->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "5) Kalman gain", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = table_kalman_gain_5->horizontalHeaderItem(0);
        ___qtablewidgetitem38->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = table_kalman_gain_5->verticalHeaderItem(0);
        ___qtablewidgetitem39->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_61->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem40 = table_covariance_predicted_5->horizontalHeaderItem(0);
        ___qtablewidgetitem40->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem41 = table_covariance_predicted_5->verticalHeaderItem(0);
        ___qtablewidgetitem41->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_62->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem42 = table_observation_5_transposed->horizontalHeaderItem(0);
        ___qtablewidgetitem42->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem43 = table_observation_5_transposed->verticalHeaderItem(0);
        ___qtablewidgetitem43->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_63->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem44 = table_innovation_covariance_5_inverted->horizontalHeaderItem(0);
        ___qtablewidgetitem44->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem45 = table_innovation_covariance_5_inverted->verticalHeaderItem(0);
        ___qtablewidgetitem45->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_64->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "K", 0, QApplication::UnicodeUTF8));
        label_65->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Kalman gain", 0, QApplication::UnicodeUTF8));
        label_66->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "P_predicted", 0, QApplication::UnicodeUTF8));
        label_67->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Error estimation\n"
"covariance prediction", 0, QApplication::UnicodeUTF8));
        label_68->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "H^T", 0, QApplication::UnicodeUTF8));
        label_69->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "S^-1", 0, QApplication::UnicodeUTF8));
        label_70->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Observation\n"
"(transposed)", 0, QApplication::UnicodeUTF8));
        label_71->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Innovation covariance\n"
"(inverted)", 0, QApplication::UnicodeUTF8));
        label_72->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "6) State update", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem46 = table_new_state_estimate->horizontalHeaderItem(0);
        ___qtablewidgetitem46->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem47 = table_new_state_estimate->verticalHeaderItem(0);
        ___qtablewidgetitem47->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_73->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem48 = table_state_predicted_6->horizontalHeaderItem(0);
        ___qtablewidgetitem48->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem49 = table_state_predicted_6->verticalHeaderItem(0);
        ___qtablewidgetitem49->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_74->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "+", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem50 = table_kalman_gain_6->horizontalHeaderItem(0);
        ___qtablewidgetitem50->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem51 = table_kalman_gain_6->verticalHeaderItem(0);
        ___qtablewidgetitem51->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_75->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem52 = table_innovation_6->horizontalHeaderItem(0);
        ___qtablewidgetitem52->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem53 = table_innovation_6->verticalHeaderItem(0);
        ___qtablewidgetitem53->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_76->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "x_n", 0, QApplication::UnicodeUTF8));
        label_77->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Newest state estimate", 0, QApplication::UnicodeUTF8));
        label_78->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "x_predicted", 0, QApplication::UnicodeUTF8));
        label_79->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Predicted state", 0, QApplication::UnicodeUTF8));
        label_80->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "K", 0, QApplication::UnicodeUTF8));
        label_81->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "y_squiggle", 0, QApplication::UnicodeUTF8));
        label_82->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Kalman gain", 0, QApplication::UnicodeUTF8));
        label_83->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Innovation", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "7) Covariance update", 0, QApplication::UnicodeUTF8));
        label_84->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "P_n", 0, QApplication::UnicodeUTF8));
        label_85->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "I", 0, QApplication::UnicodeUTF8));
        label_86->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "K", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem54 = table_new_covariance->horizontalHeaderItem(0);
        ___qtablewidgetitem54->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem55 = table_new_covariance->verticalHeaderItem(0);
        ___qtablewidgetitem55->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_87->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "=", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem56 = table_identity_matrix->horizontalHeaderItem(0);
        ___qtablewidgetitem56->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem57 = table_identity_matrix->verticalHeaderItem(0);
        ___qtablewidgetitem57->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_88->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem58 = table_kalman_gain_7->horizontalHeaderItem(0);
        ___qtablewidgetitem58->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem59 = table_kalman_gain_7->verticalHeaderItem(0);
        ___qtablewidgetitem59->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_89->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ".", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem60 = table_observation_7->horizontalHeaderItem(0);
        ___qtablewidgetitem60->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem61 = table_observation_7->verticalHeaderItem(0);
        ___qtablewidgetitem61->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_90->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "H", 0, QApplication::UnicodeUTF8));
        label_91->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", ") .", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem62 = table_covariance_predicted_7->horizontalHeaderItem(0);
        ___qtablewidgetitem62->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem63 = table_covariance_predicted_7->verticalHeaderItem(0);
        ___qtablewidgetitem63->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "a", 0, QApplication::UnicodeUTF8));
        label_93->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Newest error estimation\n"
"covariance estimate", 0, QApplication::UnicodeUTF8));
        label_bottom_2->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Identity matrix", 0, QApplication::UnicodeUTF8));
        label_112->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "(", 0, QApplication::UnicodeUTF8));
        label_98->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "P_predicted", 0, QApplication::UnicodeUTF8));
        label_107->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Error estimation\n"
"covariance prediction", 0, QApplication::UnicodeUTF8));
        label_92->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Kalman gain", 0, QApplication::UnicodeUTF8));
        label_95->setText(QApplication::translate("QtStandardKalmanFilterCalculationDialog", "Observation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtStandardKalmanFilterCalculationDialog: public Ui_QtStandardKalmanFilterCalculationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSTANDARDKALMANFILTERCALCULATIONDIALOG_H
