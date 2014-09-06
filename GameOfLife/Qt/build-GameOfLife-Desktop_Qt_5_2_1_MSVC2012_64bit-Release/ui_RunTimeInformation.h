/********************************************************************************
** Form generated from reading UI file 'RunTimeInformation.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNTIMEINFORMATION_H
#define UI_RUNTIMEINFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RunTimeInformation
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *predatorGroupsBox;
    QListView *listView;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *bestPredatorBox;
    QLabel *labelLifePredator;
    QLabel *labelStrenghPredator;
    QLabel *labelVisionPredator;
    QLabel *labelSpeedPredator;
    QLabel *labelPolicyPredator;
    QLabel *labelGroupIDPredator;
    QLabel *labelStatusPredator;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *preyGroupsBox;
    QListView *listViewPrey;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *bestPreyBox;
    QLabel *labelStrenghPrey;
    QLabel *labelLifePrey;
    QLabel *labelVisionPrey;
    QLabel *labelPolicyPrey;
    QLabel *labelSpeedPrey;
    QLabel *labelStatusPrey;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelIteration;
    QLabel *labelTime;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RunTimeInformation)
    {
        if (RunTimeInformation->objectName().isEmpty())
            RunTimeInformation->setObjectName(QStringLiteral("RunTimeInformation"));
        RunTimeInformation->resize(683, 633);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RunTimeInformation->sizePolicy().hasHeightForWidth());
        RunTimeInformation->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(RunTimeInformation);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 39, 321, 541));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_5);

        predatorGroupsBox = new QGroupBox(verticalLayoutWidget);
        predatorGroupsBox->setObjectName(QStringLiteral("predatorGroupsBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(predatorGroupsBox->sizePolicy().hasHeightForWidth());
        predatorGroupsBox->setSizePolicy(sizePolicy1);
        listView = new QListView(predatorGroupsBox);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(15, 30, 281, 121));

        verticalLayout_2->addWidget(predatorGroupsBox);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_3);

        bestPredatorBox = new QGroupBox(verticalLayoutWidget);
        bestPredatorBox->setObjectName(QStringLiteral("bestPredatorBox"));
        sizePolicy1.setHeightForWidth(bestPredatorBox->sizePolicy().hasHeightForWidth());
        bestPredatorBox->setSizePolicy(sizePolicy1);
        labelLifePredator = new QLabel(bestPredatorBox);
        labelLifePredator->setObjectName(QStringLiteral("labelLifePredator"));
        labelLifePredator->setGeometry(QRect(10, 20, 281, 20));
        labelStrenghPredator = new QLabel(bestPredatorBox);
        labelStrenghPredator->setObjectName(QStringLiteral("labelStrenghPredator"));
        labelStrenghPredator->setGeometry(QRect(10, 40, 281, 20));
        labelVisionPredator = new QLabel(bestPredatorBox);
        labelVisionPredator->setObjectName(QStringLiteral("labelVisionPredator"));
        labelVisionPredator->setGeometry(QRect(10, 80, 281, 20));
        labelSpeedPredator = new QLabel(bestPredatorBox);
        labelSpeedPredator->setObjectName(QStringLiteral("labelSpeedPredator"));
        labelSpeedPredator->setGeometry(QRect(10, 60, 281, 20));
        labelPolicyPredator = new QLabel(bestPredatorBox);
        labelPolicyPredator->setObjectName(QStringLiteral("labelPolicyPredator"));
        labelPolicyPredator->setGeometry(QRect(10, 100, 281, 20));
        labelGroupIDPredator = new QLabel(bestPredatorBox);
        labelGroupIDPredator->setObjectName(QStringLiteral("labelGroupIDPredator"));
        labelGroupIDPredator->setGeometry(QRect(10, 120, 281, 20));
        labelStatusPredator = new QLabel(bestPredatorBox);
        labelStatusPredator->setObjectName(QStringLiteral("labelStatusPredator"));
        labelStatusPredator->setGeometry(QRect(10, 140, 281, 20));

        verticalLayout_2->addWidget(bestPredatorBox);

        verticalSpacer = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(350, 39, 321, 541));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_6);

        preyGroupsBox = new QGroupBox(verticalLayoutWidget_2);
        preyGroupsBox->setObjectName(QStringLiteral("preyGroupsBox"));
        sizePolicy1.setHeightForWidth(preyGroupsBox->sizePolicy().hasHeightForWidth());
        preyGroupsBox->setSizePolicy(sizePolicy1);
        listViewPrey = new QListView(preyGroupsBox);
        listViewPrey->setObjectName(QStringLiteral("listViewPrey"));
        listViewPrey->setGeometry(QRect(15, 30, 281, 121));

        verticalLayout_3->addWidget(preyGroupsBox);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_4);

        bestPreyBox = new QGroupBox(verticalLayoutWidget_2);
        bestPreyBox->setObjectName(QStringLiteral("bestPreyBox"));
        sizePolicy1.setHeightForWidth(bestPreyBox->sizePolicy().hasHeightForWidth());
        bestPreyBox->setSizePolicy(sizePolicy1);
        labelStrenghPrey = new QLabel(bestPreyBox);
        labelStrenghPrey->setObjectName(QStringLiteral("labelStrenghPrey"));
        labelStrenghPrey->setGeometry(QRect(10, 40, 281, 20));
        labelLifePrey = new QLabel(bestPreyBox);
        labelLifePrey->setObjectName(QStringLiteral("labelLifePrey"));
        labelLifePrey->setGeometry(QRect(10, 20, 281, 20));
        labelVisionPrey = new QLabel(bestPreyBox);
        labelVisionPrey->setObjectName(QStringLiteral("labelVisionPrey"));
        labelVisionPrey->setGeometry(QRect(10, 80, 281, 20));
        labelPolicyPrey = new QLabel(bestPreyBox);
        labelPolicyPrey->setObjectName(QStringLiteral("labelPolicyPrey"));
        labelPolicyPrey->setGeometry(QRect(10, 100, 281, 20));
        labelSpeedPrey = new QLabel(bestPreyBox);
        labelSpeedPrey->setObjectName(QStringLiteral("labelSpeedPrey"));
        labelSpeedPrey->setGeometry(QRect(10, 60, 281, 20));
        labelStatusPrey = new QLabel(bestPreyBox);
        labelStatusPrey->setObjectName(QStringLiteral("labelStatusPrey"));
        labelStatusPrey->setGeometry(QRect(10, 120, 281, 20));

        verticalLayout_3->addWidget(bestPreyBox);

        verticalSpacer_2 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_2);

        labelIteration = new QLabel(centralwidget);
        labelIteration->setObjectName(QStringLiteral("labelIteration"));
        labelIteration->setGeometry(QRect(10, 10, 321, 16));
        labelTime = new QLabel(centralwidget);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        labelTime->setGeometry(QRect(350, 10, 321, 16));
        RunTimeInformation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RunTimeInformation);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 683, 26));
        RunTimeInformation->setMenuBar(menubar);
        statusbar = new QStatusBar(RunTimeInformation);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        RunTimeInformation->setStatusBar(statusbar);

        retranslateUi(RunTimeInformation);

        QMetaObject::connectSlotsByName(RunTimeInformation);
    } // setupUi

    void retranslateUi(QMainWindow *RunTimeInformation)
    {
        RunTimeInformation->setWindowTitle(QApplication::translate("RunTimeInformation", "MainWindow", 0));
        label->setText(QApplication::translate("RunTimeInformation", "Predators", 0));
        predatorGroupsBox->setTitle(QApplication::translate("RunTimeInformation", "Groups Information", 0));
        bestPredatorBox->setTitle(QApplication::translate("RunTimeInformation", "Best Creature", 0));
        labelLifePredator->setText(QApplication::translate("RunTimeInformation", "Life", 0));
        labelStrenghPredator->setText(QApplication::translate("RunTimeInformation", "Strengh", 0));
        labelVisionPredator->setText(QApplication::translate("RunTimeInformation", "Vision", 0));
        labelSpeedPredator->setText(QApplication::translate("RunTimeInformation", "Speed", 0));
        labelPolicyPredator->setText(QApplication::translate("RunTimeInformation", "Policy", 0));
        labelGroupIDPredator->setText(QApplication::translate("RunTimeInformation", "GroupID", 0));
        labelStatusPredator->setText(QApplication::translate("RunTimeInformation", "Status", 0));
        label_2->setText(QApplication::translate("RunTimeInformation", "Preys", 0));
        preyGroupsBox->setTitle(QApplication::translate("RunTimeInformation", "Groups Information", 0));
        bestPreyBox->setTitle(QApplication::translate("RunTimeInformation", "Best Creature", 0));
        labelStrenghPrey->setText(QApplication::translate("RunTimeInformation", "Strengh", 0));
        labelLifePrey->setText(QApplication::translate("RunTimeInformation", "Life", 0));
        labelVisionPrey->setText(QApplication::translate("RunTimeInformation", "Vision", 0));
        labelPolicyPrey->setText(QApplication::translate("RunTimeInformation", "Policy", 0));
        labelSpeedPrey->setText(QApplication::translate("RunTimeInformation", "Speed", 0));
        labelStatusPrey->setText(QApplication::translate("RunTimeInformation", "Status", 0));
        labelIteration->setText(QApplication::translate("RunTimeInformation", "Iteration", 0));
        labelTime->setText(QApplication::translate("RunTimeInformation", "Time Per Iteration", 0));
    } // retranslateUi

};

namespace Ui {
    class RunTimeInformation: public Ui_RunTimeInformation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNTIMEINFORMATION_H
