#include "mainwindow.h"
#include "card.h"
#include "office.h"
#include "ui_mainwindow.h"
#include "officestatistic.h"
#include "QSqlDatabase"
#include "user.h"
#include"QSqlQuery"
#include "popupmodel.h"
#include"QString"
#include <cstring>
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  ui->BackgroundRM->setVisible(false);
  ui->QlineStatOffice->setStyleSheet("background-color:transparent;");
  ui->body->setCurrentIndex(0);
  ui->add_office_widget->setVisible(false);
  ui->id_wtf->setVisible(false);
  ui->pop_up_Sign_Up_STK->setVisible(false);
  ui->check_cercle_ASC->setVisible(false);
  ui->check_cercle_DESC->setVisible(false);
  ui->check_cercle_available->setVisible(false);
  ui->check_cercle_not_available->setVisible(false);
  ui->check_cercle_All->setVisible(true);
  ui->check_cercle_openArea->setVisible(false);
  ui->check_cercle_office->setVisible(false);
  ui->check_cercle_heighest->setVisible(false);
  ui->check_cercle_lowest->setVisible(false);

  ui->space_line_edit->setValidator(new QIntValidator(0,999999999,this));
  ui->Price_line_edit->setValidator(new QIntValidator(0,999999999,this));
  ui->space_line->setValidator(new QIntValidator(0,999999999,this));
  ui->Price_line->setValidator(new QIntValidator(0,999999999,this));
  ui->number_SingUp->setValidator(new QIntValidator(0,999999999,this));




}

MainWindow::~MainWindow()
{
  delete ui;
}
//----------Fonctions-----------------
void MainWindow::on_Username_textChanged(const QString &arg1)
{
      stylee(ui->Username,ui->usernameIconeGrey,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_Username_editingFinished()
{
    stylee(ui->Username,ui->usernameIconeGrey,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_password_textChanged(const QString &arg1)
{
     ui->password->setStyleSheet("border-bottom: 1.5px solid #4A8292;");
}

void MainWindow::on_password_editingFinished()
{
     ui->password->setStyleSheet("border-bottom: 1.5px solid #d9d9d9;");
}

void MainWindow::on_visibilityBtn_clicked()
{

  if(ui->checkBox->isTristate() == true){
      ui->visibilityBtn->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibility.png');background-repeat: no-repeat;");
      ui->password->setEchoMode(QLineEdit::Normal);
  }else{
      ui->visibilityBtn->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibilityOff.png');background-repeat: no-repeat;");
    ui->password->setEchoMode(QLineEdit::Password);
    }
  ui->checkBox->setTristate(!ui->checkBox->isTristate());
}

void MainWindow::on_Username_SingUp_textChanged(const QString &arg1)
{

  stylee(ui->Username_SingUp,ui->usernameIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow::on_Username_SingUp_editingFinished()
{

  stylee(ui->Username_SingUp,ui->usernameIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow::on_SingUpBtn_clicked()
{
    ui->loginForm->setCurrentIndex(1);
}

void MainWindow::on_password_SingUp_textChanged(const QString &arg1)
{
   ui->password_SingUp->setStyleSheet("border-bottom: 1.5px solid #4A8292;");
}

void MainWindow::on_password_SingUp_editingFinished()
{
    ui->password_SingUp->setStyleSheet("border-bottom: 1.5px solid #d9d9d9;");
}

void MainWindow::on_visibilityBtn_SingUp_clicked()
{
  if(ui->checkBox_SingUp->isTristate() == true){
      ui->visibilityBtn_SingUp->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibility.png');background-repeat: no-repeat;");
      ui->password_SingUp->setEchoMode(QLineEdit::Normal);
  }else{
      ui->visibilityBtn_SingUp->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibilityOff.png');background-repeat: no-repeat;");
    ui->password_SingUp->setEchoMode(QLineEdit::Password);
    }
  ui->checkBox_SingUp->setTristate(!ui->checkBox_SingUp->isTristate());
}

void MainWindow::on_email_SingUp_textChanged(const QString &arg1)
{

  stylee(ui->email_SingUp,ui->emailIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_email_SingUp_editingFinished()
{

  stylee(ui->email_SingUp,ui->emailIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/email_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow::on_number_SingUp_textChanged(const QString &arg1)
{

  stylee(ui->number_SingUp,ui->numberIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_number_SingUp_editingFinished()
{
  stylee(ui->number_SingUp,ui->numberIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_SingUpBtn_3_clicked()
{
    ui->loginForm->setCurrentIndex(0);
}

void MainWindow::on_LoginButton_clicked()
{


  QString user=ui->Username->text();
      QString password=ui->password->text();
      QSqlQuery query;
       User P1;
       bool login , check=true;
       login=P1.login_user(user,password);


      if(login)
      {

          ui->mainWidget->setCurrentIndex(1);
          check=false;

      }
      else
        {
          check=true;
        }
      if(check){
          ui->pop_up_Sign_Up_STK->setVisible(true);
          qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
          ui->popup_stacked_widget_2->setCurrentIndex(1);
          QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
          QString title="  Failed !";
          QString description="The UserName Or Password Are Not Correct  !!";
          PopUpModel *pop = new PopUpModel();
          pop->setIcon(icon);
          pop->setTitel(title);
          pop->setDescription(description);
          ui->CardsLayout_3->addWidget(pop);
        }
      else{
          ui->Login->setVisible(false);
          ui->pop_up_Sign_Up_STK->setVisible(false);

        }
}
void MainWindow::on_Reservation_Btn_clicked()
{
    ui->BackgroundOM->setVisible(false);
    ui->BackgroundRM->setVisible(true);
    //Ofice_Btn styling
    QString url = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)";
    QPixmap img(url);
    ui->office_icone->clear();
    ui->office_icone->setPixmap(img);
    QFont font = QFont ("Segoe UI Light");
    ui->Office_Btn->setFont(font);
    //Reservation_Btn styling
    QFont font1 = QFont ("Segoe UI");
    QString url1 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_used.png)";
    QPixmap img1(url1);
    ui->Reservation_Icone->clear();
    ui->Reservation_Icone->setPixmap(img1);
    //OfficeBtn styling
    ui->Reservation_Btn->setFont(font1);
    QString url2 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)";
    QPixmap img2(url2);
    ui->office_icone->clear();
    ui->office_icone->setPixmap(img2);
    QFont font2 = QFont ("Segoe UI Light");
    ui->Office_Btn->setFont(font2);

    //------
    QString url3 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
    QPixmap img3(url3);
    ui->display_offices_icone->clear();
    ui->display_offices_icone->setPixmap(img3);
    QFont font3 = QFont ("Segoe UI Light");
    ui->Display_offices_Btn->setFont(font3);
    //------
    QFont font4 = QFont ("Segoe UI Light");
    QString url4 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)";
    QPixmap img4(url4);
    ui->statistics_offices_icone->clear();
    ui->statistics_offices_icone->setPixmap(img4);
    ui->Statistics_offices_Btn->setFont(font4);
    QString url5 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
    QPixmap img5(url5);
    ui->display_offices_icone_res->clear();
    ui->display_offices_icone_res->setPixmap(img5);
    QFont font5 = QFont ("Segoe UI ");
    ui->Display_offices_Reservation_btn->setFont(font5);

}
void MainWindow:: on_Display_offices_Reservation_btn_clicked()
{
  QString url = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
  QPixmap img(url);
  ui->display_offices_icone->clear();
  ui->display_offices_icone->setPixmap(img);
  QFont font = QFont ("Segoe UI Light ");
  ui->Display_offices_Btn->setFont(font);
  //Statistics_offices styling
  QFont font1 = QFont ("Segoe UI Light");
  QString url1 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)";
  QPixmap img1(url1);
  ui->statistics_offices_icone->clear();
  ui->statistics_offices_icone->setPixmap(img1);
  ui->Statistics_offices_Btn->setFont(font1);
  //-----------------------
  ui->BackgroundRM->setVisible(true);
  QFont font2 = QFont ("Segoe UI");
  QString url2 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_used.png)";
  QPixmap img2(url2);
  ui->Reservation_Icone->clear();
  ui->Reservation_Icone->setPixmap(img2);
  ui->Reservation_Btn->setFont(font2);
  QString url3 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)";
  QPixmap img3(url3);
  ui->office_icone->clear();
  ui->office_icone->setPixmap(img3);
  QFont font3 = QFont ("Segoe UI Light");
  ui->Office_Btn->setFont(font3);
  ui->BackgroundOM->setVisible(false);
  ui->body->setCurrentIndex(0);
  //---------------------------------------------
  QString url5 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)";
  QPixmap img5(url5);
  ui->display_offices_icone_res->clear();
  ui->display_offices_icone_res->setPixmap(img5);
  QFont font5 = QFont ("Segoe UI ");
  ui->Display_offices_Reservation_btn->setFont(font5);

}

void MainWindow::on_Office_Btn_clicked()
{
  ui->BackgroundOM->setVisible(true);
  ui->BackgroundRM->setVisible(false);
  QString url = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)";
  QPixmap img(url);
  ui->office_icone->clear();
  ui->office_icone->setPixmap(img);
  QFont font = QFont ("Segoe UI");
  ui->Office_Btn->setFont(font);
  //OfficeBtn styling
  QFont font1 = QFont ("Segoe UI Light");
  QString url1 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)";
  QPixmap img1(url1);
  ui->Reservation_Icone->clear();
  ui->Reservation_Icone->setPixmap(img1);
  ui->Reservation_Btn->setFont(font1);
  //-----------------
  QString url2 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)";
  QPixmap img2(url2);
  ui->display_offices_icone->clear();
  ui->display_offices_icone->setPixmap(img2);
  QFont font2 = QFont ("Segoe UI ");
  ui->Display_offices_Btn->setFont(font2);
  ui->body->setCurrentIndex(0);
    ui->Reservation_Btn->setFont(font1);
    //---------------------------------------
    QString url5 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
    QPixmap img5(url5);
    ui->display_offices_icone_res->clear();
    ui->display_offices_icone_res->setPixmap(img5);
    QFont font5 = QFont ("Segoe UI Light ");
    ui->Display_offices_Reservation_btn->setFont(font5);
}





void MainWindow::on_Statistics_offices_Btn_clicked()
{
  //display offices styling
   QString url = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
  ui->body->setCurrentIndex(1);
   QPixmap img(url);
   ui->display_offices_icone->clear();
   ui->display_offices_icone->setPixmap(img);
   QFont font = QFont ("Segoe UI Light");
   ui->Display_offices_Btn->setFont(font);
   //Statistics_offices styling
   QFont font1 = QFont ("Segoe UI");
   QString url1 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUsed.png)";
   QPixmap img1(url1);
   ui->statistics_offices_icone->clear();
   ui->statistics_offices_icone->setPixmap(img1);
   ui->Statistics_offices_Btn->setFont(font1);
   //----------------
   ui->BackgroundRM->setVisible(false);
     ui->Reservation_Btn->setFont(font);
   QFont font2 = QFont ("Segoe UI");
   QString url2 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)";
   QPixmap img2(url2);
   ui->Reservation_Icone->clear();
   ui->Reservation_Icone->setPixmap(img2);
   QString url3 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)";
   QPixmap img3(url3);
   ui->office_icone->clear();
   ui->office_icone->setPixmap(img3);
   QFont font3 = QFont ("Segoe UI");
   ui->Office_Btn->setFont(font3);
   ui->BackgroundOM->setVisible(true);
   //---------------------------------
   QString url5 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
   QPixmap img5(url5);
   ui->display_offices_icone_res->clear();
   ui->display_offices_icone_res->setPixmap(img5);
   QFont font5 = QFont ("Segoe UI Light ");
   ui->Display_offices_Reservation_btn->setFont(font5);
   // create statistic
 QLineSeries *series = new QLineSeries();
   // statistic implementation for Qline stat office
   // y Axe
   series->append(0,6);
   series->append(2,4);
   series->append(3,8);
   series->append(7,4);
   series->append(10,5);
 // X Axe
   *series << QPointF(11,1) << QPointF(13,3) << QPointF(17,3) << QPointF(18,3) <<QPointF(20,2);
 QChart *chart = new QChart();
 chart->legend()->hide();
 chart->addSeries(series);
 chart->createDefaultAxes();
 chart->setTitle("Line Chart Offices");

 QChartView * chartView=new QChartView(chart);

 chartView->setRenderHints(QPainter::Antialiasing);
 QVBoxLayout *layout = new QVBoxLayout(ui->QlineStatOffice);
 layout->addWidget(chartView);

 QPieSeries *series1 = new QPieSeries();

 series1->append("Open Area",300);

 series1->append("Offices",10);

 QChart * chart1=new QChart();

 chart1->addSeries(series1);

 chart1->setTitle("stats");

 QChartView * chartView1=new QChartView(chart1);

 chartView1->setRenderHints(QPainter::Antialiasing);
 QVBoxLayout *layout1 = new QVBoxLayout(ui->QPieStatOffice);
 layout1->addWidget(chartView1);
 //---------------------------------------------------------------------------------------
 OfficeStatistic office1;

 QString earnings =QString::number(office1.getEarnings());
 QString availabiltyon =QString::number(office1.getAvailabiltyOn());
 QString availabiltyoff =QString::number(office1.getAvailibiltyOff());
 QString name1,name2,name3,name4,name5,name6;
 int somme1,somme2,somme3,somme4,somme5,somme6;
 ui->earning_sum->setText(earnings);
 ui->available_offices->setText(availabiltyon);
 ui->Not_available_offices->setText(availabiltyoff);
 somme1=office1.getOfficeFirstMonth(name1);
 somme2=office1.getOfficeSecondMonth(name2);
 somme3=office1.getOfficeThirdMonth(name3);
 QString sommest =QString::number(somme1);
  QString sommest1 =QString::number(somme2);
 QString sommest2 =QString::number(somme3);
 somme4=office1.getOfficeFirstMonth(name4);
 somme5=office1.getOfficeSecondMonth(name5);
 somme6=office1.getOfficeThirdMonth(name6);
 QString sommest3 =QString::number(somme4);
  QString sommest4 =QString::number(somme5);
 QString sommest5 =QString::number(somme6);
 ui->green_price_best->setText(sommest);
 ui->green_price_best2->setText(sommest1);
 ui->green_price_best3->setText(sommest2);
 ui->red_label_worst->setText(sommest3);
 ui->red_price_worst2->setText(sommest4);
 ui->red_price_worst3->setText(sommest5);
 ui->office_name_best1->setText(name1);
 ui->office_name_best2->setText(name2);
 ui->office_name_best3->setText(name3);
 ui->office_name_worst1->setText(name4);
 ui->office_name_worst2->setText(name5);
 ui->office_name_worst3->setText(name1);



}


void MainWindow::on_Display_offices_Btn_clicked()
{ //
  QString url = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)";
  QPixmap img(url);
  ui->display_offices_icone->clear();
  ui->display_offices_icone->setPixmap(img);
  QFont font = QFont ("Segoe UI ");
  ui->Display_offices_Btn->setFont(font);
  //Statistics_offices styling
  QFont font1 = QFont ("Segoe UI Light");
  QString url1 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)";
  QPixmap img1(url1);
  ui->statistics_offices_icone->clear();
  ui->statistics_offices_icone->setPixmap(img1);
  ui->Statistics_offices_Btn->setFont(font1);
  //-----------------------
  ui->BackgroundRM->setVisible(false);
  QFont font2 = QFont ("Segoe UI");
  QString url2 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)";
  QPixmap img2(url2);
  ui->Reservation_Icone->clear();
  ui->Reservation_Icone->setPixmap(img2);
      ui->Reservation_Btn->setFont(font1);
  QString url3 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)";
  QPixmap img3(url3);
  ui->office_icone->clear();
  ui->office_icone->setPixmap(img3);
  QFont font3 = QFont ("Segoe UI");
  ui->Office_Btn->setFont(font3);
  ui->BackgroundOM->setVisible(true);
  //-----------------------------
  QString url5 = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)";
  QPixmap img5(url5);
  ui->display_offices_icone_res->clear();
  ui->display_offices_icone_res->setPixmap(img5);
  QFont font5 = QFont ("Segoe UI Light ");
  ui->Display_offices_Reservation_btn->setFont(font5);
  ui->body->setCurrentIndex(0);


dataSet.erase(dataSet.begin(),dataSet.end()) ;
qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


Office * office;
dataSet = office->getAllOffices();
std::list<Office*>::iterator it1;


std::list<Office*>::iterator it;
for (it = dataSet.begin(); it != dataSet.end(); ++it){
    Card *card = new Card();
    card->setOfficeID((*it)->getIdOffice());
    card->setNameOffice((*it)->getNameOffice());
    card->setOfficePrice((*it)->getPrice());
    card->setOfficeDescription((*it)->getDescription());
    card->setOfficeImage((*it)->getImage());
    connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
     ui->CardsLayout->addWidget(card);
}
}

void MainWindow::recieveData(QString str)
{

    ui->body->setCurrentIndex(3);
    //ui->idOffice->setText(str);
    ui->id_wtf->setText(str);

}
void MainWindow::on_exit_add_office_clicked()
{
    ui->add_office_widget->setVisible(false);
}

void MainWindow::on_pushButton_clicked()
{
     ui->add_office_widget->setVisible(true);
}

void MainWindow::on_exit_button_clicked()
{
    ui->add_office_widget->setVisible(false);
}

void MainWindow::on_office_Name_line_textChanged(const QString &arg1)
{
  stylee(ui->office_Name_line,ui->officeName_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_office_Name_line_editingFinished()
{
  stylee(ui->office_Name_line,ui->officeName_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow::on_space_line_textChanged(const QString &arg1)
{
  stylee(ui->space_line,ui->space_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/space_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_space_line_editingFinished()
{
  stylee(ui->space_line,ui->space_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/space_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_position_line_textChanged(const QString &arg1)
{
stylee(ui->position_line,ui->position_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_position_line_editingFinished()
{
  stylee(ui->position_line,ui->position_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Price_line_textChanged(const QString &arg1)
{
  stylee(ui->Price_line,ui->price_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeBlue.png","border-bottom: 1.5px solid #4A8292;border-radius:unset;");
}


void MainWindow::on_Price_line_editingFinished()
{
    stylee(ui->Price_line,ui->price_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void stylee(QLineEdit *e,QLabel *icone,QString url,QString styleSheet){
  e->setStyleSheet(styleSheet);
  QPixmap img(url);
  icone->clear();
  icone->setPixmap(img);

}
void MainWindow::on_description_line_textChanged(const QString &arg1)
{
  stylee(ui->description_line,ui->description_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/description_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}


void MainWindow::on_description_line_editingFinished()
{
  stylee(ui->description_line,ui->description_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/description_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_add_office_btn_clicked()
{

      ui->add_office_widget->setVisible(true);

}

void MainWindow::on_exit_add_popup_clicked()
{
    ui->add_office_widget->setVisible(false);
}


void MainWindow::on_add_office_button_clicked()
{
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));

  QString id_office;
  QString image = "C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/office.png";//we have to make url line in the pop up widget
  QString description=ui->description_line->text();
  QString price=ui->Price_line->text();
  QString name=ui->office_Name_line->text();
  QString space=ui->space_line->text();
  QString position=ui->position_line->text();
  QString status="available";
  QString type=ui->type_line->text();

  if(ui->type_line->text()== ""){
        type="office";
    }
  QString date=ui->date_line->text();


  Office * office = new Office(id_office,image,description,price,name,space,position,status,type,date);

  Office stock(id_office,image,description,price,name,space,position,status,type,date);
  bool check=stock.add_office_database();
  if(check){
      qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/success_icon.png";
      QString title="Success !";
      QString description="The product have been added to this staging \n                    table successfully";

      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_2->addWidget(pop);


      ui->popup_stacked_widget->setCurrentIndex(1);



    }
  else{
      qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
      QString title="Failed !";
      QString description="The product haven't been added to this staging \n                    table successfully";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_2->addWidget(pop);


      ui->popup_stacked_widget->setCurrentIndex(1);
    }

  dataSet.insert(dataSet.begin(), office);
  std::list<Office*>::iterator it;

  for (it = dataSet.begin(); it != dataSet.end(); ++it){
      Card *card = new Card();
      card->setOfficeID((*it)->getIdOffice());
      card->setOfficePrice((*it)->getPrice());
      card->setOfficeDescription((*it)->getDescription());
      card->setOfficeImage((*it)->getImage());
      card->setNameOffice((*it)->getNameOffice());

      connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
       ui->CardsLayout->addWidget(card);
  }

}

void MainWindow::on_GoBackButton_clicked()
{
    ui->body->setCurrentIndex(0);
}



void MainWindow::on_omg_clicked()
{

   ui->body->setCurrentIndex(2);
}


void MainWindow::on_SingUpBtn1_clicked()
{
  ui->loginForm->setCurrentIndex(0);


  QString username=ui->Username_SingUp->text();
  QString password=ui->password_SingUp->text();
  int phone_number=ui->number_SingUp->text().toInt();
  QString email=ui->email_SingUp->text();

  bool verfy=EmailCheck(email);
  if(verfy){
  User stock(username,password,email,phone_number);
  bool check=stock.Add_new();
  if(check){
      ui->pop_up_Sign_Up_STK->setVisible(true);
      qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      ui->popup_stacked_widget_2->setCurrentIndex(1);
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/success_icon.png";
      QString title="Success !";
      QString description="The User Have Been Added To This Staging \n                    Table Successfully";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_3->addWidget(pop);




    }
  else{

      ui->pop_up_Sign_Up_STK->setVisible(true);
      qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      ui->popup_stacked_widget_2->setCurrentIndex(1);
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
      QString title="  Failed !";
      QString description="The UserName Or Password Are Not Correct  !!";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_3->addWidget(pop);



    }
    }
  else{

      ui->pop_up_Sign_Up_STK->setVisible(true);
      qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      ui->popup_stacked_widget_2->setCurrentIndex(1);
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
      QString title="  Failed !";
      QString description="The UserName Or Password Are Not Correct  !!";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_3->addWidget(pop);


    }




}
void MainWindow::on_edit_office_button_more_clicked()
{
   ui->add_office_widget->setVisible(true);
   ui->popup_stacked_widget->setCurrentIndex(2);
}
void MainWindow::on_edit_office_button_clicked()
{

  //ui->edit_office_widget->setVisible(false);

  QString id_office=ui->id_wtf->text();
  QString image="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/office.png";
  QString name=ui->office_Name_line_edit->text();
  QString space=ui->space_line_edit->text();
  QString position=ui->position_line_edit->text();
  QString price=ui->Price_line_edit->text();
  QString description=ui->description_line_edit->text();
  QString status;
   QString date;
   QString type;
   qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
   Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);

   Office stock(id_office,image,description,price,name,position,space,status,type,date);

  bool check=stock.edit_office_database();
  if(check){
      qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/success_icon.png";
      QString title="Success !";
      QString description="The Product Have Been Edited In This Staging \n                    Table Successfully";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_2->addWidget(pop);


      ui->popup_stacked_widget->setCurrentIndex(1);
    }
  else{
      qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
      QString title="Failed !";
      QString description="The Product Haven't Been Edited In This Staging \n                    Table Successfully";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_2->addWidget(pop);


      ui->popup_stacked_widget->setCurrentIndex(1);
    }

}
void MainWindow::on_delete_office_button_more_clicked(){

  ui->add_office_widget->setVisible(true);


  QString id_office=ui->id_wtf->text();
  QString image;
  QString name;
  QString space;
  QString position;
  QString price;
  QString description;
  QString status;
   QString date;
   QString type;
  qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
   Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);

   Office stock(id_office,image,description,price,name,position,space,status,type,date);
  bool check=stock.deleteOfficeById();
  if(check){
      qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/success_icon.png";
      QString title="Success !";
      QString description="The Product Have Been Deleted In This Staging \n                    Table Successfully";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_2->addWidget(pop);
      ui->popup_stacked_widget->setCurrentIndex(1);

      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


      Office * office;
      dataSet = office->getAllOffices();
      std::list<Office*>::iterator it1;


      std::list<Office*>::iterator it;
      for (it = dataSet.begin(); it != dataSet.end(); ++it){
          Card *card = new Card();
          card->setOfficeID((*it)->getIdOffice());
          card->setNameOffice((*it)->getNameOffice());
          card->setOfficePrice((*it)->getPrice());
          card->setOfficeDescription((*it)->getDescription());
          card->setOfficeImage((*it)->getImage());
          connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
           ui->CardsLayout->addWidget(card);
      }
    }
  else{
      qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
      QString title="Failed !";
      QString description="The Product Haven't Been Deleted In This Staging \n                    Table Successfully";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_2->addWidget(pop);


      ui->popup_stacked_widget->setCurrentIndex(1);
    }

}
void MainWindow::on_search_button_office_clicked()
{
  QString id_office=ui->id_wtf->text();
  QString image;
  QString name=ui->search_line_office->text();
  QString space;//=ui->space_line_3->text();
  QString position;//=ui->position_line_3->text();
  QString price;//ui->Price_line_3->text();
  QString description;//ui->description_line_3->text();
  QString status;
   QString date;
   QString type;

   Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);

   Office stock(id_office,image,description,price,name,position,space,status,type,date);
  if(name!=""){   //if the search is not  empty!! we are going to display the recomended one else we are going to display all the offices
  bool check=stock.searchOfficeByName(name);
  if(check){
      QMessageBox::information(nullptr, QObject::tr("database is  open"),
                                       QObject::tr("Success.\n""Click Cancel to exit."), QMessageBox::Ok);
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


      Office * office;
      dataSet = office->getSearchOffices(name);
      std::list<Office*>::iterator it1;


      std::list<Office*>::iterator it;
      for (it = dataSet.begin(); it != dataSet.end(); ++it){
          Card *card = new Card();
          card->setOfficeID((*it)->getIdOffice());
          card->setNameOffice((*it)->getNameOffice());
          card->setOfficePrice((*it)->getPrice());
          card->setOfficeDescription((*it)->getDescription());
          card->setOfficeImage((*it)->getImage());
          connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
           ui->CardsLayout->addWidget(card);
    }
    }
  else{
      QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                       QObject::tr("Failed.\n""Click Cancel to exit."), QMessageBox::Cancel);

    }
    }
  else
    {
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


      Office * office;
      dataSet = office->getAllOffices();
      std::list<Office*>::iterator it1;


      std::list<Office*>::iterator it;
      for (it = dataSet.begin(); it != dataSet.end(); ++it){
          Card *card = new Card();
          card->setOfficeID((*it)->getIdOffice());
          card->setNameOffice((*it)->getNameOffice());
          card->setOfficePrice((*it)->getPrice());
          card->setOfficeDescription((*it)->getDescription());
          card->setOfficeImage((*it)->getImage());
          connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
           ui->CardsLayout->addWidget(card);
      }
    }

}

void MainWindow:: on_search_line_office_textChanged(const QString &arg1){
  QString id_office=ui->id_wtf->text();
  QString image;
  QString name=ui->search_line_office->text();
  QString space;
  QString position;
  QString price;
  QString description;
  QString status;
  QString date;
  QString type;
   Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);

   Office stock(id_office,image,description,price,name,position,space,status,type,date);
  if(name!=""){   //if the search is not  empty!! we are going to display the recomended one else we are going to display all the offices
  bool check=stock.searchOfficeByName(name);
  if(check)
    {

      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
      Office * office;
      dataSet = office->getSearchOffices(arg1);
      std::list<Office*>::iterator it1;
      std::list<Office*>::iterator it;
      for (it = dataSet.begin(); it != dataSet.end(); ++it)
        {
          Card *card = new Card();
          card->setOfficeID((*it)->getIdOffice());
          card->setNameOffice((*it)->getNameOffice());
          card->setOfficePrice((*it)->getPrice());
          card->setOfficeDescription((*it)->getDescription());
          card->setOfficeImage((*it)->getImage());
          connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
           ui->CardsLayout->addWidget(card);
        }
    }
    }
  else
    {
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


      Office * office;
      dataSet = office->getAllOffices();
      std::list<Office*>::iterator it1;


      std::list<Office*>::iterator it;
      for (it = dataSet.begin(); it != dataSet.end(); ++it){
          Card *card = new Card();
          card->setOfficeID((*it)->getIdOffice());
          card->setNameOffice((*it)->getNameOffice());
          card->setOfficePrice((*it)->getPrice());
          card->setOfficeDescription((*it)->getDescription());
          card->setOfficeImage((*it)->getImage());
          connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
           ui->CardsLayout->addWidget(card);
      }
    }
}
void MainWindow:: on_GoBack_area_add_office_clicked(){
  ui->add_office_widget->setVisible(false);
  ui->popup_stacked_widget->setCurrentIndex(0);
  ui->body->setCurrentIndex(0);
}

void MainWindow ::on_GoBack_area_Sign_Up_clicked(){
  ui->pop_up_Sign_Up_STK->setVisible(false);
}
void MainWindow:: on_print_pdf_office_clicked(){
  QString id=ui->id_wtf->text();
  QString name=ui->title_office->text();
  QString description=ui->description_text_office->text();
  QString space=ui->space_description_office->text();
  QString position=ui->position_description_office->text();
  QString price=ui->price_office->text();
  QString BankOffer=ui->bankOffer_description_office->text();
  QFile file("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/"+name+" "+id+""".pdf");
  QPdfWriter pdf("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/"+name+".pdf");
  QPainter painter(&pdf);

  painter.setPen(Qt::black);
  painter.drawText(4000,400,"receipt N°:  "+id+"" );
  painter.drawText(3500,1300,"Office Name: "+name+"" );
  painter.drawText(3500,1700,"Description :"+description+"  " );
  painter.drawText(3500,2100,"Space :  "+space+"" );
  painter.drawText(3500,2500,"Position: :  "+position+"" );
  painter.drawText(3500,2900,"BankOffer : "+BankOffer+"" );
  painter.drawText(3500,3300,"The sum is :  "+price+"" );
  painter.end();
}


void MainWindow::on_lowest_button_clicked()
{
  ui->check_cercle_heighest->setVisible(false);
  ui->check_cercle_lowest->setVisible(true);
  price_office = " ASC ";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
  std::list<Office*>::iterator it1;


  std::list<Office*>::iterator it;
  for (it = dataSet.begin(); it != dataSet.end(); ++it)
   {
      Card *card = new Card();
      card->setOfficeID((*it)->getIdOffice());
      card->setNameOffice((*it)->getNameOffice());
      card->setOfficePrice((*it)->getPrice());
      card->setOfficeDescription((*it)->getDescription());
      card->setOfficeImage((*it)->getImage());
      connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
       ui->CardsLayout->addWidget(card);
   }
}

void MainWindow:: on_heighest_button_clicked()
{
  ui->check_cercle_heighest->setVisible(true);
  ui->check_cercle_lowest->setVisible(false);
  price_office = " DESC ";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
   std::list<Office*>::iterator it1;


  std::list<Office*>::iterator it;
  for (it = dataSet.begin(); it != dataSet.end(); ++it)
   {
      Card *card = new Card();
      card->setOfficeID((*it)->getIdOffice());
      card->setNameOffice((*it)->getNameOffice());
      card->setOfficePrice((*it)->getPrice());
      card->setOfficeDescription((*it)->getDescription());
      card->setOfficeImage((*it)->getImage());
      connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
       ui->CardsLayout->addWidget(card);
   }
}
void MainWindow ::on_open_area_button_clicked()
{ ui->check_cercle_openArea->setVisible(true);
  ui->check_cercle_office->setVisible(false);
  type_office = " open area ";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);

  std::list<Office*>::iterator it1;


  std::list<Office*>::iterator it;
  for (it = dataSet.begin(); it != dataSet.end(); ++it)
   {
      Card *card = new Card();
      card->setOfficeID((*it)->getIdOffice());
      card->setNameOffice((*it)->getNameOffice());
      card->setOfficePrice((*it)->getPrice());
      card->setOfficeDescription((*it)->getDescription());
      card->setOfficeImage((*it)->getImage());
      connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
       ui->CardsLayout->addWidget(card);
   }

}
void MainWindow::on_office_button_clicked()
{
  ui->check_cercle_openArea->setVisible(false);
  ui->check_cercle_office->setVisible(true);
  type_office = "office";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    std::list<Office*>::iterator it1;


    std::list<Office*>::iterator it;
    for (it = dataSet.begin(); it != dataSet.end(); ++it)
     {
        Card *card = new Card();
        card->setOfficeID((*it)->getIdOffice());
        card->setNameOffice((*it)->getNameOffice());
        card->setOfficePrice((*it)->getPrice());
        card->setOfficeDescription((*it)->getDescription());
        card->setOfficeImage((*it)->getImage());
        connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
         ui->CardsLayout->addWidget(card);
     }

}
void MainWindow:: on_available_button_clicked()
{
  ui->check_cercle_available->setVisible(true);
  ui->check_cercle_not_available->setVisible(false);
  ui->check_cercle_All->setVisible(false);
  availibity_office = "available";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    std::list<Office*>::iterator it1;


    std::list<Office*>::iterator it;
    for (it = dataSet.begin(); it != dataSet.end(); ++it)
     {
        Card *card = new Card();
        card->setOfficeID((*it)->getIdOffice());
        card->setNameOffice((*it)->getNameOffice());
        card->setOfficePrice((*it)->getPrice());
        card->setOfficeDescription((*it)->getDescription());
        card->setOfficeImage((*it)->getImage());
        connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
         ui->CardsLayout->addWidget(card);
     }
}

void MainWindow:: on_not_available_button_clicked()
{

  ui->check_cercle_available->setVisible(false);
  ui->check_cercle_not_available->setVisible(true);
  ui->check_cercle_All->setVisible(false);

  availibity_office = " not available ";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    std::list<Office*>::iterator it1;


    std::list<Office*>::iterator it;
    for (it = dataSet.begin(); it != dataSet.end(); ++it)
     {
        Card *card = new Card();
        card->setOfficeID((*it)->getIdOffice());
        card->setNameOffice((*it)->getNameOffice());
        card->setOfficePrice((*it)->getPrice());
        card->setOfficeDescription((*it)->getDescription());
        card->setOfficeImage((*it)->getImage());
        connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
         ui->CardsLayout->addWidget(card);
     }
}
void MainWindow:: on_asc_button_clicked()
{
  ui->check_cercle_ASC->setVisible(true);
  ui->check_cercle_DESC->setVisible(false);


  space_office = " ASC ";
  dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    std::list<Office*>::iterator it1;


    std::list<Office*>::iterator it;
    for (it = dataSet.begin(); it != dataSet.end(); ++it)
     {
        Card *card = new Card();
        card->setOfficeID((*it)->getIdOffice());
        card->setNameOffice((*it)->getNameOffice());
        card->setOfficePrice((*it)->getPrice());
        card->setOfficeDescription((*it)->getDescription());
        card->setOfficeImage((*it)->getImage());
        connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
         ui->CardsLayout->addWidget(card);
     }
}

void MainWindow:: on_desc_button_clicked()
{
  ui->check_cercle_ASC->setVisible(false);
  ui->check_cercle_DESC->setVisible(true);
  space_office = " DESC ";

  dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));


    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    //dataSet = office->getOfficesBySpaceDESC();
    std::list<Office*>::iterator it1;


    std::list<Office*>::iterator it;
    for (it = dataSet.begin(); it != dataSet.end(); ++it)
     {
        Card *card = new Card();
        card->setOfficeID((*it)->getIdOffice());
        card->setNameOffice((*it)->getNameOffice());
        card->setOfficePrice((*it)->getPrice());
        card->setOfficeDescription((*it)->getDescription());
        card->setOfficeImage((*it)->getImage());
        connect(card,SIGNAL(sendData(QString)),this,SLOT(recieveData(QString)));
         ui->CardsLayout->addWidget(card);
     }
}
bool MainWindow:: EmailCheck (QString email)
{
  if((email.contains('@'))&& (email.toStdString().length()>5)&& (email.contains('@'))){
      return true ;
    }
  else
    return false;
}
