/********************************************************************************
** Form generated from reading UI file 'cppqwebviewexample1dialog.ui'
**
** Created: Wed Jul 17 17:27:53 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPPQWEBVIEWEXAMPLE1DIALOG_H
#define UI_CPPQWEBVIEWEXAMPLE1DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_CppQWebViewExample1Dialog
{
public:
    QGridLayout *gridLayout;
    QWebView *webView;

    void setupUi(QDialog *CppQWebViewExample1Dialog)
    {
        if (CppQWebViewExample1Dialog->objectName().isEmpty())
            CppQWebViewExample1Dialog->setObjectName(QString::fromUtf8("CppQWebViewExample1Dialog"));
        CppQWebViewExample1Dialog->resize(400, 300);
        gridLayout = new QGridLayout(CppQWebViewExample1Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webView = new QWebView(CppQWebViewExample1Dialog);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webView, 0, 0, 1, 1);


        retranslateUi(CppQWebViewExample1Dialog);

        QMetaObject::connectSlotsByName(CppQWebViewExample1Dialog);
    } // setupUi

    void retranslateUi(QDialog *CppQWebViewExample1Dialog)
    {
        CppQWebViewExample1Dialog->setWindowTitle(QApplication::translate("CppQWebViewExample1Dialog", "CppQWebViewExample1Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CppQWebViewExample1Dialog: public Ui_CppQWebViewExample1Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPPQWEBVIEWEXAMPLE1DIALOG_H
