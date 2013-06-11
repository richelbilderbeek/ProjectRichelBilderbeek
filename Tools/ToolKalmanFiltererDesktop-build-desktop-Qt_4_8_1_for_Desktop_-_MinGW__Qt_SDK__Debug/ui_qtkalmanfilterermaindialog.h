/********************************************************************************
** Form generated from reading UI file 'qtkalmanfilterermaindialog.ui'
**
** Created: Mon 10. Jun 14:15:15 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTKALMANFILTERERMAINDIALOG_H
#define UI_QTKALMANFILTERERMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtKalmanFiltererMainDialog
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QScrollArea *area_left;
    QWidget *scroll_area_parameters_layout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_start;
    QCheckBox *box_show_calculation;
    QCheckBox *box_show_graphs;
    QTabWidget *tab_widget;
    QWidget *tab_calculation;
    QGridLayout *gridLayout_2;
    QScrollArea *scroll_area_calculation;
    QWidget *scroll_area_calculation_contents;
    QWidget *tab_graph;
    QGridLayout *gridLayout_3;
    QScrollArea *scroll_area_graph;
    QWidget *scroll_area_graph_contents;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_save_graph;

    void setupUi(QDialog *QtKalmanFiltererMainDialog)
    {
        if (QtKalmanFiltererMainDialog->objectName().isEmpty())
            QtKalmanFiltererMainDialog->setObjectName(QString::fromUtf8("QtKalmanFiltererMainDialog"));
        QtKalmanFiltererMainDialog->resize(621, 125);
        gridLayout = new QGridLayout(QtKalmanFiltererMainDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(QtKalmanFiltererMainDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        area_left = new QScrollArea(splitter);
        area_left->setObjectName(QString::fromUtf8("area_left"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(area_left->sizePolicy().hasHeightForWidth());
        area_left->setSizePolicy(sizePolicy);
        area_left->setWidgetResizable(true);
        scroll_area_parameters_layout = new QWidget();
        scroll_area_parameters_layout->setObjectName(QString::fromUtf8("scroll_area_parameters_layout"));
        scroll_area_parameters_layout->setGeometry(QRect(0, 0, 276, 105));
        verticalLayout_2 = new QVBoxLayout(scroll_area_parameters_layout);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        button_start = new QPushButton(scroll_area_parameters_layout);
        button_start->setObjectName(QString::fromUtf8("button_start"));

        verticalLayout_2->addWidget(button_start);

        box_show_calculation = new QCheckBox(scroll_area_parameters_layout);
        box_show_calculation->setObjectName(QString::fromUtf8("box_show_calculation"));
        box_show_calculation->setChecked(false);

        verticalLayout_2->addWidget(box_show_calculation);

        box_show_graphs = new QCheckBox(scroll_area_parameters_layout);
        box_show_graphs->setObjectName(QString::fromUtf8("box_show_graphs"));
        box_show_graphs->setChecked(true);

        verticalLayout_2->addWidget(box_show_graphs);

        area_left->setWidget(scroll_area_parameters_layout);
        splitter->addWidget(area_left);
        tab_widget = new QTabWidget(splitter);
        tab_widget->setObjectName(QString::fromUtf8("tab_widget"));
        tab_calculation = new QWidget();
        tab_calculation->setObjectName(QString::fromUtf8("tab_calculation"));
        gridLayout_2 = new QGridLayout(tab_calculation);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        scroll_area_calculation = new QScrollArea(tab_calculation);
        scroll_area_calculation->setObjectName(QString::fromUtf8("scroll_area_calculation"));
        scroll_area_calculation->setWidgetResizable(true);
        scroll_area_calculation_contents = new QWidget();
        scroll_area_calculation_contents->setObjectName(QString::fromUtf8("scroll_area_calculation_contents"));
        scroll_area_calculation_contents->setGeometry(QRect(0, 0, 294, 61));
        scroll_area_calculation->setWidget(scroll_area_calculation_contents);

        gridLayout_2->addWidget(scroll_area_calculation, 0, 0, 1, 1);

        tab_widget->addTab(tab_calculation, QString());
        tab_graph = new QWidget();
        tab_graph->setObjectName(QString::fromUtf8("tab_graph"));
        gridLayout_3 = new QGridLayout(tab_graph);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        scroll_area_graph = new QScrollArea(tab_graph);
        scroll_area_graph->setObjectName(QString::fromUtf8("scroll_area_graph"));
        scroll_area_graph->setWidgetResizable(true);
        scroll_area_graph_contents = new QWidget();
        scroll_area_graph_contents->setObjectName(QString::fromUtf8("scroll_area_graph_contents"));
        scroll_area_graph_contents->setGeometry(QRect(0, 0, 294, 32));
        scroll_area_graph->setWidget(scroll_area_graph_contents);

        gridLayout_3->addWidget(scroll_area_graph, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 1, 1, 1);

        button_save_graph = new QPushButton(tab_graph);
        button_save_graph->setObjectName(QString::fromUtf8("button_save_graph"));

        gridLayout_3->addWidget(button_save_graph, 2, 0, 1, 1);

        tab_widget->addTab(tab_graph, QString());
        splitter->addWidget(tab_widget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(QtKalmanFiltererMainDialog);

        tab_widget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QtKalmanFiltererMainDialog);
    } // setupUi

    void retranslateUi(QDialog *QtKalmanFiltererMainDialog)
    {
        QtKalmanFiltererMainDialog->setWindowTitle(QApplication::translate("QtKalmanFiltererMainDialog", "KalmanFilterer", 0, QApplication::UnicodeUTF8));
        button_start->setText(QApplication::translate("QtKalmanFiltererMainDialog", "&Start", 0, QApplication::UnicodeUTF8));
        box_show_calculation->setText(QApplication::translate("QtKalmanFiltererMainDialog", "Show calculation", 0, QApplication::UnicodeUTF8));
        box_show_graphs->setText(QApplication::translate("QtKalmanFiltererMainDialog", "Show graphs", 0, QApplication::UnicodeUTF8));
        tab_widget->setTabText(tab_widget->indexOf(tab_calculation), QApplication::translate("QtKalmanFiltererMainDialog", "Calculation", 0, QApplication::UnicodeUTF8));
        button_save_graph->setText(QApplication::translate("QtKalmanFiltererMainDialog", "Save graphs to file", 0, QApplication::UnicodeUTF8));
        tab_widget->setTabText(tab_widget->indexOf(tab_graph), QApplication::translate("QtKalmanFiltererMainDialog", "Graphs", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtKalmanFiltererMainDialog: public Ui_QtKalmanFiltererMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTKALMANFILTERERMAINDIALOG_H
