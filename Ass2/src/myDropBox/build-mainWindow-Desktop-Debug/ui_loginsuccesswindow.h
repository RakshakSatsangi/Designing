/********************************************************************************
** Form generated from reading UI file 'loginsuccesswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSUCCESSWINDOW_H
#define UI_LOGINSUCCESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginSuccessWindow
{
public:
    QWidget *centralwidget;
    QTreeWidget *dirTreeWidget;
    QPushButton *logoutButton;
    QTreeWidget *sharedTreeWidget;
    QTreeWidget *publicTreeWidget;
    QRadioButton *myfileradioButton;
    QRadioButton *sharedradioButton;
    QRadioButton *publicradioButton;
    QLabel *welcomeLabel;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *openButton;
    QPushButton *dldButton;
    QPushButton *SyncButton;
    QPushButton *uploadNewEditionButton;
    QPushButton *uploadButton;
    QPushButton *createFolderButton;
    QPushButton *deleteButton;
    QPushButton *shareButton;
    QPushButton *refreshButton;
    QProgressBar *progressBar;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *loginSuccessWindow)
    {
        if (loginSuccessWindow->objectName().isEmpty())
            loginSuccessWindow->setObjectName(QStringLiteral("loginSuccessWindow"));
        loginSuccessWindow->resize(800, 600);
        QFont font;
        font.setFamily(QStringLiteral("TlwgMono"));
        font.setBold(true);
        font.setWeight(75);
        loginSuccessWindow->setFont(font);
        centralwidget = new QWidget(loginSuccessWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        dirTreeWidget = new QTreeWidget(centralwidget);
        new QTreeWidgetItem(dirTreeWidget);
        dirTreeWidget->setObjectName(QStringLiteral("dirTreeWidget"));
        dirTreeWidget->setGeometry(QRect(10, 40, 581, 391));
        dirTreeWidget->setMinimumSize(QSize(451, 391));
        dirTreeWidget->header()->setDefaultSectionSize(200);
        dirTreeWidget->header()->setMinimumSectionSize(57);
        dirTreeWidget->header()->setStretchLastSection(true);
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName(QStringLiteral("logoutButton"));
        logoutButton->setGeometry(QRect(680, 500, 99, 27));
        logoutButton->setCursor(QCursor(Qt::PointingHandCursor));
        sharedTreeWidget = new QTreeWidget(centralwidget);
        new QTreeWidgetItem(sharedTreeWidget);
        sharedTreeWidget->setObjectName(QStringLiteral("sharedTreeWidget"));
        sharedTreeWidget->setGeometry(QRect(60, 100, 531, 331));
        sharedTreeWidget->header()->setVisible(true);
        sharedTreeWidget->header()->setDefaultSectionSize(150);
        publicTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("Select File"));
        publicTreeWidget->setHeaderItem(__qtreewidgetitem);
        new QTreeWidgetItem(publicTreeWidget);
        publicTreeWidget->setObjectName(QStringLiteral("publicTreeWidget"));
        publicTreeWidget->setGeometry(QRect(110, 150, 481, 281));
        publicTreeWidget->header()->setVisible(true);
        publicTreeWidget->header()->setDefaultSectionSize(180);
        myfileradioButton = new QRadioButton(centralwidget);
        myfileradioButton->setObjectName(QStringLiteral("myfileradioButton"));
        myfileradioButton->setGeometry(QRect(40, 500, 117, 22));
        myfileradioButton->setChecked(true);
        sharedradioButton = new QRadioButton(centralwidget);
        sharedradioButton->setObjectName(QStringLiteral("sharedradioButton"));
        sharedradioButton->setGeometry(QRect(180, 500, 151, 22));
        publicradioButton = new QRadioButton(centralwidget);
        publicradioButton->setObjectName(QStringLiteral("publicradioButton"));
        publicradioButton->setGeometry(QRect(360, 500, 161, 22));
        welcomeLabel = new QLabel(centralwidget);
        welcomeLabel->setObjectName(QStringLiteral("welcomeLabel"));
        welcomeLabel->setGeometry(QRect(20, 10, 201, 20));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setWeight(75);
        welcomeLabel->setFont(font1);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(610, 20, 182, 401));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        openButton = new QPushButton(widget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(openButton);

        dldButton = new QPushButton(widget);
        dldButton->setObjectName(QStringLiteral("dldButton"));
        dldButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(dldButton);

        SyncButton = new QPushButton(widget);
        SyncButton->setObjectName(QStringLiteral("SyncButton"));
        SyncButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(SyncButton);

        uploadNewEditionButton = new QPushButton(widget);
        uploadNewEditionButton->setObjectName(QStringLiteral("uploadNewEditionButton"));
        uploadNewEditionButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(uploadNewEditionButton);

        uploadButton = new QPushButton(widget);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        uploadButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(uploadButton);

        createFolderButton = new QPushButton(widget);
        createFolderButton->setObjectName(QStringLiteral("createFolderButton"));
        createFolderButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(createFolderButton);

        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(deleteButton);

        shareButton = new QPushButton(widget);
        shareButton->setObjectName(QStringLiteral("shareButton"));
        shareButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(shareButton);

        refreshButton = new QPushButton(widget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));
        refreshButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(refreshButton);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(120, 450, 252, 33));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        loginSuccessWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(loginSuccessWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 29));
        loginSuccessWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(loginSuccessWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        loginSuccessWindow->setStatusBar(statusbar);

        retranslateUi(loginSuccessWindow);

        QMetaObject::connectSlotsByName(loginSuccessWindow);
    } // setupUi

    void retranslateUi(QMainWindow *loginSuccessWindow)
    {
        loginSuccessWindow->setWindowTitle(QApplication::translate("loginSuccessWindow", "MainWindow", 0));
        QTreeWidgetItem *___qtreewidgetitem = dirTreeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("loginSuccessWindow", "Source Path", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("loginSuccessWindow", "Folder/File", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("loginSuccessWindow", "Select File", 0));

        const bool __sortingEnabled = dirTreeWidget->isSortingEnabled();
        dirTreeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = dirTreeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(2, QApplication::translate("loginSuccessWindow", "root", 0));
        ___qtreewidgetitem1->setText(1, QApplication::translate("loginSuccessWindow", "Folder", 0));
        ___qtreewidgetitem1->setText(0, QApplication::translate("loginSuccessWindow", "/root", 0));
        dirTreeWidget->setSortingEnabled(__sortingEnabled);

        logoutButton->setText(QApplication::translate("loginSuccessWindow", "Log Out", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = sharedTreeWidget->headerItem();
        ___qtreewidgetitem2->setText(2, QApplication::translate("loginSuccessWindow", "Source Path", 0));
        ___qtreewidgetitem2->setText(1, QApplication::translate("loginSuccessWindow", "Folder/File", 0));
        ___qtreewidgetitem2->setText(0, QApplication::translate("loginSuccessWindow", "Select File", 0));

        const bool __sortingEnabled1 = sharedTreeWidget->isSortingEnabled();
        sharedTreeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem3 = sharedTreeWidget->topLevelItem(0);
        ___qtreewidgetitem3->setText(1, QApplication::translate("loginSuccessWindow", "Folder", 0));
        ___qtreewidgetitem3->setText(0, QApplication::translate("loginSuccessWindow", "Shared_files", 0));
        sharedTreeWidget->setSortingEnabled(__sortingEnabled1);

        QTreeWidgetItem *___qtreewidgetitem4 = publicTreeWidget->headerItem();
        ___qtreewidgetitem4->setText(2, QApplication::translate("loginSuccessWindow", "Source Path", 0));
        ___qtreewidgetitem4->setText(1, QApplication::translate("loginSuccessWindow", "Folder/File", 0));

        const bool __sortingEnabled2 = publicTreeWidget->isSortingEnabled();
        publicTreeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem5 = publicTreeWidget->topLevelItem(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("loginSuccessWindow", "Public_files", 0));
        publicTreeWidget->setSortingEnabled(__sortingEnabled2);

        myfileradioButton->setText(QApplication::translate("loginSuccessWindow", "My Files", 0));
        sharedradioButton->setText(QApplication::translate("loginSuccessWindow", "Shared Files", 0));
        publicradioButton->setText(QApplication::translate("loginSuccessWindow", "Public Files", 0));
        welcomeLabel->setText(QString());
        openButton->setText(QApplication::translate("loginSuccessWindow", "Open", 0));
        dldButton->setText(QApplication::translate("loginSuccessWindow", "Download", 0));
        SyncButton->setText(QApplication::translate("loginSuccessWindow", "Sync", 0));
        uploadNewEditionButton->setText(QApplication::translate("loginSuccessWindow", "Upload New Edition", 0));
        uploadButton->setText(QApplication::translate("loginSuccessWindow", "Upload", 0));
        createFolderButton->setText(QApplication::translate("loginSuccessWindow", "Create Folder", 0));
        deleteButton->setText(QApplication::translate("loginSuccessWindow", "Delete", 0));
        shareButton->setText(QApplication::translate("loginSuccessWindow", "Share", 0));
        refreshButton->setText(QApplication::translate("loginSuccessWindow", "Refresh", 0));
        label->setText(QApplication::translate("loginSuccessWindow", "Search", 0));
    } // retranslateUi

};

namespace Ui {
    class loginSuccessWindow: public Ui_loginSuccessWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSUCCESSWINDOW_H
