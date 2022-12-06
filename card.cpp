#include "card.h"
#include "ui_card.h"
#include "ui_card.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
Card::Card(QWidget *parent) :
    QWidget(parent),
    uiCard(new Ui::Card)
{
    uiCard->setupUi(this);
    uiCard->id_office->setVisible(false);
     uiCard->type->setVisible(false);
     uiCard->date->setVisible(false);
     uiCard->space_office->setVisible(false);
    uiCard->position->setVisible(false);
    uiCard->cin_client->setVisible(false);
    uiCard->id_reservation->setVisible(false);
    uiCard->status->setVisible(false);
}

Card::~Card()
{
    delete uiCard;
}

// just to draw a border. could also use stylesheet
void Card::paintEvent(QPaintEvent *event)
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
QString Card:: getPostionOffice(){
  return uiCard->position->text();
}
void Card:: setPositionOffice(QString value){
  uiCard->position->setText(value);
}

QString Card:: getSpaceOffice()
{
  return uiCard->space_office->text();
}
void Card:: setSpaceOffice(QString value)
{
  uiCard->space_office->setText(value);
}

void Card::setOfficePrice(QString value)
{
    uiCard->officePrice->setText(value);
}

QString Card::getOfficePrice()
{
    return uiCard->officePrice->text();
}
void Card::setOfficeID(QString value)
{
    uiCard->id_office->setText(value);
}

QString Card::getOfficeID()
{
    return uiCard->id_office->text();
}
QString Card:: getDateOffice()
{
  return uiCard->date->text();
}
void Card:: setDateOffice(QString value)
{
      uiCard->date->setText(value);
}
QString Card:: getTypeOffice()
{
  return  uiCard->type->text();
}
void Card:: setTypeOffice(QString value)
{
  uiCard->type->setText(value);
}


void Card:: setOfficeImage(QString value){
  uiCard->image->setStyleSheet("border-radius: 10px;");
  QPixmap mypix (value);
  uiCard->image->setPixmap(mypix);
}
QString Card:: getOfficeImage(){

  return uiCard->image->text();
}

void Card:: setOfficeDescription(QString value){
  uiCard->description->setText(value);
}
QString Card:: getOfficeDescription(){
  return uiCard->description->text();

}

void Card::on_seeMoreBtn_clicked()
{

  Office  office =  Office(this->getOfficeID(),this->getOfficeImage(),this->getOfficeDescription(),this->getOfficePrice(),this->getNameOffice(),this->getSpaceOffice(),this->getPostionOffice(),this->getStatusOffice(),this->getTypeOffice(),this->getDateOffice());
  emit sendData(office);
 // emit sendData(this->getNameOffice());
  //emit sendData(this->getSpaceOffice());
  //emit sendData(this->getPostionOffice());
  //emit sendData(this->getOfficeDescription());
}

void Card::setNameOffice(QString value){
  uiCard->name->setText(value);
}
QString Card::getNameOffice(){
   return uiCard->name->text();
}
/*QString Card::getPostionOffice(){
   return this->postion;
}
void Card::setPositionOffice(QString value){
  this->postion=value;
}
QString Card::getSpaceOffice(){
   return this->space;
}*/
void Card:: setIdReservation(QString value){
uiCard->id_reservation->setText(value);
}
QString Card::getIdReservation(){
  return uiCard->id_reservation->text();
}
QString Card::getStatusOffice()
{
  return uiCard->status->text();
}
void Card:: setStatusOffice(QString value)
{
  uiCard->status->setText(value);
}
