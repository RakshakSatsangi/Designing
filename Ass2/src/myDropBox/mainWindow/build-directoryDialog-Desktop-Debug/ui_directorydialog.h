/********************************************************************************
** Form generated from reading UI file 'directorydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRECTORYDIALOG_H
#define UI_DIRECTORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_directoryDialog
{
public:

    void setupUi(QDialog *directoryDialog)
    {
        if (directoryDialog->objectName().isEmpty())
            directoryDialog->setObjectName(QStringLiteral("directoryDialog"));
        directoryDialog->resize(400, 300);

        retranslateUi(directoryDialog);

        QMetaObject::connectSlotsByName(directoryDialog);
    } // setupUi

    void retranslateUi(QDialog *directoryDialog)
    {
        directoryDialog->setWindowTitle(QApplication::translate("directoryDialog", "directoryDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class directoryDialog: public Ui_directoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRECTORYDIALOG_H
