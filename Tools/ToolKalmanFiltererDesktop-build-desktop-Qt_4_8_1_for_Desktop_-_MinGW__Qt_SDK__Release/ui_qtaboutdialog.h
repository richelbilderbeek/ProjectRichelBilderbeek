/********************************************************************************
** Form generated from reading UI file 'qtaboutdialog.ui'
**
** Created: Fri 7. Jun 11:45:52 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTABOUTDIALOG_H
#define UI_QTABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QtAboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_title;
    QLabel *label_copyright;
    QLabel *label_author;
    QLabel *label_date;
    QLabel *label_download;
    QLineEdit *edit_url;
    QLabel *label_licence;
    QPlainTextEdit *text_libraries;
    QPlainTextEdit *text_whatsnew;
    QPlainTextEdit *text_licence;
    QLabel *label_build_date_time;
    QLabel *label_build_type;

    void setupUi(QDialog *QtAboutDialog)
    {
        if (QtAboutDialog->objectName().isEmpty())
            QtAboutDialog->setObjectName(QString::fromUtf8("QtAboutDialog"));
        QtAboutDialog->resize(935, 563);
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(12);
        QtAboutDialog->setFont(font);
        verticalLayout = new QVBoxLayout(QtAboutDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_title = new QLabel(QtAboutDialog);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_title->setFont(font1);

        verticalLayout->addWidget(label_title);

        label_copyright = new QLabel(QtAboutDialog);
        label_copyright->setObjectName(QString::fromUtf8("label_copyright"));

        verticalLayout->addWidget(label_copyright);

        label_author = new QLabel(QtAboutDialog);
        label_author->setObjectName(QString::fromUtf8("label_author"));

        verticalLayout->addWidget(label_author);

        label_date = new QLabel(QtAboutDialog);
        label_date->setObjectName(QString::fromUtf8("label_date"));

        verticalLayout->addWidget(label_date);

        label_download = new QLabel(QtAboutDialog);
        label_download->setObjectName(QString::fromUtf8("label_download"));

        verticalLayout->addWidget(label_download);

        edit_url = new QLineEdit(QtAboutDialog);
        edit_url->setObjectName(QString::fromUtf8("edit_url"));
        edit_url->setReadOnly(true);

        verticalLayout->addWidget(edit_url);

        label_licence = new QLabel(QtAboutDialog);
        label_licence->setObjectName(QString::fromUtf8("label_licence"));

        verticalLayout->addWidget(label_licence);

        text_libraries = new QPlainTextEdit(QtAboutDialog);
        text_libraries->setObjectName(QString::fromUtf8("text_libraries"));
        text_libraries->setReadOnly(true);

        verticalLayout->addWidget(text_libraries);

        text_whatsnew = new QPlainTextEdit(QtAboutDialog);
        text_whatsnew->setObjectName(QString::fromUtf8("text_whatsnew"));
        text_whatsnew->setReadOnly(true);

        verticalLayout->addWidget(text_whatsnew);

        text_licence = new QPlainTextEdit(QtAboutDialog);
        text_licence->setObjectName(QString::fromUtf8("text_licence"));
        text_licence->setReadOnly(true);

        verticalLayout->addWidget(text_licence);

        label_build_date_time = new QLabel(QtAboutDialog);
        label_build_date_time->setObjectName(QString::fromUtf8("label_build_date_time"));

        verticalLayout->addWidget(label_build_date_time);

        label_build_type = new QLabel(QtAboutDialog);
        label_build_type->setObjectName(QString::fromUtf8("label_build_type"));

        verticalLayout->addWidget(label_build_type);


        retranslateUi(QtAboutDialog);

        QMetaObject::connectSlotsByName(QtAboutDialog);
    } // setupUi

    void retranslateUi(QDialog *QtAboutDialog)
    {
        QtAboutDialog->setWindowTitle(QApplication::translate("QtAboutDialog", "About", 0, QApplication::UnicodeUTF8));
        label_title->setText(QApplication::translate("QtAboutDialog", "[file_info] version [version]", 0, QApplication::UnicodeUTF8));
        label_copyright->setText(QApplication::translate("QtAboutDialog", "Copyright (C) [years] [author]", 0, QApplication::UnicodeUTF8));
        label_author->setText(QApplication::translate("QtAboutDialog", "Programmed by [author]", 0, QApplication::UnicodeUTF8));
        label_date->setText(QApplication::translate("QtAboutDialog", "[date]", 0, QApplication::UnicodeUTF8));
        label_download->setText(QApplication::translate("QtAboutDialog", "[file_info] can be downloaded from", 0, QApplication::UnicodeUTF8));
        label_licence->setText(QApplication::translate("QtAboutDialog", "Licenced under GPL 3.0", 0, QApplication::UnicodeUTF8));
        text_licence->setPlainText(QString());
        label_build_date_time->setText(QApplication::translate("QtAboutDialog", "Source code built at [date][time]", 0, QApplication::UnicodeUTF8));
        label_build_type->setText(QApplication::translate("QtAboutDialog", "[debug|release] build", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtAboutDialog: public Ui_QtAboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTABOUTDIALOG_H
