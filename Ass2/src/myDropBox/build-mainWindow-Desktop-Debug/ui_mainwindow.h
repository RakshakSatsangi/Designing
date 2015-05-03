/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLabel *label_9;
    QLabel *label_8;
    QPushButton *connectButton;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *logInButton;
    QLineEdit *lineEdit;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QPushButton *createAccButton;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(730, 628);
        QFont font;
        font.setFamily(QStringLiteral("TlwgMono"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit_7 = new QLineEdit(centralWidget);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        gridLayout_2->addWidget(lineEdit_7, 0, 1, 1, 1);

        lineEdit_8 = new QLineEdit(centralWidget);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        gridLayout_2->addWidget(lineEdit_8, 1, 1, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(connectButton->sizePolicy().hasHeightForWidth());
        connectButton->setSizePolicy(sizePolicy);
        connectButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(connectButton, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        QFont font1;
        font1.setPointSize(11);
        lineEdit_2->setFont(font1);
        lineEdit_2->setMaxLength(20);
        lineEdit_2->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, lineEdit_2);

        logInButton = new QPushButton(centralWidget);
        logInButton->setObjectName(QStringLiteral("logInButton"));
        logInButton->setFont(font1);
        logInButton->setCursor(QCursor(Qt::PointingHandCursor));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, logInButton);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lineEdit);


        verticalLayout->addLayout(formLayout_2);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lineEdit_3);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lineEdit_4);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(6, QFormLayout::LabelRole, lineEdit_5);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(8, QFormLayout::LabelRole, lineEdit_6);

        createAccButton = new QPushButton(centralWidget);
        createAccButton->setObjectName(QStringLiteral("createAccButton"));
        createAccButton->setCursor(QCursor(Qt::PointingHandCursor));

        formLayout->setWidget(9, QFormLayout::LabelRole, createAccButton);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setPointSize(21);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);


        verticalLayout->addLayout(formLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 730, 29));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
        label_2->setBuddy(lineEdit_2);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEdit_7, lineEdit_8);
        QWidget::setTabOrder(lineEdit_8, connectButton);
        QWidget::setTabOrder(connectButton, lineEdit);
        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, logInButton);
        QWidget::setTabOrder(logInButton, lineEdit_3);
        QWidget::setTabOrder(lineEdit_3, lineEdit_4);
        QWidget::setTabOrder(lineEdit_4, lineEdit_5);
        QWidget::setTabOrder(lineEdit_5, lineEdit_6);
        QWidget::setTabOrder(lineEdit_6, createAccButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_9->setText(QApplication::translate("MainWindow", "Port No. of Server", 0));
        label_8->setText(QApplication::translate("MainWindow", "IP ADDRESS of Server", 0));
        connectButton->setText(QApplication::translate("MainWindow", "CONNECT", 0));
        label->setText(QApplication::translate("MainWindow", "UserName", 0));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0));
#ifndef QT_NO_WHATSTHIS
        lineEdit_2->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lineEdit_2->setText(QString());
        logInButton->setText(QApplication::translate("MainWindow", "Log In", 0));
        label_4->setText(QApplication::translate("MainWindow", "Enter Your Name", 0));
        label_5->setText(QApplication::translate("MainWindow", "Choose a UserName", 0));
        label_6->setText(QApplication::translate("MainWindow", "Choose a Password", 0));
        label_7->setText(QApplication::translate("MainWindow", "ReType Password", 0));
        createAccButton->setText(QApplication::translate("MainWindow", "Create an account", 0));
        label_3->setText(QApplication::translate("MainWindow", "CREATE AN ACCOUNT", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
