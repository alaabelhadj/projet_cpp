#include "availableofficecard.h"
#include "ui_availableofficecard.h"

AvailableOfficeCard::AvailableOfficeCard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AvailableOfficeCard)
{
  ui->setupUi(this);
}

AvailableOfficeCard::~AvailableOfficeCard()
{
  delete ui;
}


QString AvailableOfficeCard:: GetOfficeName()
{
  return ui->seeMoreBtn->text();
}
void AvailableOfficeCard:: SetOfficeName(QString value)
{
  ui->seeMoreBtn->setText(value);
}
void AvailableOfficeCard::on_seeMoreBtn_clicked()
{
  emit sendData(this->id,this->name);

   if(ui->checkBox->isTristate() == true){
       ui->seeMoreBtn->setStyleSheet("background-color:#4A8292; font-weight:bold; color:#F1F1F1;");

   }else{
        ui->seeMoreBtn->setStyleSheet("background-color:#92B4E2; border-radius:5px; color:#F3F3F3;");
     }
   ui->checkBox->setTristate(!ui->checkBox->isTristate());
}
