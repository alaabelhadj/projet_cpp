#ifndef AVAILABLEOFFICECARD_H
#define AVAILABLEOFFICECARD_H

#include <QWidget>
#include "reservation.h"
namespace Ui {
  class AvailableOfficeCard;
}

class AvailableOfficeCard : public QWidget
{
  Q_OBJECT

public:
  QString id ;
  QString name;
  explicit AvailableOfficeCard(QWidget *parent = nullptr);
  ~AvailableOfficeCard();
//  QString GetOfficeId();
//  void SetOfficeId(QString value);
  QString GetOfficeName();
  void SetOfficeName(QString value);
private:
  Ui::AvailableOfficeCard *ui;
private slots:
    void on_seeMoreBtn_clicked();
signals:
   void sendData(QString, QString);
};

#endif // AVAILABLEOFFICECARD_H
