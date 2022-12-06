#ifndef POPUP_H
#define POPUP_H

#include"QString"
class PopUp
{
private:
  QString icon;
  QString title;
  QString description;
public:
  PopUp();
  PopUp(QString,QString,QString);
  QString getIcon(){return icon;}
  QString getTitel(){return title;}
  QString getDescription(){return description;}
  void setIcon(QString icon){this->icon=icon;}
  void setTitel(QString title){this->title=title;}
  void setDescription(QString description){this->description=description;}

};

#endif // POPUP_H
