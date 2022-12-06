#include "reservationcard.h"
#include "ui_reservationcard.h"
#include "QPainter"
#include "reservation.h"
#include <QPainterPath>
ReservationCard::ReservationCard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ReservationCard)
{
  ui->setupUi(this);
  ui->cin_client->setVisible(false);
  ui->id_reservation->setVisible(false);
}

ReservationCard::~ReservationCard()
{
  delete ui;
}

void ReservationCard:: setIdReservation(QString value){
ui->id_reservation->setText(value);
}
QString ReservationCard::getIdReservation()
{
return ui->id_reservation->text();
}
void ReservationCard:: setIdOfficeReservation(QString value){
ui->id_office->setText(value);
}
QString ReservationCard::getIdOfficeReservation()
{
return ui->id_office->text();
}
void ReservationCard:: setCINReservation(QString value){
  ui->cin_client->setText(value);
}
QString ReservationCard:: getCINReservation(){
  return ui->cin_client->text();
}
void ReservationCard:: setCheckInReservation(QString value){
  ui->check_in->setText(value);
}
QString ReservationCard:: getCheckInReservation(){
  return ui->check_in->text();
}
void ReservationCard:: setCheckOutReservation(QString value){
  ui->check_out->setText(value);
}
QString ReservationCard:: getCheckOutReservation(){
  return ui->check_out->text();
}
QString ReservationCard::getNameOfficeReservation()
{
  return ui->name_office->text();
}

void ReservationCard:: setNameOfficeReservation(QString value)
{
  ui->name_office->setText(value) ;

}
void ReservationCard::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QColor backgroundColor = palette().color(QPalette::Light);
    p.setBrush(backgroundColor);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    QPen pen(Qt::white, 0);
    p.setPen(pen);
    p.drawPath(path);
    p.drawRoundedRect(QRect(0,0,width()-1, height()-1),5,5);




}
void ReservationCard::on_seeMoreBtn_clicked()
{
  Reservation  reservation =  Reservation(this->getIdReservation(),this->getIdOfficeReservation(),this->getCINReservation(),this->getCheckInReservation(),this->getCheckOutReservation(),this->getNameOfficeReservation());
  emit sendDataReservation(reservation);
}
