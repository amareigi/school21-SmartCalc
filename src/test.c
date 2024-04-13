#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "s21_smartcalc.h"

START_TEST(test1) {
  char* str = "8-7";
  double a = 1.0;
  double b = parser(str, 0.0);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(test2) {
  char* str = "-7";
  double a = -7.0;
  double b = parser(str, 0.0);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(test6) {
  char* str = "1*(1*(1*(1*(-1))))";
  int a = -1;
  int b = parser(str, 0.0);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_test_0) {
  char* str = "5+5";
  double a = 10.0;
  double b = parser(str, 0.0);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(s21_test_1) {
  double a = 162.0;
  char* str = "4*5*2*2*2+2";
  double b = parser(str, 0.0);
  ck_assert_double_eq(b, a);
}
END_TEST

START_TEST(s21_test_2) {
  double a = 20;
  char* str = "150/10+5*2/2";
  double b = parser(str, 0.0);
  ck_assert_double_eq(b, a);
}
END_TEST

START_TEST(s21_test_3) {
  double a = 9.0;
  char* str = "5+5-2*3/6";
  double b = parser(str, 0.0);
  ck_assert_double_eq(b, a);
}
END_TEST

START_TEST(s21_test_4) {
  char* str = "123+0.456";
  double a = parser(str, 0.0);
  double b = 123.456;
  ck_assert_double_eq(a, b);
}

START_TEST(s21_test_5) {
  char* str = "-(-1)";
  double a = parser(str, 0.0);
  double b = 1;
  ck_assert_double_eq(a, b);
}

START_TEST(s21_test_6) {
  char* str = "cos(10mod2.2)";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, cos(fmod(10, 2.2)));
}

START_TEST(s21_test_7) {
  char* str = "sqrt(ln(10))";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, sqrt(log(10)));
}

START_TEST(s21_test_8) {
  char* str = "atan(10)+sin(10)";
  double a = parser(str, 0.0);
  ck_assert_double_eq_tol(a, atan(10) + sin(10), 1e-7);
}

START_TEST(s21_test_9) {
  char* str = "asin(1)";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, asin(1));
}

START_TEST(s21_test_10) {
  char* str = "10-20*(-10)";
  double a = parser(str, 0.0);
  double b = 210.0;
  ck_assert_double_eq(a, b);
}

START_TEST(s21_test_11) {
  char* str = "sin(8)";
  double a = sin(8);
  double b = parser(str, 0.0);
  ck_assert_int_eq(a, b);
}

END_TEST
START_TEST(s21_test_12) {
  char* str = "2+(5*5*5+5+2*2)/(2)";
  double a = parser(str, 0.0);
  double b = 69.0;
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(s21_test_13) {
  char* str = "5mod2";
  double a = fmod(5, 2);
  double b = parser(str, 0.0);
  ck_assert_int_eq(a, b);
}

START_TEST(s21_test_14) {
  double b = 11.958851;
  char* str = "5+(3+sin(8/2-3.5))*2";
  double a = parser(str, 0.0);
  ck_assert_double_eq_tol(a, b, 1e-7);
}
END_TEST

START_TEST(s21_test_15) {
  char* str = "24*4-3*2";
  double b = 90.0;
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(s21_test_16) {
  double b = 4.0;
  char* str = "2-(-2)";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(s21_test_17) {
  char* str = "-sin(9)";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, -sin(9));
}
END_TEST

START_TEST(s21_test_18) {
  char* str = "sin(9)-(-2)";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, sin(9) - (-2));
}
END_TEST

START_TEST(s21_test_19) {
  char* str = "-cos(9)";
  double a = parser(str, 0.0);
  ck_assert_double_eq(a, -cos(9));
}
END_TEST

START_TEST(s21_test_20) {
  double b = parser("(-2)+2", 0.0);
  ck_assert_double_eq(b, 0.0);
}
END_TEST

START_TEST(s21_test_21) {
  double b = parser("(-2.2)-2.2", 0.0);
  ck_assert_double_eq(b, -4.4);
}
END_TEST

START_TEST(s21_test_22) {
  double b = parser("(-2.2)*(2.2)", 0.0);
  ck_assert_double_eq(b, (-2.2) * (2.2));
}
END_TEST

START_TEST(s21_test_23) {
  double b = parser("(-2.2)/2.2", 0.0);
  ck_assert_float_eq(b, -1);
}
END_TEST

START_TEST(s21_test_24) {
  double b = parser("(2.2)^(-2.2)", 0.0);
  ck_assert_double_eq_tol(b, 0.17647, 0.17647);
}
END_TEST

START_TEST(s21_test_25) {
  double b = parser("sin(2)", 0.0);
  ck_assert_double_eq(b, sin(2));
}
END_TEST

START_TEST(s21_test_26) {
  long double b = parser("cos(2)", 0.0);
  ck_assert_double_eq_tol(b, cos(2), 1e-7);
}
END_TEST

START_TEST(s21_test_27) {
  long double b = parser("tan(2)", 0.0);
  ck_assert_ldouble_eq(b, tan(2));
}
END_TEST

START_TEST(s21_test_28) {
  long double b = parser("asin(1)", 0.0);
  ck_assert_ldouble_eq(b, asin(1));
}
END_TEST

START_TEST(s21_test_29) {
  long double b = parser("acos(1)", 0.0);
  ck_assert_ldouble_eq(b, acos(1));
}
END_TEST

START_TEST(s21_test_30) {
  long double b = parser("atan(1)", 0.0);
  ck_assert_ldouble_eq(b, atan(1));
}
END_TEST

START_TEST(s21_test_31) {
  long double b = parser("log(1)", 0.0);
  ck_assert_ldouble_eq(b, log(1));
}
END_TEST

START_TEST(s21_test_32) {
  long double b = parser("log(1)", 0.0);
  ck_assert_ldouble_eq(b, log10(1));
}
END_TEST

START_TEST(s21_test_33) {
  long double b = parser("sqrt(1)", 0.0);
  ck_assert_ldouble_eq(b, sqrt(1));
}
END_TEST

START_TEST(s21_test_34) {
  long double b = parser("4mod8", 0.0);
  ck_assert_ldouble_eq(b, 4);
}
END_TEST

START_TEST(s21_test_35) {
  double b = 4.0;
  char* str = "x-(-x)";
  double a = parser(str, 2.0);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(s21_test_36) {
  char* str = "-sin(x)";
  double a = parser(str, 9.0);
  ck_assert_double_eq(a, -sin(9));
}
END_TEST
START_TEST(s21_test_37) {
  char* str = "sin(9)-(-x)";
  double a = parser(str, 2.0);
  ck_assert_double_eq(a, sin(9) - (-2));
}
END_TEST
START_TEST(s21_test_38) {
  char* str = "-cos(x)";
  double a = parser(str, 9.0);
  ck_assert_double_eq(a, -cos(9));
}
END_TEST
START_TEST(s21_test_39) {
  double b = parser("(-x)+x", 2.0);
  ck_assert_double_eq(b, 0.0);
}
END_TEST

START_TEST(s21_test_40) {
  double b = parser("(-x)-x", 2.2);
  ck_assert_double_eq(b, -4.4);
}
END_TEST

START_TEST(s21_test_41) {
  double b = parser("(-x) * (x)", 2.2);
  double a = (-2.2) * (2.2);
  ck_assert_double_eq(b, a);
}
END_TEST

START_TEST(s21_test_42) {
  double b = parser("(-x)/x", 2.2);
  ck_assert_float_eq(b, -1);
}
END_TEST

START_TEST(s21_test_43) {
  double b = parser("(x)^(-x)", 2.2);
  ck_assert_double_eq_tol(b, 0.17647, 0.17647);
}
END_TEST

START_TEST(s21_test_44) {
  double b = parser("sin(x)", 2.0);
  ck_assert_double_eq(b, sin(2));
}
END_TEST

START_TEST(s21_test_45) {
  long double b = parser("cos(x)", 0.0);
  ck_assert_double_eq_tol(b, cos(0), 1e-7);
}
END_TEST

START_TEST(s21_test_46) {
  long double b = parser("tan(x)", 2.0);
  ck_assert_ldouble_eq(b, tan(2));
}
END_TEST

START_TEST(s21_test_47) {
  long double b = parser("asin(x)", 1.0);
  ck_assert_ldouble_eq(b, asin(1));
}
END_TEST

START_TEST(s21_test_48) {
  long double b = parser("acos(x)", 1.0);
  ck_assert_ldouble_eq(b, acos(1));
}
END_TEST

START_TEST(s21_test_49) {
  long double b = parser("atan(x)", 1.0);
  ck_assert_ldouble_eq(b, atan(1));
}
END_TEST

START_TEST(s21_test_50) {
  long double b = parser("log(x)", 1.0);
  ck_assert_ldouble_eq(b, log(1));
}
END_TEST

START_TEST(s21_test_51) {
  long double b = parser("log(x)", 1.0);
  ck_assert_ldouble_eq(b, log10(1));
}
END_TEST

START_TEST(s21_test_52) {
  long double b = parser("sqrt(x)", 1.0);
  ck_assert_ldouble_eq(b, sqrt(1));
}
END_TEST

START_TEST(s21_test_53) {
  long double b = parser("4modx", 8.0);
  ck_assert_ldouble_eq(b, 4);
}
END_TEST

START_TEST(s21_test_54) {
  Creditpay a = Credit(500000, 5, 10);
  ck_assert_double_eq_tol(a.overpayment, 12569.15, 1e-2);
  ck_assert_double_eq_tol(a.payment, 102513.83, 1e-2);
  ck_assert_double_eq_tol(a.total, 512569.15, 1e-2);
}
END_TEST

START_TEST(s21_test_55) {
  Creditpay a = Credit2(500000, 5, 10);
  ck_assert_double_eq(a.overpayment, 12500);
  ck_assert_double_eq_tol(a.payment, 104166.67, 1e-2);
  ck_assert_double_eq_tol(a.total, 512500.00, 1e-2);
}
END_TEST

START_TEST(s21_test_56) {
  char* str = "1*(1*(1*(1*(-1))))";
  int a = check_input(str);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_test_57) {
  char* str = "1*(1*(1*(1*(-))";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_58) {
  char* str = "-cos(mod*(1*(1*(-))";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_59) {
  char* str = "-cos(4)*11...22";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_60) {
  char* str = "-cos(4)*112.*xx";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_61) {
  char* str = "*tan+(4)*11.2.*()-lg+(/sil";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_62) {
  char* str = "4--4";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_63) {
  char* str = "mc+-4";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_64) {
  char* str = "4mod+-4";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_test_65) {
  char* str = "4cod+-4";
  int a = check_input(str);
  ck_assert_int_eq(a, 1);
}
END_TEST

int main() {
  Suite* suite = suite_create("UNITS");
  TCase* tcase = tcase_create("TESTS");
  SRunner* srunner = srunner_create(suite);
  int val = 0;

  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, test1);
  tcase_add_test(tcase, test2);
  tcase_add_test(tcase, test6);
  tcase_add_test(tcase, s21_test_0);
  tcase_add_test(tcase, s21_test_1);
  tcase_add_test(tcase, s21_test_2);
  tcase_add_test(tcase, s21_test_3);
  tcase_add_test(tcase, s21_test_4);
  tcase_add_test(tcase, s21_test_5);
  tcase_add_test(tcase, s21_test_6);
  tcase_add_test(tcase, s21_test_7);
  tcase_add_test(tcase, s21_test_8);
  tcase_add_test(tcase, s21_test_9);
  tcase_add_test(tcase, s21_test_10);
  tcase_add_test(tcase, s21_test_11);
  tcase_add_test(tcase, s21_test_12);
  tcase_add_test(tcase, s21_test_13);
  tcase_add_test(tcase, s21_test_14);
  tcase_add_test(tcase, s21_test_15);
  tcase_add_test(tcase, s21_test_16);
  tcase_add_test(tcase, s21_test_17);
  tcase_add_test(tcase, s21_test_18);
  tcase_add_test(tcase, s21_test_19);
  tcase_add_test(tcase, s21_test_20);
  tcase_add_test(tcase, s21_test_21);
  tcase_add_test(tcase, s21_test_22);
  tcase_add_test(tcase, s21_test_23);
  tcase_add_test(tcase, s21_test_24);
  tcase_add_test(tcase, s21_test_25);
  tcase_add_test(tcase, s21_test_26);
  tcase_add_test(tcase, s21_test_27);
  tcase_add_test(tcase, s21_test_28);
  tcase_add_test(tcase, s21_test_29);
  tcase_add_test(tcase, s21_test_30);
  tcase_add_test(tcase, s21_test_31);
  tcase_add_test(tcase, s21_test_32);
  tcase_add_test(tcase, s21_test_33);
  tcase_add_test(tcase, s21_test_34);
  tcase_add_test(tcase, s21_test_35);
  tcase_add_test(tcase, s21_test_36);
  tcase_add_test(tcase, s21_test_37);
  tcase_add_test(tcase, s21_test_38);
  tcase_add_test(tcase, s21_test_39);
  tcase_add_test(tcase, s21_test_40);
  tcase_add_test(tcase, s21_test_41);
  tcase_add_test(tcase, s21_test_42);
  tcase_add_test(tcase, s21_test_43);
  tcase_add_test(tcase, s21_test_44);
  tcase_add_test(tcase, s21_test_45);
  tcase_add_test(tcase, s21_test_46);
  tcase_add_test(tcase, s21_test_47);
  tcase_add_test(tcase, s21_test_48);
  tcase_add_test(tcase, s21_test_49);
  tcase_add_test(tcase, s21_test_50);
  tcase_add_test(tcase, s21_test_51);
  tcase_add_test(tcase, s21_test_52);
  tcase_add_test(tcase, s21_test_53);
  tcase_add_test(tcase, s21_test_54);
  tcase_add_test(tcase, s21_test_55);
  tcase_add_test(tcase, s21_test_56);
  tcase_add_test(tcase, s21_test_57);
  tcase_add_test(tcase, s21_test_58);
  tcase_add_test(tcase, s21_test_59);
  tcase_add_test(tcase, s21_test_60);
  tcase_add_test(tcase, s21_test_61);
  tcase_add_test(tcase, s21_test_62);
  tcase_add_test(tcase, s21_test_63);
  tcase_add_test(tcase, s21_test_64);
  tcase_add_test(tcase, s21_test_65);
  srunner_run_all(srunner, CK_NORMAL);
  val = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return val == 0 ? 0 : 1;
}
