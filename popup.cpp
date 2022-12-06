#include "popup.h"

PopUp::PopUp()
{
  icon="";
  title="";
  description="";
}
PopUp::PopUp(QString icon,QString title,QString description)
{
  this->icon=icon;
  this->title=title;
  this->description=description;
}
