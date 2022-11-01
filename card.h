#ifndef CARD_H
#define CARD_H

#include <ui_mainwindow.h>
#include <QWidget>
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

    void setOfficeDescription(QString value);
    QString getOfficeDescription();
    void setOfficeSeeMoreState(QString value);
    QString getOfficeSeeMoreState();
    void setOfficeID(QString value);
    QString getOfficeID();

    ~Card();

private:
    Ui::Card *uiCard;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void on_seeMoreBtn_clicked();

signals:
   void sendData(QString);
};

#endif // CARD_H
