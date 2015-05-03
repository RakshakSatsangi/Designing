/********************************************************************************
** Form generated from reading UI file 'enternamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERNAMEDIALOG_H
#define UI_ENTERNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_enterNameDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *enterNameDialog)
    {
        if (enterNameDialog->objectName().isEmpty())
            enterNameDialog->setObjectName(QStringLiteral("enterNameDialog"));
        enterNameDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(enterNameDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(enterNameDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 40, 161, 20));
        lineEdit = new QLineEdit(enterNameDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 80, 113, 27));

        retranslateUi(enterNameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), enterNameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), enterNameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(enterNameDialog);
    } // setupUi

    void retranslateUi(QDialog *enterNameDialog)
    {
        enterNameDialog->setWindowTitle(QApplication::translate("enterNameDialog", "Dialog", 0));
        label->setText(QApplication::translate("enterNameDialog", "Enter File/Folder Name", 0));
    } // retranslateUi

};

namespace Ui {
    class enterNameDialog: public Ui_enterNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERNAMEDIALOG_H
