/********************************************************************************
** Form generated from reading UI file 'qtcodetohtmlmaindialog.ui'
**
** Created: Mon 10. Jun 11:58:13 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCODETOHTMLMAINDIALOG_H
#define UI_QTCODETOHTMLMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtCodeToHtmlMainDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_page_type;
    QComboBox *box_header;
    QLabel *label_tech_info;
    QComboBox *box_tech_info;
    QLabel *label_content_type;
    QComboBox *box_source;
    QTabWidget *tab_source;
    QWidget *tab_source_snippet;
    QGridLayout *gridLayout;
    QPlainTextEdit *edit_source_snippet;
    QWidget *tab_source_file;
    QVBoxLayout *verticalLayout;
    QLineEdit *edit_source;
    QTabWidget *tab_widget;
    QWidget *tab_result_webpage;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QWidget *tab_result_text;
    QGridLayout *gridLayout_4;
    QPlainTextEdit *edit_html;
    QPushButton *button_convert;

    void setupUi(QDialog *QtCodeToHtmlMainDialog)
    {
        if (QtCodeToHtmlMainDialog->objectName().isEmpty())
            QtCodeToHtmlMainDialog->setObjectName(QString::fromUtf8("QtCodeToHtmlMainDialog"));
        QtCodeToHtmlMainDialog->setWindowModality(Qt::ApplicationModal);
        QtCodeToHtmlMainDialog->resize(584, 657);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtCodeToHtmlMainDialog->sizePolicy().hasHeightForWidth());
        QtCodeToHtmlMainDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtCodeToHtmlMainDialog->setWindowIcon(icon);
        QtCodeToHtmlMainDialog->setStyleSheet(QString::fromUtf8("QDialog { \n"
"background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0  #808080, stop: 1 #ffffff);\n"
"}\n"
"\n"
"QPushButton { font: 18 px, \"monospace\" }\n"
"QTabWidget { font: 12 px, \"monospace\" }\n"
"QLabel { font: 12px, \"monospace\" }\n"
"QComboBox { font: 12px, \"monospace\" }\n"
"QPlainTextEdit { font: 10px, \"monospace\" }\n"
""));
        gridLayout_2 = new QGridLayout(QtCodeToHtmlMainDialog);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_page_type = new QLabel(QtCodeToHtmlMainDialog);
        label_page_type->setObjectName(QString::fromUtf8("label_page_type"));

        gridLayout_2->addWidget(label_page_type, 0, 0, 1, 1);

        box_header = new QComboBox(QtCodeToHtmlMainDialog);
        box_header->setObjectName(QString::fromUtf8("box_header"));

        gridLayout_2->addWidget(box_header, 0, 1, 1, 1);

        label_tech_info = new QLabel(QtCodeToHtmlMainDialog);
        label_tech_info->setObjectName(QString::fromUtf8("label_tech_info"));

        gridLayout_2->addWidget(label_tech_info, 1, 0, 1, 1);

        box_tech_info = new QComboBox(QtCodeToHtmlMainDialog);
        box_tech_info->setObjectName(QString::fromUtf8("box_tech_info"));

        gridLayout_2->addWidget(box_tech_info, 1, 1, 1, 1);

        label_content_type = new QLabel(QtCodeToHtmlMainDialog);
        label_content_type->setObjectName(QString::fromUtf8("label_content_type"));

        gridLayout_2->addWidget(label_content_type, 2, 0, 1, 1);

        box_source = new QComboBox(QtCodeToHtmlMainDialog);
        box_source->setObjectName(QString::fromUtf8("box_source"));

        gridLayout_2->addWidget(box_source, 2, 1, 1, 1);

        tab_source = new QTabWidget(QtCodeToHtmlMainDialog);
        tab_source->setObjectName(QString::fromUtf8("tab_source"));
        tab_source_snippet = new QWidget();
        tab_source_snippet->setObjectName(QString::fromUtf8("tab_source_snippet"));
        gridLayout = new QGridLayout(tab_source_snippet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        edit_source_snippet = new QPlainTextEdit(tab_source_snippet);
        edit_source_snippet->setObjectName(QString::fromUtf8("edit_source_snippet"));
        edit_source_snippet->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(edit_source_snippet, 0, 0, 1, 1);

        tab_source->addTab(tab_source_snippet, QString());
        tab_source_file = new QWidget();
        tab_source_file->setObjectName(QString::fromUtf8("tab_source_file"));
        verticalLayout = new QVBoxLayout(tab_source_file);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        edit_source = new QLineEdit(tab_source_file);
        edit_source->setObjectName(QString::fromUtf8("edit_source"));

        verticalLayout->addWidget(edit_source);

        tab_source->addTab(tab_source_file, QString());

        gridLayout_2->addWidget(tab_source, 3, 0, 1, 2);

        tab_widget = new QTabWidget(QtCodeToHtmlMainDialog);
        tab_widget->setObjectName(QString::fromUtf8("tab_widget"));
        tab_widget->setMaximumSize(QSize(16777215, 16777215));
        tab_widget->setFocusPolicy(Qt::NoFocus);
        tab_result_webpage = new QWidget();
        tab_result_webpage->setObjectName(QString::fromUtf8("tab_result_webpage"));
        gridLayout_3 = new QGridLayout(tab_result_webpage);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(tab_result_webpage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        tab_widget->addTab(tab_result_webpage, QString());
        tab_result_text = new QWidget();
        tab_result_text->setObjectName(QString::fromUtf8("tab_result_text"));
        gridLayout_4 = new QGridLayout(tab_result_text);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        edit_html = new QPlainTextEdit(tab_result_text);
        edit_html->setObjectName(QString::fromUtf8("edit_html"));
        QFont font;
        font.setFamily(QString::fromUtf8(",monospace"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        edit_html->setFont(font);
        edit_html->setReadOnly(true);

        gridLayout_4->addWidget(edit_html, 0, 0, 1, 1);

        tab_widget->addTab(tab_result_text, QString());

        gridLayout_2->addWidget(tab_widget, 5, 0, 1, 2);

        button_convert = new QPushButton(QtCodeToHtmlMainDialog);
        button_convert->setObjectName(QString::fromUtf8("button_convert"));

        gridLayout_2->addWidget(button_convert, 4, 0, 1, 2);


        retranslateUi(QtCodeToHtmlMainDialog);

        tab_source->setCurrentIndex(0);
        tab_widget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QtCodeToHtmlMainDialog);
    } // setupUi

    void retranslateUi(QDialog *QtCodeToHtmlMainDialog)
    {
        QtCodeToHtmlMainDialog->setWindowTitle(QApplication::translate("QtCodeToHtmlMainDialog", "CodeToHtml", 0, QApplication::UnicodeUTF8));
        label_page_type->setText(QApplication::translate("QtCodeToHtmlMainDialog", "Page type", 0, QApplication::UnicodeUTF8));
        box_header->clear();
        box_header->insertItems(0, QStringList()
         << QApplication::translate("QtCodeToHtmlMainDialog", "C++", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "Music", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "Text", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "Tool", 0, QApplication::UnicodeUTF8)
        );
        label_tech_info->setText(QApplication::translate("QtCodeToHtmlMainDialog", "Technical information", 0, QApplication::UnicodeUTF8));
        box_tech_info->clear();
        box_tech_info->insertItems(0, QStringList()
         << QApplication::translate("QtCodeToHtmlMainDialog", "Auto", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "Yes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "No", 0, QApplication::UnicodeUTF8)
        );
        label_content_type->setText(QApplication::translate("QtCodeToHtmlMainDialog", "Content type", 0, QApplication::UnicodeUTF8));
        box_source->clear();
        box_source->insertItems(0, QStringList()
         << QApplication::translate("QtCodeToHtmlMainDialog", "C++", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "Project file", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QtCodeToHtmlMainDialog", "Text", 0, QApplication::UnicodeUTF8)
        );
        edit_source_snippet->setPlainText(QApplication::translate("QtCodeToHtmlMainDialog", "#include <iostream>\n"
"\n"
"int main()\n"
"{\n"
"  std::cout << \"Hello world\\n\";\n"
"}", 0, QApplication::UnicodeUTF8));
        tab_source->setTabText(tab_source->indexOf(tab_source_snippet), QApplication::translate("QtCodeToHtmlMainDialog", "&1. Text snippet", 0, QApplication::UnicodeUTF8));
        edit_source->setText(QApplication::translate("QtCodeToHtmlMainDialog", "/home/richel/Projects/Tools/ToolCodeToHtml", 0, QApplication::UnicodeUTF8));
        tab_source->setTabText(tab_source->indexOf(tab_source_file), QApplication::translate("QtCodeToHtmlMainDialog", "&2. File or folder", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QtCodeToHtmlMainDialog", "Temporarily removed QWebView due to errors", 0, QApplication::UnicodeUTF8));
        tab_widget->setTabText(tab_widget->indexOf(tab_result_webpage), QApplication::translate("QtCodeToHtmlMainDialog", "&3. Webpage", 0, QApplication::UnicodeUTF8));
        edit_html->setPlainText(QString());
        tab_widget->setTabText(tab_widget->indexOf(tab_result_text), QApplication::translate("QtCodeToHtmlMainDialog", "&4. HTML text", 0, QApplication::UnicodeUTF8));
        button_convert->setText(QApplication::translate("QtCodeToHtmlMainDialog", "&Convert", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtCodeToHtmlMainDialog: public Ui_QtCodeToHtmlMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCODETOHTMLMAINDIALOG_H
