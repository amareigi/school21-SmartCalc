#include "mainwindow.h"

#include "ui_mainwindow.h"

extern "C" {
#include "../s21_smartcalc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tabWidget->setTabText(0, "Calculator v1.0");
  ui->tabWidget->setTabText(1, "Credit and deposit");

  ui->result_show->setReadOnly(true);
  ui->mouth_pay->setReadOnly(true);
  ui->full_sum->setReadOnly(true);
  ui->pereplata->setReadOnly(true);

  QString style =
      "QDoubleSpinBox {"
      "background-color: rgb(10, 186, 181);"  // фон
      "border-radius: 5px;"                   // углов
      "color: rgb(0, 0, 0);"                  // текст
      "font-size: 20px;"                      // шрифта
      "}";

  ui->x_show->setStyleSheet(style);
  ui->sum_cred->setStyleSheet(style);
  ui->time->setStyleSheet(style);
  ui->pecent->setStyleSheet(style);

  connect(ui->frog, SIGNAL(clicked()), this, SLOT(touch_me()));

  connect(ui->p_0, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_1, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_2, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_3, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_4, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_5, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_6, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_7, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_8, SIGNAL(clicked()), this, SLOT(digits_press()));
  connect(ui->p_9, SIGNAL(clicked()), this, SLOT(digits_press()));

  connect(ui->arcos, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->arcsin, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->artan, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(trig_press()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(trig_press()));

  connect(ui->div, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->mul, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->stepen, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->sum, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->scob_l, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->scob_w, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->perem, SIGNAL(clicked()), this, SLOT(bin_press()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(bin_press()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_press() {
  QPushButton *digits = (QPushButton *)sender();

  ui->result_show->setText(ui->result_show->text() + digits->text());
}

void MainWindow::bin_press() {
  QPushButton *bin = (QPushButton *)sender();

  ui->result_show->setText(ui->result_show->text() + bin->text());
}

void MainWindow::trig_press() {
  QPushButton *trig = (QPushButton *)sender();

  ui->result_show->setText(ui->result_show->text() + trig->text() + "(");
}
// тут основное
void MainWindow::on_ent_clicked() {
  double x = 0;
  x = ui->x_show->text().toDouble();
  std::string str = ui->result_show->text().toStdString();
  char *stroka = (char *)str.c_str();
  if (check_input(stroka) == 0) {
    double res = parser(stroka, x);
    QString result = QString::number(res);
    ui->result_show->setText(result);
  } else
    ui->result_show->setText("ERROR");
}

void MainWindow::on_CLEAR_clicked() { ui->result_show->setText(""); }

void MainWindow::on_dote_clicked() {
  if (ui->result_show->text().isEmpty() ||
      ui->result_show->text().back() != '.')
    ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::on_graph_clicked() {
  std::string str = ui->result_show->text().toStdString();
  char *gr_str = (char *)str.c_str();
  if (check_input(gr_str) == 0) {
    double Ymax = ui->y_max->text().toDouble(),
           Ymin = ui->y_min->text().toDouble();
    double min = ui->x_min->text().toDouble();
    double max = ui->x_max->text().toDouble();
    if (Ymax != 0 && Ymin != 0 && max != 0 && min != 0 && max > min &&
        Ymax > Ymin) {
      double yy = 0;
      int N = 10000;
      if (max <= 5 || min >= -5) N = 100;
      double h = (max - min) / N;

      QVector<double> x(N), y(N);
      int i = 0;
      for (double X = min; X <= max;) {
        x[i] = X;
        yy = parser(gr_str, X);
        yy > Ymax || yy < Ymin ? y[i] = qQNaN() : y[i] = yy;
        X += h;
        i++;
      }
      ui->widget->clearGraphs();
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      ui->widget->xAxis->setLabel("x");
      ui->widget->yAxis->setLabel("y");
      ui->widget->xAxis->setRange(min, max);
      for (int i = 1; i < N; i++) {
        if (y[i] < Ymin) Ymin = y[i];
        if (y[i] > Ymax) Ymax = y[i];
      }
      ui->widget->yAxis->setRange(Ymin, Ymax);
      ui->widget->replot();
    } else {
      ui->result_show->setText("INVALID");
    }
  } else
    ui->result_show->setText("ERROR");
}

void MainWindow::on_credit_res_clicked() {
  if (!(ui->sum_cred->text().contains("-")) &&
      !(ui->time->text().contains("-")) &&
      !(ui->pecent->text().contains("-"))) {
    if (ui->ann->isChecked()) {
      Creditpay cred =
          Credit(ui->sum_cred->text().toDouble(), ui->time->text().toDouble(),
                 ui->pecent->text().toDouble());
      ui->mouth_pay->setText(QString::number(cred.payment, 'f', 2));
      ui->full_sum->setText(QString::number(cred.total, 'f', 2));
      ui->pereplata->setText(QString::number(cred.overpayment, 'f', 2));
    } else if (ui->diff->isChecked()) {
      Creditpay cred =
          Credit2(ui->sum_cred->text().toDouble(), ui->time->text().toDouble(),
                  ui->pecent->text().toDouble());
      ui->mouth_pay->setText(QString::number(cred.payment, 'f', 2) + "->" +
                             QString::number(cred.last_pay, 'f', 2));
      ui->full_sum->setText(QString::number(cred.total, 'f', 2));
      ui->pereplata->setText(QString::number(cred.overpayment, 'f', 2));
    }
  }
}

void MainWindow::touch_me() {
  // QDesktopServices::openUrl(
  //     QUrl("https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley"));
}
