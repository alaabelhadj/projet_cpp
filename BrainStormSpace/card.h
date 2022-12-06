#ifndef CARD_H
#define CARD_H

#include <ui_mainwindow.h>
#include <QWidget>
#include"office.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Card;
}
QT_END_NAMESPACE

class Card : public QWidget
{
    Q_OBJECT


public:
    explicit Card(QWidget *parent = nullptr);
    void setOfficePrice(QString value);
    QString getOfficePrice();

    void setOfficeImage(QString value);
    QString getOfficeImage();
    QString getNameOffice();
    void setNameOffice(QString value);
    QString getPostionOffice();
    void setPositionOffice(QString value);
    QString getSpaceOffice();
    void setSpaceOffice(QString value);
    QString getStatusOffice();
    void setStatusOffice(QString value);
    void setOfficeDescription(QString value);
    QString getOfficeDescription();
    void setOfficeSeeMoreState(QString value);
    QString getOfficeSeeMoreState();
    void setOfficeID(QString value);
    QString getOfficeID();
    QString getDateOffice();
    void setDateOffice(QString value);
    QString getTypeOffice();
    void setTypeOffice(QString value);

QString getIdReservation();
void  setIdReservation(QString value);
    ~Card();

private:
    Ui::Card *uiCard;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void on_seeMoreBtn_clicked();

signals:
   void sendData(Office);
};

#endif // CARD_H
