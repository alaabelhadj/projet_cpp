/********************************************************************************
** Form generated from reading UI file 'availableofficecard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVAILABLEOFFICECARD_H
#define UI_AVAILABLEOFFICECARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AvailableOfficeCard
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *seeMoreBtn;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;

    void setupUi(QWidget *AvailableOfficeCard)
    {
        if (AvailableOfficeCard->objectName().isEmpty())
            AvailableOfficeCard->setObjectName(QStringLiteral("AvailableOfficeCard"));
        AvailableOfficeCard->resize(338, 46);
        AvailableOfficeCard->setMaximumSize(QSize(16777215, 1677777));
        AvailableOfficeCard->setStyleSheet(QStringLiteral("float:top;"));
        horizontalLayout = new QHBoxLayout(AvailableOfficeCard);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        seeMoreBtn = new QPushButton(AvailableOfficeCard);
        seeMoreBtn->setObjectName(QStringLiteral("seeMoreBtn"));
        seeMoreBtn->setStyleSheet(QLatin1String("#seeMoreBtn\n"
"{\n"
"background-color:#92B4E2;\n"
"border-radius:5px;\n"
"color:#F3F3F3;\n"
"\n"
";}\n"
"#seeMoreBtn:hover\n"
"{\n"
"	background-color:#4A8292;\n"
"	font-weight:bold;\n"
"	color:#F1F1F1;\n"
"}"));

        verticalLayout_2->addWidget(seeMoreBtn);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(63, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox = new QCheckBox(AvailableOfficeCard);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setMaximumSize(QSize(0, 0));

        horizontalLayout->addWidget(checkBox);


        retranslateUi(AvailableOfficeCard);

        QMetaObject::connectSlotsByName(AvailableOfficeCard);
    } // setupUi

    void retranslateUi(QWidget *AvailableOfficeCard)
    {
        AvailableOfficeCard->setWindowTitle(QApplication::translate("AvailableOfficeCard", "Form", Q_NULLPTR));
        seeMoreBtn->setText(QString());
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AvailableOfficeCard: public Ui_AvailableOfficeCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVAILABLEOFFICECARD_H
