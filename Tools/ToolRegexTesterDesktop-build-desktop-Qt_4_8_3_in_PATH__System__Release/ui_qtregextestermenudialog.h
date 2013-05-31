/********************************************************************************
** Form generated from reading UI file 'qtregextestermenudialog.ui'
**
** Created: Mon May 20 08:34:14 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTREGEXTESTERMENUDIALOG_H
#define UI_QTREGEXTESTERMENUDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_QtRegexTesterMenuDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_tr1_left;
    QPushButton *pushButton;
    QLabel *label_tr1_right;
    QLabel *label_cpp11_left;
    QPushButton *button_find_cpp11;
    QLabel *label_cpp11_right;
    QLabel *label_boost_left;
    QPushButton *button_find_boost;
    QLabel *label_boost_right;
    QLabel *label_qt_left;
    QPushButton *button_find_qt;
    QLabel *label_qt_right;
    QSpacerItem *verticalSpacer;
    QPushButton *button_about;
    QPushButton *button_quit;

    void setupUi(QDialog *QtRegexTesterMenuDialog)
    {
        if (QtRegexTesterMenuDialog->objectName().isEmpty())
            QtRegexTesterMenuDialog->setObjectName(QString::fromUtf8("QtRegexTesterMenuDialog"));
        QtRegexTesterMenuDialog->resize(238, 269);
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        QtRegexTesterMenuDialog->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/PicR.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtRegexTesterMenuDialog->setWindowIcon(icon);
        QtRegexTesterMenuDialog->setStyleSheet(QString::fromUtf8("QDialog { \n"
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
        gridLayout = new QGridLayout(QtRegexTesterMenuDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_tr1_left = new QLabel(QtRegexTesterMenuDialog);
        label_tr1_left->setObjectName(QString::fromUtf8("label_tr1_left"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_tr1_left->sizePolicy().hasHeightForWidth());
        label_tr1_left->setSizePolicy(sizePolicy);
        label_tr1_left->setPixmap(QPixmap(QString::fromUtf8(":/images/PicCppTr1.png")));
        label_tr1_left->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_tr1_left, 0, 0, 1, 1);

        pushButton = new QPushButton(QtRegexTesterMenuDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        label_tr1_right = new QLabel(QtRegexTesterMenuDialog);
        label_tr1_right->setObjectName(QString::fromUtf8("label_tr1_right"));
        sizePolicy.setHeightForWidth(label_tr1_right->sizePolicy().hasHeightForWidth());
        label_tr1_right->setSizePolicy(sizePolicy);
        label_tr1_right->setPixmap(QPixmap(QString::fromUtf8(":/images/PicCppTr1.png")));
        label_tr1_right->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_tr1_right, 0, 2, 1, 1);

        label_cpp11_left = new QLabel(QtRegexTesterMenuDialog);
        label_cpp11_left->setObjectName(QString::fromUtf8("label_cpp11_left"));
        sizePolicy.setHeightForWidth(label_cpp11_left->sizePolicy().hasHeightForWidth());
        label_cpp11_left->setSizePolicy(sizePolicy);
        label_cpp11_left->setPixmap(QPixmap(QString::fromUtf8(":/images/PicCpp11.png")));
        label_cpp11_left->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_cpp11_left, 1, 0, 1, 1);

        button_find_cpp11 = new QPushButton(QtRegexTesterMenuDialog);
        button_find_cpp11->setObjectName(QString::fromUtf8("button_find_cpp11"));
        button_find_cpp11->setEnabled(true);

        gridLayout->addWidget(button_find_cpp11, 1, 1, 1, 1);

        label_cpp11_right = new QLabel(QtRegexTesterMenuDialog);
        label_cpp11_right->setObjectName(QString::fromUtf8("label_cpp11_right"));
        sizePolicy.setHeightForWidth(label_cpp11_right->sizePolicy().hasHeightForWidth());
        label_cpp11_right->setSizePolicy(sizePolicy);
        label_cpp11_right->setPixmap(QPixmap(QString::fromUtf8(":/images/PicCpp11.png")));
        label_cpp11_right->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_cpp11_right, 1, 2, 1, 1);

        label_boost_left = new QLabel(QtRegexTesterMenuDialog);
        label_boost_left->setObjectName(QString::fromUtf8("label_boost_left"));
        sizePolicy.setHeightForWidth(label_boost_left->sizePolicy().hasHeightForWidth());
        label_boost_left->setSizePolicy(sizePolicy);
        label_boost_left->setPixmap(QPixmap(QString::fromUtf8(":/images/PicBoost.png")));
        label_boost_left->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_boost_left, 2, 0, 1, 1);

        button_find_boost = new QPushButton(QtRegexTesterMenuDialog);
        button_find_boost->setObjectName(QString::fromUtf8("button_find_boost"));

        gridLayout->addWidget(button_find_boost, 2, 1, 1, 1);

        label_boost_right = new QLabel(QtRegexTesterMenuDialog);
        label_boost_right->setObjectName(QString::fromUtf8("label_boost_right"));
        sizePolicy.setHeightForWidth(label_boost_right->sizePolicy().hasHeightForWidth());
        label_boost_right->setSizePolicy(sizePolicy);
        label_boost_right->setPixmap(QPixmap(QString::fromUtf8(":/images/PicBoost.png")));
        label_boost_right->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_boost_right, 2, 2, 1, 1);

        label_qt_left = new QLabel(QtRegexTesterMenuDialog);
        label_qt_left->setObjectName(QString::fromUtf8("label_qt_left"));
        sizePolicy.setHeightForWidth(label_qt_left->sizePolicy().hasHeightForWidth());
        label_qt_left->setSizePolicy(sizePolicy);
        label_qt_left->setPixmap(QPixmap(QString::fromUtf8(":/images/PicQt.png")));
        label_qt_left->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_qt_left, 3, 0, 1, 1);

        button_find_qt = new QPushButton(QtRegexTesterMenuDialog);
        button_find_qt->setObjectName(QString::fromUtf8("button_find_qt"));

        gridLayout->addWidget(button_find_qt, 3, 1, 1, 1);

        label_qt_right = new QLabel(QtRegexTesterMenuDialog);
        label_qt_right->setObjectName(QString::fromUtf8("label_qt_right"));
        sizePolicy.setHeightForWidth(label_qt_right->sizePolicy().hasHeightForWidth());
        label_qt_right->setSizePolicy(sizePolicy);
        label_qt_right->setPixmap(QPixmap(QString::fromUtf8(":/images/PicQt.png")));
        label_qt_right->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_qt_right, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        button_about = new QPushButton(QtRegexTesterMenuDialog);
        button_about->setObjectName(QString::fromUtf8("button_about"));

        gridLayout->addWidget(button_about, 5, 0, 1, 3);

        button_quit = new QPushButton(QtRegexTesterMenuDialog);
        button_quit->setObjectName(QString::fromUtf8("button_quit"));

        gridLayout->addWidget(button_quit, 6, 0, 1, 3);

        QWidget::setTabOrder(pushButton, button_find_cpp11);
        QWidget::setTabOrder(button_find_cpp11, button_find_boost);
        QWidget::setTabOrder(button_find_boost, button_find_qt);
        QWidget::setTabOrder(button_find_qt, button_about);
        QWidget::setTabOrder(button_about, button_quit);

        retranslateUi(QtRegexTesterMenuDialog);

        QMetaObject::connectSlotsByName(QtRegexTesterMenuDialog);
    } // setupUi

    void retranslateUi(QDialog *QtRegexTesterMenuDialog)
    {
        QtRegexTesterMenuDialog->setWindowTitle(QApplication::translate("QtRegexTesterMenuDialog", "RegexTester", 0, QApplication::UnicodeUTF8));
        label_tr1_left->setText(QString());
        pushButton->setText(QApplication::translate("QtRegexTesterMenuDialog", "TR1", 0, QApplication::UnicodeUTF8));
        label_tr1_right->setText(QString());
        label_cpp11_left->setText(QString());
        button_find_cpp11->setText(QApplication::translate("QtRegexTesterMenuDialog", "C++11", 0, QApplication::UnicodeUTF8));
        label_cpp11_right->setText(QString());
        label_boost_left->setText(QString());
        button_find_boost->setText(QApplication::translate("QtRegexTesterMenuDialog", "Boost", 0, QApplication::UnicodeUTF8));
        label_boost_right->setText(QString());
        label_qt_left->setText(QString());
        button_find_qt->setText(QApplication::translate("QtRegexTesterMenuDialog", "Qt", 0, QApplication::UnicodeUTF8));
        label_qt_right->setText(QString());
        button_about->setText(QApplication::translate("QtRegexTesterMenuDialog", "&About", 0, QApplication::UnicodeUTF8));
        button_quit->setText(QApplication::translate("QtRegexTesterMenuDialog", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtRegexTesterMenuDialog: public Ui_QtRegexTesterMenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTREGEXTESTERMENUDIALOG_H
