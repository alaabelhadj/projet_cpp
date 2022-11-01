#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "popup.h"
#include "office.h"
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <iostream>
#include <regex>
#include <string>
#include <cctype>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  std::list<Office*> dataSet;
  QString type_office="office";
  QString price_office=" ASC ";
  QString space_office=" ASC ";
  QString availibity_office="available";
  bool  EmailCheck (QString email);

private slots:

  void on_Username_textChanged(const QString &arg1);

  void on_Username_editingFinished();

  void on_password_textChanged(const QString &arg1);

  void on_password_editingFinished();

  void on_visibilityBtn_clicked();

  void on_Username_SingUp_textChanged(const QString &arg1);

  void on_Username_SingUp_editingFinished();

  void on_SingUpBtn_clicked();

  void on_password_SingUp_textChanged(const QString &arg1);

  void on_password_SingUp_editingFinished();

  void on_visibilityBtn_SingUp_clicked();

  void on_email_SingUp_textChanged(const QString &arg1);

  void on_email_SingUp_editingFinished();

  void on_number_SingUp_textChanged(const QString &arg1);

  void on_number_SingUp_editingFinished();

  void on_SingUpBtn_3_clicked();

  void on_Display_offices_Reservation_btn_clicked();

  void on_LoginButton_clicked();

  void on_Reservation_Btn_clicked();

  void on_Office_Btn_clicked();

  void on_Statistics_offices_Btn_clicked();

  void on_Display_offices_Btn_clicked();

  void on_exit_add_office_clicked();

  void on_pushButton_clicked();

  void on_exit_button_clicked();

  void on_office_Name_line_textChanged(const QString &arg1);

  void on_office_Name_line_editingFinished();

  void on_space_line_textChanged(const QString &arg1);

  void on_space_line_editingFinished();

  void on_position_line_textChanged(const QString &arg1);

  void on_position_line_editingFinished();

  void on_Price_line_textChanged(const QString &arg1);

  void on_Price_line_editingFinished();

  void on_description_line_textChanged(const QString &arg1);

  void on_description_line_editingFinished();

  void on_add_office_btn_clicked();

  void on_exit_add_popup_clicked();

  void on_GoBack_area_Sign_Up_clicked();

  void on_add_office_button_clicked();

  void recieveData(QString);

  void on_GoBackButton_clicked();

  void on_GoBack_area_add_office_clicked();

   void on_omg_clicked();

   void on_SingUpBtn1_clicked();

   void on_edit_office_button_more_clicked();

   void on_edit_office_button_clicked();

   void on_delete_office_button_more_clicked();

   void on_search_button_office_clicked();

   void on_search_line_office_textChanged(const QString &arg1);

   void on_print_pdf_office_clicked();

   void on_lowest_button_clicked();

   void on_heighest_button_clicked();

   void on_open_area_button_clicked();

   void on_office_button_clicked();

   void on_available_button_clicked();

   void on_not_available_button_clicked();

   void on_asc_button_clicked();

   void on_desc_button_clicked();




public:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
