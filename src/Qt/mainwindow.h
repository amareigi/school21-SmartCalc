#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QMainWindow>
#include <QUrl>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_ent_clicked();
  void digits_press();
  void on_CLEAR_clicked();
  void bin_press();
  void trig_press();
  void touch_me();

  void on_dote_clicked();

  void on_credit_res_clicked();

  void on_graph_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
