/********************************************************************************
** Form generated from reading UI file 'popupmodel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPMODEL_H
#define UI_POPUPMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopUpModel
{
public:
    QWidget *container_pop_up;
    QLabel *pop_up_icon;
    QLabel *title_container_pop_up;
    QLabel *description_pop_up;

    void setupUi(QWidget *PopUpModel)
    {
        if (PopUpModel->objectName().isEmpty())
            PopUpModel->setObjectName(QStringLiteral("PopUpModel"));
        PopUpModel->resize(391, 231);
        PopUpModel->setStyleSheet(QLatin1String("background-color:white;\n"
"border-radius:10px"));
        container_pop_up = new QWidget(PopUpModel);
        container_pop_up->setObjectName(QStringLiteral("container_pop_up"));
        container_pop_up->setGeometry(QRect(0, 0, 391, 231));
        container_pop_up->setStyleSheet(QLatin1String("background-color:white;\n"
"border-radius:10px;"));
        pop_up_icon = new QLabel(container_pop_up);
        pop_up_icon->setObjectName(QStringLiteral("pop_up_icon"));
        pop_up_icon->setGeometry(QRect(150, 10, 91, 91));
        pop_up_icon->setPixmap(QPixmap(QString::fromUtf8(":/img/img/success_icon.png")));
        title_container_pop_up = new QLabel(container_pop_up);
        title_container_pop_up->setObjectName(QStringLiteral("title_container_pop_up"));
        title_container_pop_up->setGeometry(QRect(140, 110, 231, 21));
        title_container_pop_up->setStyleSheet(QLatin1String("position: absolute;\n"
"width: 114px;\n"
"height: 30px;\n"
"left: 576px;\n"
"top: 263px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 400;\n"
"font-size: 25px;\n"
"line-height: 30px;\n"
"text-align: center;\n"
"color: #989797;"));
        description_pop_up = new QLabel(container_pop_up);
        description_pop_up->setObjectName(QStringLiteral("description_pop_up"));
        description_pop_up->setGeometry(QRect(64, 160, 301, 31));
        description_pop_up->setStyleSheet(QLatin1String("position: absolute;\n"
"width: 281px;\n"
"height: 32px;\n"
"left: 496px;\n"
"top: 311px;\n"
"\n"
"\n"
"font-style: normal;\n"
"font-weight: 400;\n"
"font-size: 13px;\n"
"line-height: 16px;\n"
"text-align: center;\n"
"\n"
"color: #000000;"));

        retranslateUi(PopUpModel);

        QMetaObject::connectSlotsByName(PopUpModel);
    } // setupUi

    void retranslateUi(QWidget *PopUpModel)
    {
        PopUpModel->setWindowTitle(QApplication::translate("PopUpModel", "Form", Q_NULLPTR));
        pop_up_icon->setText(QString());
        title_container_pop_up->setText(QApplication::translate("PopUpModel", "Success !", Q_NULLPTR));
        description_pop_up->setText(QApplication::translate("PopUpModel", "The product have been added to this staging \n"
"                    table successfully", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PopUpModel: public Ui_PopUpModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPMODEL_H
