#include "s21_smartcalc.h"

Creditpay Credit(double sum, int time, double perc) {  //Аннуитетный платеж
  double monthly_percent = perc / 12 / 100;
  Creditpay cred = {0};
  cred.payment = sum * ((monthly_percent * pow(1 + monthly_percent, time)) /
                        (pow(1 + monthly_percent, time) - 1));
  cred.total = cred.payment * time;
  cred.overpayment = cred.total - sum;
  return cred;
}

Creditpay Credit2(double sum, int time,
                  double perc) {  // Дифференцированный платеж
  Creditpay cred = {0};
  double monthly_percent = perc / 12 / 100;

  for (int i = 1; i <= time; i++) {
    cred.overpayment =
        (sum / time) + ((sum - (i - 1) * (sum / time)) * monthly_percent);
    cred.total += cred.overpayment;
    if (i == 1)
      cred.payment = cred.overpayment;
    else if (i == time)
      cred.last_pay = cred.overpayment;
  }
  cred.overpayment = cred.total - sum;
  return cred;
}