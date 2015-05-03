/********************************************************************************
** Form generated from reading UI file 'sharedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREDIALOG_H
#define UI_SHAREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_shareDialog
{
public:
    QListWidget *listWidget;
    QLabel *label;
    QRadioButton *publicradioButton;
    QRadioButton *specificradioButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label_2;
    QLabel *pathlabel;

    void setupUi(QDialog *shareDialog)
    {
        if (shareDialog->objectName().isEmpty())
            shareDialog->setObjectName(QStringLiteral("shareDialog"));
        shareDialog->resize(902, 688);
        listWidget = new QListWidget(shareDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(520, 80, 341, 571));
        label = new QLabel(shareDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(520, 30, 191, 31));
        publicradioButton = new QRadioButton(shareDialog);
        publicradioButton->setObjectName(QStringLiteral("publicradioButton"));
        publicradioButton->setGeometry(QRect(40, 140, 171, 22));
        specificradioButton = new QRadioButton(shareDialog);
        specificradioButton->setObjectName(QStringLiteral("specificradioButton"));
        specificradioButton->setGeometry(QRect(40, 190, 241, 22));
        okButton = new QPushButton(shareDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(40, 580, 99, 27));
        cancelButton = new QPushButton(shareDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(180, 580, 99, 27));
        label_2 = new QLabel(shareDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 60, 100, 17));
        pathlabel = new QLabel(shareDialog);
        pathlabel->setObjectName(QStringLiteral("pathlabel"));
        pathlabel->setGeometry(QRect(40, 90, 430, 20));

        retranslateUi(shareDialog);

        QMetaObject::connectSlotsByName(shareDialog);
    } // setupUi

    void retranslateUi(QDialog *shareDialog)
    {
        shareDialog->setWindowTitle(QApplication::translate("shareDialog", "Dialog", 0));
        label->setText(QApplication::translate("shareDialog", "Share with : ", 0));
        publicradioButton->setText(QApplication::translate("shareDialog", "Share with Public", 0));
        specificradioButton->setText(QApplication::translate("shareDialog", "Share with specific user", 0));
        okButton->setText(QApplication::translate("shareDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("shareDialog", "Cancel", 0));
        label_2->setText(QApplication::translate("shareDialog", "Sharing File:", 0));
        pathlabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class shareDialog: public Ui_shareDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREDIALOG_H
