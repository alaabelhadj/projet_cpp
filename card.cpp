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
   // uiCard->id_office->setVisible(false);

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
  emit sendData(this->getOfficeID());
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
