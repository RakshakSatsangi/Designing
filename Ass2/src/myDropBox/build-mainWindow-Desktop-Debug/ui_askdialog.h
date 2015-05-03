/********************************************************************************
** Form generated from reading UI file 'askdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASKDIALOG_H
#define UI_ASKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_askDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *textEdit;

    void setupUi(QDialog *askDialog)
    {
        if (askDialog->objectName().isEmpty())
            askDialog->setObjectName(QStringLiteral("askDialog"));
        askDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(askDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textEdit = new QTextEdit(askDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(70, 30, 251, 78));

        retranslateUi(askDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), askDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), askDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(askDialog);
    } // setupUi

    void retranslateUi(QDialog *askDialog)
    {
        askDialog->setWindowTitle(QApplication::translate("askDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class askDialog: public Ui_askDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASKDIALOG_H
