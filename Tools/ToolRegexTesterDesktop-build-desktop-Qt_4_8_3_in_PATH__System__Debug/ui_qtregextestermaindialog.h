/********************************************************************************
** Form generated from reading UI file 'qtregextestermaindialog.ui'
**
** Created: Tue May 28 21:41:09 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTREGEXTESTERMAINDIALOG_H
#define UI_QTREGEXTESTERMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtRegexTesterMainDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_regex;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_regex;
    QLineEdit *edit_regex;
    QWidget *widget_line;
    QHBoxLayout *horizontalLayout;
    QLabel *label_line;
    QLineEdit *edit_line;
    QLabel *label_regex_valid;
    QLabel *label_regex_match;
    QLabel *label_regex_found;
    QPlainTextEdit *edit_matching_regexes;
    QWidget *widget_line_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_line_2;
    QLineEdit *edit_format;
    QPlainTextEdit *edit_replaced_regexes;

    void setupUi(QDialog *QtRegexTesterMainDialog)
    {
        if (QtRegexTesterMainDialog->objectName().isEmpty())
            QtRegexTesterMainDialog->setObjectName(QString::fromUtf8("QtRegexTesterMainDialog"));
        QtRegexTesterMainDialog->resize(695, 544);
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(12);
        QtRegexTesterMainDialog->setFont(font);
        QtRegexTesterMainDialog->setStyleSheet(QString::fromUtf8("QDialog { \n"
"  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #B0B0B0, stop: 1 #ffffff);\n"
"}\n"
"QLabel { \n"
"  font-size: 18px;\n"
"  font-family: Courier;\n"
"  font-weight: bold\n"
"}\n"
"QPushButton { \n"
"  font-family: Courier New;\n"
"  font-size: 16px;\n"
"  font-weight: bold;\n"
"  color: black;\n"
"  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #999, stop: 0.1 #aaa, stop: 0.49 #ddd, stop: 0.5 #ccc, stop: 1 #ddd);\n"
"  border-width: 3px;\n"
"  border-color: #444;\n"
"  border-style: solid;\n"
"  border-radius: 7;\n"
"  padding: 3px;\n"
"  padding-left: 5px;\n"
"  padding-right: 5px;\n"
"}"));
        verticalLayout = new QVBoxLayout(QtRegexTesterMainDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_regex = new QWidget(QtRegexTesterMainDialog);
        widget_regex->setObjectName(QString::fromUtf8("widget_regex"));
        horizontalLayout_2 = new QHBoxLayout(widget_regex);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_regex = new QLabel(widget_regex);
        label_regex->setObjectName(QString::fromUtf8("label_regex"));

        horizontalLayout_2->addWidget(label_regex);

        edit_regex = new QLineEdit(widget_regex);
        edit_regex->setObjectName(QString::fromUtf8("edit_regex"));

        horizontalLayout_2->addWidget(edit_regex);


        verticalLayout->addWidget(widget_regex);

        widget_line = new QWidget(QtRegexTesterMainDialog);
        widget_line->setObjectName(QString::fromUtf8("widget_line"));
        horizontalLayout = new QHBoxLayout(widget_line);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_line = new QLabel(widget_line);
        label_line->setObjectName(QString::fromUtf8("label_line"));

        horizontalLayout->addWidget(label_line);

        edit_line = new QLineEdit(widget_line);
        edit_line->setObjectName(QString::fromUtf8("edit_line"));

        horizontalLayout->addWidget(edit_line);


        verticalLayout->addWidget(widget_line);

        label_regex_valid = new QLabel(QtRegexTesterMainDialog);
        label_regex_valid->setObjectName(QString::fromUtf8("label_regex_valid"));
        label_regex_valid->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_regex_valid);

        label_regex_match = new QLabel(QtRegexTesterMainDialog);
        label_regex_match->setObjectName(QString::fromUtf8("label_regex_match"));
        label_regex_match->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_regex_match);

        label_regex_found = new QLabel(QtRegexTesterMainDialog);
        label_regex_found->setObjectName(QString::fromUtf8("label_regex_found"));
        label_regex_found->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_regex_found);

        edit_matching_regexes = new QPlainTextEdit(QtRegexTesterMainDialog);
        edit_matching_regexes->setObjectName(QString::fromUtf8("edit_matching_regexes"));
        edit_matching_regexes->setFocusPolicy(Qt::NoFocus);
        edit_matching_regexes->setReadOnly(true);

        verticalLayout->addWidget(edit_matching_regexes);

        widget_line_2 = new QWidget(QtRegexTesterMainDialog);
        widget_line_2->setObjectName(QString::fromUtf8("widget_line_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_line_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_line_2 = new QLabel(widget_line_2);
        label_line_2->setObjectName(QString::fromUtf8("label_line_2"));

        horizontalLayout_3->addWidget(label_line_2);

        edit_format = new QLineEdit(widget_line_2);
        edit_format->setObjectName(QString::fromUtf8("edit_format"));

        horizontalLayout_3->addWidget(edit_format);


        verticalLayout->addWidget(widget_line_2);

        edit_replaced_regexes = new QPlainTextEdit(QtRegexTesterMainDialog);
        edit_replaced_regexes->setObjectName(QString::fromUtf8("edit_replaced_regexes"));
        edit_replaced_regexes->setFocusPolicy(Qt::NoFocus);
        edit_replaced_regexes->setReadOnly(true);

        verticalLayout->addWidget(edit_replaced_regexes);

        QWidget::setTabOrder(edit_regex, edit_line);
        QWidget::setTabOrder(edit_line, edit_matching_regexes);

        retranslateUi(QtRegexTesterMainDialog);

        QMetaObject::connectSlotsByName(QtRegexTesterMainDialog);
    } // setupUi

    void retranslateUi(QDialog *QtRegexTesterMainDialog)
    {
        QtRegexTesterMainDialog->setWindowTitle(QApplication::translate("QtRegexTesterMainDialog", "Regex tester", 0, QApplication::UnicodeUTF8));
        label_regex->setText(QApplication::translate("QtRegexTesterMainDialog", "Regex: ", 0, QApplication::UnicodeUTF8));
        label_line->setText(QApplication::translate("QtRegexTesterMainDialog", "Line:    ", 0, QApplication::UnicodeUTF8));
        edit_line->setText(QApplication::translate("QtRegexTesterMainDialog", "Both '1234 AB' and '9999 ZZ' are valid Dutch zip codes", 0, QApplication::UnicodeUTF8));
        label_regex_valid->setText(QApplication::translate("QtRegexTesterMainDialog", "Regex valid: yes", 0, QApplication::UnicodeUTF8));
        label_regex_match->setText(QApplication::translate("QtRegexTesterMainDialog", "Regex matches line: yes", 0, QApplication::UnicodeUTF8));
        label_regex_found->setText(QApplication::translate("QtRegexTesterMainDialog", "Regex found in line: yes", 0, QApplication::UnicodeUTF8));
        label_line_2->setText(QApplication::translate("QtRegexTesterMainDialog", "Format:", 0, QApplication::UnicodeUTF8));
        edit_format->setText(QApplication::translate("QtRegexTesterMainDialog", "$0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtRegexTesterMainDialog: public Ui_QtRegexTesterMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTREGEXTESTERMAINDIALOG_H
