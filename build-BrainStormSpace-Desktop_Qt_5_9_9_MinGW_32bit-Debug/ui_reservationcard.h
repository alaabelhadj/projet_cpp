/********************************************************************************
** Form generated from reading UI file 'reservationcard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESERVATIONCARD_H
#define UI_RESERVATIONCARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReservationCard
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *image;
    QLabel *name_office;
    QSpacerItem *horizontalSpacer_7;
    QLabel *id_office;
    QLabel *cin_client;
    QLabel *id_reservation;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer_5;
    QLabel *check_in;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *check_out;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *seeMoreBtn;

    void setupUi(QWidget *ReservationCard)
    {
        if (ReservationCard->objectName().isEmpty())
            ReservationCard->setObjectName(QStringLiteral("ReservationCard"));
        ReservationCard->setWindowModality(Qt::NonModal);
        ReservationCard->resize(697, 191);
        ReservationCard->setMaximumSize(QSize(16777215, 191));
        ReservationCard->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(ReservationCard);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        image = new QLabel(ReservationCard);
        image->setObjectName(QStringLiteral("image"));
        image->setMaximumSize(QSize(64, 64));
        image->setPixmap(QPixmap(QString::fromUtf8(":/img/img/office.png")));

        horizontalLayout->addWidget(image);

        name_office = new QLabel(ReservationCard);
        name_office->setObjectName(QStringLiteral("name_office"));
        name_office->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(name_office);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        id_office = new QLabel(ReservationCard);
        id_office->setObjectName(QStringLiteral("id_office"));

        horizontalLayout->addWidget(id_office);

        cin_client = new QLabel(ReservationCard);
        cin_client->setObjectName(QStringLiteral("cin_client"));

        horizontalLayout->addWidget(cin_client);

        id_reservation = new QLabel(ReservationCard);
        id_reservation->setObjectName(QStringLiteral("id_reservation"));

        horizontalLayout->addWidget(id_reservation);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(ReservationCard);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        horizontalSpacer_5 = new QSpacerItem(4, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        check_in = new QLabel(ReservationCard);
        check_in->setObjectName(QStringLiteral("check_in"));

        horizontalLayout_4->addWidget(check_in);

        horizontalSpacer_4 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_2 = new QLabel(ReservationCard);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_6 = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        check_out = new QLabel(ReservationCard);
        check_out->setObjectName(QStringLiteral("check_out"));

        horizontalLayout_4->addWidget(check_out);

        horizontalSpacer_3 = new QSpacerItem(118, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        seeMoreBtn = new QPushButton(ReservationCard);
        seeMoreBtn->setObjectName(QStringLiteral("seeMoreBtn"));
        seeMoreBtn->setEnabled(true);
        seeMoreBtn->setStyleSheet(QLatin1String("#seeMoreBtn{border-radius: 5px;\n"
"background-color:#92B4E2;\n"
"color:white;\n"
"height:22px;}\n"
""));

        horizontalLayout_2->addWidget(seeMoreBtn);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(ReservationCard);

        QMetaObject::connectSlotsByName(ReservationCard);
    } // setupUi

    void retranslateUi(QWidget *ReservationCard)
    {
        ReservationCard->setWindowTitle(QApplication::translate("ReservationCard", "Form", Q_NULLPTR));
        image->setText(QString());
        name_office->setText(QApplication::translate("ReservationCard", "c3", Q_NULLPTR));
        id_office->setText(QApplication::translate("ReservationCard", "TextLabel", Q_NULLPTR));
        cin_client->setText(QApplication::translate("ReservationCard", "TextLabel", Q_NULLPTR));
        id_reservation->setText(QApplication::translate("ReservationCard", "TextLabel", Q_NULLPTR));
        label->setText(QApplication::translate("ReservationCard", "Check IN:", Q_NULLPTR));
        check_in->setText(QApplication::translate("ReservationCard", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("ReservationCard", "Check OUT:", Q_NULLPTR));
        check_out->setText(QApplication::translate("ReservationCard", "TextLabel", Q_NULLPTR));
        seeMoreBtn->setText(QApplication::translate("ReservationCard", "See More", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReservationCard: public Ui_ReservationCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESERVATIONCARD_H
