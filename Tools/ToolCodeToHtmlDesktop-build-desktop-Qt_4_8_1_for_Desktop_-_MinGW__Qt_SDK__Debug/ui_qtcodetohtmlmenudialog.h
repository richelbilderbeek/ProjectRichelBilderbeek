/********************************************************************************
** Form generated from reading UI file 'qtcodetohtmlmenudialog.ui'
**
** Created: Mon 10. Jun 11:58:13 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCODETOHTMLMENUDIALOG_H
#define UI_QTCODETOHTMLMENUDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QtCodeToHtmlMenuDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *button_about;
    QPushButton *button_quit;
    QPushButton *button_start;
    QLabel *label;

    void setupUi(QDialog *QtCodeToHtmlMenuDialog)
    {
        if (QtCodeToHtmlMenuDialog->objectName().isEmpty())
            QtCodeToHtmlMenuDialog->setObjectName(QString::fromUtf8("QtCodeToHtmlMenuDialog"));
        QtCodeToHtmlMenuDialog->resize(276, 352);
        QFont font;
        font.setPointSize(20);
        QtCodeToHtmlMenuDialog->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/R.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtCodeToHtmlMenuDialog->setWindowIcon(icon);
        QtCodeToHtmlMenuDialog->setStyleSheet(QString::fromUtf8("QDialog { \n"
"background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0  #808080, stop: 1 #ffffff);\n"
"}\n"
"QPushButton { background-color: rgb(255, 255, 255);  }\n"
"QPushButton { color: rgb(0,0,0); }\n"
"QPushButton { font: 48px, \"monospace\" }"));
        gridLayout = new QGridLayout(QtCodeToHtmlMenuDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        button_about = new QPushButton(QtCodeToHtmlMenuDialog);
        button_about->setObjectName(QString::fromUtf8("button_about"));
        button_about->setFlat(true);

        gridLayout->addWidget(button_about, 2, 0, 1, 1);

        button_quit = new QPushButton(QtCodeToHtmlMenuDialog);
        button_quit->setObjectName(QString::fromUtf8("button_quit"));
        button_quit->setFlat(true);

        gridLayout->addWidget(button_quit, 3, 0, 1, 1);

        button_start = new QPushButton(QtCodeToHtmlMenuDialog);
        button_start->setObjectName(QString::fromUtf8("button_start"));
        button_start->setFlat(true);

        gridLayout->addWidget(button_start, 1, 0, 1, 1);

        label = new QLabel(QtCodeToHtmlMenuDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/ToolCodeToHtmlHelloWorld.png")));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        QWidget::setTabOrder(button_start, button_about);
        QWidget::setTabOrder(button_about, button_quit);

        retranslateUi(QtCodeToHtmlMenuDialog);

        QMetaObject::connectSlotsByName(QtCodeToHtmlMenuDialog);
    } // setupUi

    void retranslateUi(QDialog *QtCodeToHtmlMenuDialog)
    {
        QtCodeToHtmlMenuDialog->setWindowTitle(QApplication::translate("QtCodeToHtmlMenuDialog", "CodeToHtml", 0, QApplication::UnicodeUTF8));
        button_about->setText(QApplication::translate("QtCodeToHtmlMenuDialog", "About", 0, QApplication::UnicodeUTF8));
        button_quit->setText(QApplication::translate("QtCodeToHtmlMenuDialog", "Quit", 0, QApplication::UnicodeUTF8));
        button_start->setText(QApplication::translate("QtCodeToHtmlMenuDialog", "Start", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtCodeToHtmlMenuDialog: public Ui_QtCodeToHtmlMenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCODETOHTMLMENUDIALOG_H
