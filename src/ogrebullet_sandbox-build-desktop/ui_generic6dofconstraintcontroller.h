/********************************************************************************
** Form generated from reading UI file 'generic6dofconstraintcontroller.ui'
**
** Created: Thu 7. Apr 14:42:16 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERIC6DOFCONSTRAINTCONTROLLER_H
#define UI_GENERIC6DOFCONSTRAINTCONTROLLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Generic6DofConstraintController
{
public:
    QPushButton *pbSaveChanges;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGroupBox *gbAngularLimits;
    QWidget *gridLayoutWidget_2;
    QGridLayout *glAngularLimits;
    QLabel *lAngularLowerLimit_title;
    QLabel *lAngularUpperLimit_title;
    QLineEdit *leAngularLowerLimit_x;
    QLineEdit *leAngularUpperLimit_x;
    QLineEdit *leAngularLowerLimit_y;
    QLineEdit *leAngularUpperLimit_y;
    QLineEdit *leAngularLowerLimit_z;
    QLineEdit *leAngularUpperLimit_z;
    QGroupBox *gbAngularMotors;
    QWidget *gridLayoutWidget;
    QGridLayout *glAngularMotors;
    QLabel *l_m3;
    QLabel *l_m2;
    QCheckBox *cbEnable_m1;
    QCheckBox *cbEnable_m2;
    QCheckBox *cbEnable_m3;
    QLabel *l_enable_title;
    QLabel *l_targetVelocity_title;
    QLineEdit *leTargetVelocity_m1;
    QLineEdit *leTargetVelocity_m2;
    QLineEdit *leTargetVelocity_m3;
    QLabel *l_maxMotorForce_title;
    QLineEdit *leMaxMotorForce_m1;
    QLineEdit *leMaxMotorForce_m2;
    QLineEdit *leMaxMotorForce_m3;
    QLabel *l_m1;
    QLineEdit *leMaxLimitForce_m1;
    QLineEdit *leMaxLimitForce_m2;
    QLineEdit *leMaxLimitForce_m3;
    QLabel *l_maxMotorForce_title_2;
    QLabel *l_maxMotorForce_title_3;
    QLineEdit *leBounce_m1;
    QLineEdit *leBounce_m2;
    QLineEdit *leBounce_m3;
    QLabel *l_maxMotorForce_title_4;
    QLineEdit *leDamping_m1;
    QLineEdit *leDamping_m2;
    QLineEdit *leDamping_m3;

    void setupUi(QWidget *Generic6DofConstraintController)
    {
        if (Generic6DofConstraintController->objectName().isEmpty())
            Generic6DofConstraintController->setObjectName(QString::fromUtf8("Generic6DofConstraintController"));
        Generic6DofConstraintController->resize(563, 429);
        pbSaveChanges = new QPushButton(Generic6DofConstraintController);
        pbSaveChanges->setObjectName(QString::fromUtf8("pbSaveChanges"));
        pbSaveChanges->setGeometry(QRect(30, 390, 81, 31));
        scrollArea = new QScrollArea(Generic6DofConstraintController);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 531, 371));
        scrollArea->setFrameShape(QFrame::VLine);
        scrollArea->setLineWidth(6);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 412, 419));
        gbAngularLimits = new QGroupBox(scrollAreaWidgetContents_2);
        gbAngularLimits->setObjectName(QString::fromUtf8("gbAngularLimits"));
        gbAngularLimits->setGeometry(QRect(10, 10, 391, 111));
        gridLayoutWidget_2 = new QWidget(gbAngularLimits);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 381, 81));
        glAngularLimits = new QGridLayout(gridLayoutWidget_2);
        glAngularLimits->setObjectName(QString::fromUtf8("glAngularLimits"));
        glAngularLimits->setContentsMargins(0, 0, 0, 0);
        lAngularLowerLimit_title = new QLabel(gridLayoutWidget_2);
        lAngularLowerLimit_title->setObjectName(QString::fromUtf8("lAngularLowerLimit_title"));
        lAngularLowerLimit_title->setMinimumSize(QSize(120, 0));

        glAngularLimits->addWidget(lAngularLowerLimit_title, 0, 0, 1, 1);

        lAngularUpperLimit_title = new QLabel(gridLayoutWidget_2);
        lAngularUpperLimit_title->setObjectName(QString::fromUtf8("lAngularUpperLimit_title"));

        glAngularLimits->addWidget(lAngularUpperLimit_title, 1, 0, 1, 1);

        leAngularLowerLimit_x = new QLineEdit(gridLayoutWidget_2);
        leAngularLowerLimit_x->setObjectName(QString::fromUtf8("leAngularLowerLimit_x"));

        glAngularLimits->addWidget(leAngularLowerLimit_x, 0, 1, 1, 1);

        leAngularUpperLimit_x = new QLineEdit(gridLayoutWidget_2);
        leAngularUpperLimit_x->setObjectName(QString::fromUtf8("leAngularUpperLimit_x"));

        glAngularLimits->addWidget(leAngularUpperLimit_x, 1, 1, 1, 1);

        leAngularLowerLimit_y = new QLineEdit(gridLayoutWidget_2);
        leAngularLowerLimit_y->setObjectName(QString::fromUtf8("leAngularLowerLimit_y"));

        glAngularLimits->addWidget(leAngularLowerLimit_y, 0, 2, 1, 1);

        leAngularUpperLimit_y = new QLineEdit(gridLayoutWidget_2);
        leAngularUpperLimit_y->setObjectName(QString::fromUtf8("leAngularUpperLimit_y"));

        glAngularLimits->addWidget(leAngularUpperLimit_y, 1, 2, 1, 1);

        leAngularLowerLimit_z = new QLineEdit(gridLayoutWidget_2);
        leAngularLowerLimit_z->setObjectName(QString::fromUtf8("leAngularLowerLimit_z"));

        glAngularLimits->addWidget(leAngularLowerLimit_z, 0, 3, 1, 1);

        leAngularUpperLimit_z = new QLineEdit(gridLayoutWidget_2);
        leAngularUpperLimit_z->setObjectName(QString::fromUtf8("leAngularUpperLimit_z"));

        glAngularLimits->addWidget(leAngularUpperLimit_z, 1, 3, 1, 1);

        gbAngularMotors = new QGroupBox(scrollAreaWidgetContents_2);
        gbAngularMotors->setObjectName(QString::fromUtf8("gbAngularMotors"));
        gbAngularMotors->setGeometry(QRect(10, 130, 391, 291));
        gridLayoutWidget = new QWidget(gbAngularMotors);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 380, 251));
        glAngularMotors = new QGridLayout(gridLayoutWidget);
        glAngularMotors->setContentsMargins(0, 0, 0, 0);
        glAngularMotors->setObjectName(QString::fromUtf8("glAngularMotors"));
        glAngularMotors->setSizeConstraint(QLayout::SetDefaultConstraint);
        glAngularMotors->setContentsMargins(0, 0, 0, 0);
        l_m3 = new QLabel(gridLayoutWidget);
        l_m3->setObjectName(QString::fromUtf8("l_m3"));

        glAngularMotors->addWidget(l_m3, 0, 3, 1, 1);

        l_m2 = new QLabel(gridLayoutWidget);
        l_m2->setObjectName(QString::fromUtf8("l_m2"));

        glAngularMotors->addWidget(l_m2, 0, 2, 1, 1);

        cbEnable_m1 = new QCheckBox(gridLayoutWidget);
        cbEnable_m1->setObjectName(QString::fromUtf8("cbEnable_m1"));

        glAngularMotors->addWidget(cbEnable_m1, 1, 1, 1, 1);

        cbEnable_m2 = new QCheckBox(gridLayoutWidget);
        cbEnable_m2->setObjectName(QString::fromUtf8("cbEnable_m2"));

        glAngularMotors->addWidget(cbEnable_m2, 1, 2, 1, 1);

        cbEnable_m3 = new QCheckBox(gridLayoutWidget);
        cbEnable_m3->setObjectName(QString::fromUtf8("cbEnable_m3"));

        glAngularMotors->addWidget(cbEnable_m3, 1, 3, 1, 1);

        l_enable_title = new QLabel(gridLayoutWidget);
        l_enable_title->setObjectName(QString::fromUtf8("l_enable_title"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(l_enable_title->sizePolicy().hasHeightForWidth());
        l_enable_title->setSizePolicy(sizePolicy);
        l_enable_title->setMaximumSize(QSize(100, 16777215));

        glAngularMotors->addWidget(l_enable_title, 1, 0, 1, 1);

        l_targetVelocity_title = new QLabel(gridLayoutWidget);
        l_targetVelocity_title->setObjectName(QString::fromUtf8("l_targetVelocity_title"));
        sizePolicy.setHeightForWidth(l_targetVelocity_title->sizePolicy().hasHeightForWidth());
        l_targetVelocity_title->setSizePolicy(sizePolicy);
        l_targetVelocity_title->setMinimumSize(QSize(120, 0));
        l_targetVelocity_title->setMaximumSize(QSize(100, 16777215));

        glAngularMotors->addWidget(l_targetVelocity_title, 2, 0, 1, 1);

        leTargetVelocity_m1 = new QLineEdit(gridLayoutWidget);
        leTargetVelocity_m1->setObjectName(QString::fromUtf8("leTargetVelocity_m1"));
        leTargetVelocity_m1->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leTargetVelocity_m1->sizePolicy().hasHeightForWidth());
        leTargetVelocity_m1->setSizePolicy(sizePolicy1);
        leTargetVelocity_m1->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leTargetVelocity_m1, 2, 1, 1, 1);

        leTargetVelocity_m2 = new QLineEdit(gridLayoutWidget);
        leTargetVelocity_m2->setObjectName(QString::fromUtf8("leTargetVelocity_m2"));
        sizePolicy1.setHeightForWidth(leTargetVelocity_m2->sizePolicy().hasHeightForWidth());
        leTargetVelocity_m2->setSizePolicy(sizePolicy1);
        leTargetVelocity_m2->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leTargetVelocity_m2, 2, 2, 1, 1);

        leTargetVelocity_m3 = new QLineEdit(gridLayoutWidget);
        leTargetVelocity_m3->setObjectName(QString::fromUtf8("leTargetVelocity_m3"));
        leTargetVelocity_m3->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leTargetVelocity_m3, 2, 3, 1, 1);

        l_maxMotorForce_title = new QLabel(gridLayoutWidget);
        l_maxMotorForce_title->setObjectName(QString::fromUtf8("l_maxMotorForce_title"));
        sizePolicy.setHeightForWidth(l_maxMotorForce_title->sizePolicy().hasHeightForWidth());
        l_maxMotorForce_title->setSizePolicy(sizePolicy);
        l_maxMotorForce_title->setMaximumSize(QSize(100, 16777215));

        glAngularMotors->addWidget(l_maxMotorForce_title, 3, 0, 1, 1);

        leMaxMotorForce_m1 = new QLineEdit(gridLayoutWidget);
        leMaxMotorForce_m1->setObjectName(QString::fromUtf8("leMaxMotorForce_m1"));
        sizePolicy1.setHeightForWidth(leMaxMotorForce_m1->sizePolicy().hasHeightForWidth());
        leMaxMotorForce_m1->setSizePolicy(sizePolicy1);
        leMaxMotorForce_m1->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leMaxMotorForce_m1, 3, 1, 1, 1);

        leMaxMotorForce_m2 = new QLineEdit(gridLayoutWidget);
        leMaxMotorForce_m2->setObjectName(QString::fromUtf8("leMaxMotorForce_m2"));
        leMaxMotorForce_m2->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leMaxMotorForce_m2, 3, 2, 1, 1);

        leMaxMotorForce_m3 = new QLineEdit(gridLayoutWidget);
        leMaxMotorForce_m3->setObjectName(QString::fromUtf8("leMaxMotorForce_m3"));
        leMaxMotorForce_m3->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leMaxMotorForce_m3, 3, 3, 1, 1);

        l_m1 = new QLabel(gridLayoutWidget);
        l_m1->setObjectName(QString::fromUtf8("l_m1"));

        glAngularMotors->addWidget(l_m1, 0, 1, 1, 1);

        leMaxLimitForce_m1 = new QLineEdit(gridLayoutWidget);
        leMaxLimitForce_m1->setObjectName(QString::fromUtf8("leMaxLimitForce_m1"));
        sizePolicy1.setHeightForWidth(leMaxLimitForce_m1->sizePolicy().hasHeightForWidth());
        leMaxLimitForce_m1->setSizePolicy(sizePolicy1);
        leMaxLimitForce_m1->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leMaxLimitForce_m1, 4, 1, 1, 1);

        leMaxLimitForce_m2 = new QLineEdit(gridLayoutWidget);
        leMaxLimitForce_m2->setObjectName(QString::fromUtf8("leMaxLimitForce_m2"));
        leMaxLimitForce_m2->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leMaxLimitForce_m2, 4, 2, 1, 1);

        leMaxLimitForce_m3 = new QLineEdit(gridLayoutWidget);
        leMaxLimitForce_m3->setObjectName(QString::fromUtf8("leMaxLimitForce_m3"));
        leMaxLimitForce_m3->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leMaxLimitForce_m3, 4, 3, 1, 1);

        l_maxMotorForce_title_2 = new QLabel(gridLayoutWidget);
        l_maxMotorForce_title_2->setObjectName(QString::fromUtf8("l_maxMotorForce_title_2"));
        sizePolicy.setHeightForWidth(l_maxMotorForce_title_2->sizePolicy().hasHeightForWidth());
        l_maxMotorForce_title_2->setSizePolicy(sizePolicy);
        l_maxMotorForce_title_2->setMaximumSize(QSize(100, 16777215));

        glAngularMotors->addWidget(l_maxMotorForce_title_2, 4, 0, 1, 1);

        l_maxMotorForce_title_3 = new QLabel(gridLayoutWidget);
        l_maxMotorForce_title_3->setObjectName(QString::fromUtf8("l_maxMotorForce_title_3"));
        sizePolicy.setHeightForWidth(l_maxMotorForce_title_3->sizePolicy().hasHeightForWidth());
        l_maxMotorForce_title_3->setSizePolicy(sizePolicy);
        l_maxMotorForce_title_3->setMaximumSize(QSize(100, 16777215));

        glAngularMotors->addWidget(l_maxMotorForce_title_3, 5, 0, 1, 1);

        leBounce_m1 = new QLineEdit(gridLayoutWidget);
        leBounce_m1->setObjectName(QString::fromUtf8("leBounce_m1"));
        sizePolicy1.setHeightForWidth(leBounce_m1->sizePolicy().hasHeightForWidth());
        leBounce_m1->setSizePolicy(sizePolicy1);
        leBounce_m1->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leBounce_m1, 5, 1, 1, 1);

        leBounce_m2 = new QLineEdit(gridLayoutWidget);
        leBounce_m2->setObjectName(QString::fromUtf8("leBounce_m2"));
        sizePolicy1.setHeightForWidth(leBounce_m2->sizePolicy().hasHeightForWidth());
        leBounce_m2->setSizePolicy(sizePolicy1);
        leBounce_m2->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leBounce_m2, 5, 2, 1, 1);

        leBounce_m3 = new QLineEdit(gridLayoutWidget);
        leBounce_m3->setObjectName(QString::fromUtf8("leBounce_m3"));
        sizePolicy1.setHeightForWidth(leBounce_m3->sizePolicy().hasHeightForWidth());
        leBounce_m3->setSizePolicy(sizePolicy1);
        leBounce_m3->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leBounce_m3, 5, 3, 1, 1);

        l_maxMotorForce_title_4 = new QLabel(gridLayoutWidget);
        l_maxMotorForce_title_4->setObjectName(QString::fromUtf8("l_maxMotorForce_title_4"));
        sizePolicy.setHeightForWidth(l_maxMotorForce_title_4->sizePolicy().hasHeightForWidth());
        l_maxMotorForce_title_4->setSizePolicy(sizePolicy);
        l_maxMotorForce_title_4->setMaximumSize(QSize(100, 16777215));

        glAngularMotors->addWidget(l_maxMotorForce_title_4, 6, 0, 1, 1);

        leDamping_m1 = new QLineEdit(gridLayoutWidget);
        leDamping_m1->setObjectName(QString::fromUtf8("leDamping_m1"));
        sizePolicy1.setHeightForWidth(leDamping_m1->sizePolicy().hasHeightForWidth());
        leDamping_m1->setSizePolicy(sizePolicy1);
        leDamping_m1->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leDamping_m1, 6, 1, 1, 1);

        leDamping_m2 = new QLineEdit(gridLayoutWidget);
        leDamping_m2->setObjectName(QString::fromUtf8("leDamping_m2"));
        sizePolicy1.setHeightForWidth(leDamping_m2->sizePolicy().hasHeightForWidth());
        leDamping_m2->setSizePolicy(sizePolicy1);
        leDamping_m2->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leDamping_m2, 6, 2, 1, 1);

        leDamping_m3 = new QLineEdit(gridLayoutWidget);
        leDamping_m3->setObjectName(QString::fromUtf8("leDamping_m3"));
        sizePolicy1.setHeightForWidth(leDamping_m3->sizePolicy().hasHeightForWidth());
        leDamping_m3->setSizePolicy(sizePolicy1);
        leDamping_m3->setMaximumSize(QSize(80, 16777215));

        glAngularMotors->addWidget(leDamping_m3, 6, 3, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(Generic6DofConstraintController);

        QMetaObject::connectSlotsByName(Generic6DofConstraintController);
    } // setupUi

    void retranslateUi(QWidget *Generic6DofConstraintController)
    {
        Generic6DofConstraintController->setWindowTitle(QApplication::translate("Generic6DofConstraintController", "Form", 0, QApplication::UnicodeUTF8));
        pbSaveChanges->setText(QApplication::translate("Generic6DofConstraintController", "Apply", 0, QApplication::UnicodeUTF8));
        gbAngularLimits->setTitle(QApplication::translate("Generic6DofConstraintController", "Angular Limits", 0, QApplication::UnicodeUTF8));
        lAngularLowerLimit_title->setText(QApplication::translate("Generic6DofConstraintController", "AngularLowerLimit", 0, QApplication::UnicodeUTF8));
        lAngularUpperLimit_title->setText(QApplication::translate("Generic6DofConstraintController", "AngularUpperLimit", 0, QApplication::UnicodeUTF8));
        leAngularUpperLimit_x->setText(QString());
        leAngularUpperLimit_y->setText(QString());
        leAngularUpperLimit_z->setText(QString());
        gbAngularMotors->setTitle(QApplication::translate("Generic6DofConstraintController", "Rotational Motors", 0, QApplication::UnicodeUTF8));
        l_m3->setText(QApplication::translate("Generic6DofConstraintController", "motor 3", 0, QApplication::UnicodeUTF8));
        l_m2->setText(QApplication::translate("Generic6DofConstraintController", "motor 2", 0, QApplication::UnicodeUTF8));
        cbEnable_m1->setText(QString());
        cbEnable_m2->setText(QString());
        cbEnable_m3->setText(QString());
        l_enable_title->setText(QApplication::translate("Generic6DofConstraintController", "m_enable", 0, QApplication::UnicodeUTF8));
        l_targetVelocity_title->setText(QApplication::translate("Generic6DofConstraintController", "m_targetVelocity", 0, QApplication::UnicodeUTF8));
        l_maxMotorForce_title->setText(QApplication::translate("Generic6DofConstraintController", "m_maxMotorForce", 0, QApplication::UnicodeUTF8));
        l_m1->setText(QApplication::translate("Generic6DofConstraintController", "motor 1", 0, QApplication::UnicodeUTF8));
        l_maxMotorForce_title_2->setText(QApplication::translate("Generic6DofConstraintController", "m_maxLimitForce", 0, QApplication::UnicodeUTF8));
        l_maxMotorForce_title_3->setText(QApplication::translate("Generic6DofConstraintController", "m_bounce", 0, QApplication::UnicodeUTF8));
        l_maxMotorForce_title_4->setText(QApplication::translate("Generic6DofConstraintController", "m_damping", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Generic6DofConstraintController: public Ui_Generic6DofConstraintController {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERIC6DOFCONSTRAINTCONTROLLER_H
