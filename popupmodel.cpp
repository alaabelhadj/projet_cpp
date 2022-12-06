#include "popupmodel.h"
#include "ui_popupmodel.h"

PopUpModel::PopUpModel(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PopUpModel)
{
  ui->setupUi(this);
}

PopUpModel::~PopUpModel()
{
  delete ui;
}
QString  PopUpModel::getIcon()
{
  return "you need to impelent this functinolity" ;
}
QString PopUpModel ::getTitel()
{
  return "you need to impelent this functinolity";
}
QString PopUpModel:: getDescription()
{
  return "you need to impelent this functinolity";
}
void PopUpModel:: setIcon(QString icon)
{
  ui->pop_up_icon->setPixmap(icon);
}
void PopUpModel:: setTitel(QString title)
{
  ui->title_container_pop_up->setText(title);
}
void PopUpModel:: setDescription(QString description)
{
  ui->description_pop_up->setText(description);
}


