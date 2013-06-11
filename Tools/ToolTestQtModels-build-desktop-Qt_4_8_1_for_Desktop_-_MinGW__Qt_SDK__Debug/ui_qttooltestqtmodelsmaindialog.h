/********************************************************************************
** Form generated from reading UI file 'qttooltestqtmodelsmaindialog.ui'
**
** Created: Mon 10. Jun 13:59:42 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTOOLTESTQTMODELSMAINDIALOG_H
#define UI_QTTOOLTESTQTMODELSMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_QtToolTestQtModelsMainDialog
{
public:
    QGridLayout *gridLayout;
    QComboBox *box_type;
    QPushButton *button_data;
    QPushButton *button_headers;
    QTableView *table;
    QPushButton *button_identity_matrix;

    void setupUi(QDialog *QtToolTestQtModelsMainDialog)
    {
        if (QtToolTestQtModelsMainDialog->objectName().isEmpty())
            QtToolTestQtModelsMainDialog->setObjectName(QString::fromUtf8("QtToolTestQtModelsMainDialog"));
        QtToolTestQtModelsMainDialog->resize(453, 375);
        gridLayout = new QGridLayout(QtToolTestQtModelsMainDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        box_type = new QComboBox(QtToolTestQtModelsMainDialog);
        box_type->setObjectName(QString::fromUtf8("box_type"));

        gridLayout->addWidget(box_type, 0, 0, 1, 3);

        button_data = new QPushButton(QtToolTestQtModelsMainDialog);
        button_data->setObjectName(QString::fromUtf8("button_data"));

        gridLayout->addWidget(button_data, 1, 0, 1, 1);

        button_headers = new QPushButton(QtToolTestQtModelsMainDialog);
        button_headers->setObjectName(QString::fromUtf8("button_headers"));

        gridLayout->addWidget(button_headers, 1, 1, 1, 1);

        table = new QTableView(QtToolTestQtModelsMainDialog);
        table->setObjectName(QString::fromUtf8("table"));
        table->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(table, 2, 0, 1, 3);

        button_identity_matrix = new QPushButton(QtToolTestQtModelsMainDialog);
        button_identity_matrix->setObjectName(QString::fromUtf8("button_identity_matrix"));

        gridLayout->addWidget(button_identity_matrix, 1, 2, 1, 1);

        QWidget::setTabOrder(box_type, button_data);
        QWidget::setTabOrder(button_data, button_headers);
        QWidget::setTabOrder(button_headers, table);

        retranslateUi(QtToolTestQtModelsMainDialog);

        QMetaObject::connectSlotsByName(QtToolTestQtModelsMainDialog);
    } // setupUi

    void retranslateUi(QDialog *QtToolTestQtModelsMainDialog)
    {
        QtToolTestQtModelsMainDialog->setWindowTitle(QApplication::translate("QtToolTestQtModelsMainDialog", "ToolTestQtModelsMainDialog", 0, QApplication::UnicodeUTF8));
        box_type->clear();
        box_type->insertItems(0, QStringList()
         << QApplication::translate("QtToolTestQtModelsMainDialog", "std::vector<std::string>", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtToolTestQtModelsMainDialog", "std::vector<std::string> (with function of t)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtToolTestQtModelsMainDialog", "boost::numeric::ublas::matrix", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtToolTestQtModelsMainDialog", "boost::numeric::ublas::vector", 0, QApplication::UnicodeUTF8)
        );
        button_data->setText(QApplication::translate("QtToolTestQtModelsMainDialog", "Put &data in (again)", 0, QApplication::UnicodeUTF8));
        button_headers->setText(QApplication::translate("QtToolTestQtModelsMainDialog", "Put &headers in (again)", 0, QApplication::UnicodeUTF8));
        button_identity_matrix->setText(QApplication::translate("QtToolTestQtModelsMainDialog", "Set identity matrix", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtToolTestQtModelsMainDialog: public Ui_QtToolTestQtModelsMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTOOLTESTQTMODELSMAINDIALOG_H
