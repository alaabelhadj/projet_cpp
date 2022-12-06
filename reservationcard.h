#ifndef RESERVATIONCARD_H
#define RESERVATIONCARD_H

#include <QWidget>
#include "reservation.h"
namespace Ui {
  class ReservationCard;
}

class ReservationCard : public QWidget
{
  Q_OBJECT

public:
  explicit ReservationCard(QWidget *parent = nullptr);
  ~ReservationCard();

  void paintEvent(QPaintEvent *event);
  void setIdReservation(QString value);
  QString getIdReservation();
  void setCINReservation(QString value);
  QString getCINReservation();
  void setCheckInReservation(QString value);
  QString getCheckInReservation();
  void setCheckOutReservation(QString value);
  QString getCheckOutReservation();
  QString getNameOfficeReservation();
  void setNameOfficeReservation(QString value);
  void setIdOfficeReservation(QString value);
  QString getIdOfficeReservation();


signals:
   void sendDataReservation(Reservation);
private:
  Ui::ReservationCard *ui;
private slots:
    void on_seeMoreBtn_clicked();

};

#endif // RESERVATIONCARD_H
