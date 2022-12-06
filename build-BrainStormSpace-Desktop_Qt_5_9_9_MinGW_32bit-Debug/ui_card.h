/********************************************************************************
** Form generated from reading UI file 'card.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARD_H
#define UI_CARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Card
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *image;
    QSpacerItem *horizontalSpacer_2;
    QLabel *name;
    QLabel *label;
    QLabel *id_office;
    QLabel *space_office;
    QLabel *date;
    QLabel *type;
    QLabel *position;
    QLabel *id_reservation;
    QLabel *cin_client;
    QLabel *status;
    QSpacerItem *horizontalSpacer;
    QLabel *officePrice;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QLabel *description;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *seeMoreBtn;

    void setupUi(QWidget *Card)
    {
        if (Card->objectName().isEmpty())
            Card->setObjectName(QStringLiteral("Card"));
        Card->resize(697, 191);
        Card->setMaximumSize(QSize(16777215, 191));
        Card->setStyleSheet(QLatin1String("#Card{\n"
"float:top;\n"
"background-color:white;\n"
"}\n"
"#Card:hover\n"
"{\n"
"	background-color:#EBEBEB;\n"
"}"));
        verticalLayout = new QVBoxLayout(Card);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        image = new QLabel(Card);
        image->setObjectName(QStringLiteral("image"));
        image->setMaximumSize(QSize(64, 64));
        image->setStyleSheet(QStringLiteral("border-radius:10px;"));
        image->setPixmap(QPixmap(QString::fromUtf8(":/brainstorm.png")));
        image->setScaledContents(true);

        horizontalLayout->addWidget(image);

        horizontalSpacer_2 = new QSpacerItem(8, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        name = new QLabel(Card);
        name->setObjectName(QStringLiteral("name"));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        name->setFont(font);
        name->setStyleSheet(QStringLiteral("font-weight:bold;"));

        horizontalLayout->addWidget(name);

        label = new QLabel(Card);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/img/stars.png")));

        horizontalLayout->addWidget(label);

        id_office = new QLabel(Card);
        id_office->setObjectName(QStringLiteral("id_office"));
        id_office->setEnabled(true);

        horizontalLayout->addWidget(id_office);

        space_office = new QLabel(Card);
        space_office->setObjectName(QStringLiteral("space_office"));

        horizontalLayout->addWidget(space_office);

        date = new QLabel(Card);
        date->setObjectName(QStringLiteral("date"));

        horizontalLayout->addWidget(date);

        type = new QLabel(Card);
        type->setObjectName(QStringLiteral("type"));

        horizontalLayout->addWidget(type);

        position = new QLabel(Card);
        position->setObjectName(QStringLiteral("position"));

        horizontalLayout->addWidget(position);

        id_reservation = new QLabel(Card);
        id_reservation->setObjectName(QStringLiteral("id_reservation"));

        horizontalLayout->addWidget(id_reservation);

        cin_client = new QLabel(Card);
        cin_client->setObjectName(QStringLiteral("cin_client"));

        horizontalLayout->addWidget(cin_client);

        status = new QLabel(Card);
        status->setObjectName(QStringLiteral("status"));

        horizontalLayout->addWidget(status);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        officePrice = new QLabel(Card);
        officePrice->setObjectName(QStringLiteral("officePrice"));
        officePrice->setMaximumSize(QSize(128, 16777215));
        officePrice->setStyleSheet(QStringLiteral("color:#159800"));
        officePrice->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(officePrice);

        label_2 = new QLabel(Card);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("color:#159800;"));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        line = new QFrame(Card);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        description = new QLabel(Card);
        description->setObjectName(QStringLiteral("description"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        description->setFont(font1);
        description->setWordWrap(true);

        verticalLayout_2->addWidget(description);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        seeMoreBtn = new QPushButton(Card);
        seeMoreBtn->setObjectName(QStringLiteral("seeMoreBtn"));
        seeMoreBtn->setStyleSheet(QLatin1String("#seeMoreBtn{\n"
"border-radius: 5px;\n"
"background-color:#92B4E2;\n"
"color:white;\n"
"height:22px;\n"
"}\n"
"#seeMoreBtn:hover\n"
"{\n"
"	background-color:#017EFB\n"
"}"));

        horizontalLayout_3->addWidget(seeMoreBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Card);

        QMetaObject::connectSlotsByName(Card);
    } // setupUi

    void retranslateUi(QWidget *Card)
    {
        Card->setWindowTitle(QApplication::translate("Card", "Form", Q_NULLPTR));
        image->setText(QString());
        name->setText(QApplication::translate("Card", "C3", Q_NULLPTR));
        label->setText(QString());
        id_office->setText(QApplication::translate("Card", "id", Q_NULLPTR));
        space_office->setText(QApplication::translate("Card", "space", Q_NULLPTR));
        date->setText(QApplication::translate("Card", "date", Q_NULLPTR));
        type->setText(QApplication::translate("Card", "type", Q_NULLPTR));
        position->setText(QApplication::translate("Card", "position", Q_NULLPTR));
        id_reservation->setText(QApplication::translate("Card", "res", Q_NULLPTR));
        cin_client->setText(QApplication::translate("Card", "cin", Q_NULLPTR));
        status->setText(QApplication::translate("Card", "status", Q_NULLPTR));
        officePrice->setText(QApplication::translate("Card", "16 min", Q_NULLPTR));
        label_2->setText(QApplication::translate("Card", "$", Q_NULLPTR));
        description->setText(QApplication::translate("Card", "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.", Q_NULLPTR));
        seeMoreBtn->setText(QApplication::translate("Card", "See More ...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Card: public Ui_Card {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARD_H
