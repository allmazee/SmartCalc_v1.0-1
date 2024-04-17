#include <check.h>
#include <math.h>
#include <stdio.h>

#include "../smart_calc.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

START_TEST(test_0) {
  char *input_str = {
      "1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17+18+19+20+21+22+23+24+25+26+27+"
      "28+29+30+31+32+33+34+35+36+37+38+39+40+41+42+43+44+45+46+47+48+49+50+51+"
      "52+53+54+55+56+57+58+59+60+61+62+63+64+65+66+67+68+69+70+71+72+73+74+75+"
      "76+77+78+79+80+81+82+83+84+85+86+87+88+89+90+91+92+93+94+95+96+97+98+99+"
      "100+101+102+103+104+105+106+107+108+109+110+111+112+113+114+115+116+117+"
      "118+119+120+121+122+123+124+125+126+127+128"};
  double x = M_PI / 2.0;
  double ans = 8256;
  double res = get_result(x, input_str);
  ck_assert_double_eq_tol(ans, res, 1e-7);
}
END_TEST

START_TEST(test_1) {
  char input_str[STACK_MAX_SIZE] = {"-1*sin(cos(tan(-x^2)^3)^4)"};
  double x = M_PI / 2.0;
  double ans = -1 * sinf(powf(cosf(powf(tanf(powf(-x, 2)), 3)), 4));
  double res = get_result(x, input_str);
  ck_assert_double_eq_tol(ans, res, 1e-7);
}
END_TEST

START_TEST(test_2) {
  double res = get_result(0, "1-2*12-3^2");
  ck_assert_double_eq_tol(res, -32, 7);
}
END_TEST

START_TEST(test_3) {
  double res = get_result(0, "((1)-2-((-3)-(4)))-5-(-6)");
  ck_assert_double_eq(((1) - 2 - ((-3) - (4))) - 5 - (-6), res);
}
END_TEST

START_TEST(test_4) {
  double res = get_result(0, "sin(12)-3");
  ck_assert_double_eq_tol(res, sin(12) - 3, 7);
}
END_TEST

START_TEST(test_5) {
  double res = get_result(0, "ln(12)^3-1*(-12+5)");
  ck_assert_double_eq_tol(res, pow(log(12), 3.0) - 1 * (-12 + 5), 7);
}
END_TEST

START_TEST(test_6) {
  double res = get_result(0, "(-5)mod(-3)");
  ck_assert_double_eq(fmod(-5, -3), res);
}
END_TEST

START_TEST(test_7) {
  double res = get_result(0, "2^3^4");
  ck_assert_double_eq(pow(2, pow(3, 4)), res);
}
END_TEST

START_TEST(test_8) {
  double res = get_result(0, "1+2-3");
  ck_assert_double_eq_tol(res, 1 + 2 - 3, 7);
}
END_TEST

START_TEST(test_9) {
  char input_str[STACK_MAX_SIZE] = {"(1+2)*((3-4)+1+(5-6+7))"};
  double x = 1.0;
  double ans = (1 + 2) * ((3 - 4) + 1 + (5 - 6 + 7));
  double res = get_result(x, input_str);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_10) {
  double res = get_result(
      0, "(cos((-5)))+ln((10/(5*7))^2)-(tan(sin(-3mod2))-5mod3*4/5/7)");
  ck_assert_double_eq_tol(res, -0.874353, 7);
}
END_TEST

START_TEST(test_11) {
  double res = get_result(0, "cos(cos(12))-3-5");
  ck_assert_double_eq_tol(res, cos(cos(12)) - 3 - 5, 7);
}
END_TEST

START_TEST(test_12) {
  double res = get_result(0, "sqrt(atan(12))");
  ck_assert_double_eq_tol(res, sqrt(atan(12)), 7);
}
END_TEST

START_TEST(test_13) {
  double res = get_result(0, "asin(1)");
  ck_assert_double_eq_tol(res, asin(1), 7);
}
END_TEST

START_TEST(test_14) {
  double res = get_result(M_PI, "x");
  ck_assert_double_eq(M_PI, res);
}
END_TEST

START_TEST(test_15) {
  double res = get_result(M_PI, "-x");
  ck_assert_double_eq(-M_PI, res);
}
END_TEST

START_TEST(test_16) {
  double res = get_result(0, "1.2345678+2.3456789-3");
  ck_assert_double_eq(1.2345678 + 2.3456789 - 3, res);
}
END_TEST

START_TEST(test_17) {
  double res = get_result(0, "sqrt(25)");
  ck_assert_double_eq(sqrt(25), res);
}
END_TEST
// isnan tests

START_TEST(test_18) {
  char *input_str = "1*(*x)";
  double x = 1.0;
  double res = get_result(x, input_str);
  ck_assert_double_eq(1, isnan(res));
}
END_TEST

START_TEST(test_19) {
  char *input_str = "ecco2k";
  double x = 1.0;
  double res = get_result(x, input_str);
  ck_assert_double_eq(1, isnan(res));
}
END_TEST

START_TEST(test_20) {
  char *input_str = "tin(111)";
  double x = 1.0;
  double res = get_result(x, input_str);
  ck_assert_double_eq(1, isnan(res));
}
END_TEST

START_TEST(test_21) {
  char *input_str = NULL;
  double x = 1.0;
  double res = get_result(x, input_str);
  ck_assert_double_eq(1, isnan(res));
}
END_TEST

START_TEST(test_22) {
  char input_str[STACK_MAX_SIZE] = {"si(2)"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_23) {
  char input_str[STACK_MAX_SIZE] = {"st()"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_24) {
  char input_str[STACK_MAX_SIZE] = {"cos"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_25) {
  char input_str[STACK_MAX_SIZE] = {"tan"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_26) {
  char input_str[STACK_MAX_SIZE] = {"*tan(22)"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_27) {
  char input_str[STACK_MAX_SIZE] = {"adin"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_28) {
  char input_str[STACK_MAX_SIZE] = {"lag"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_29) {
  char input_str[STACK_MAX_SIZE] = {"3&8"};
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_30) {
  char input_str[] = "cos5";
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_31) {
  char input_str[] = "cos(5";
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

START_TEST(test_32) {
  char input_str[] = "99mob2";
  double x = M_PI;
  double res = get_result(x, input_str);
  ck_assert_int_eq(1, isnan(res));
}
END_TEST

int test() {
  Suite *s = suite_create("All Part");
  TCase *tc = tcase_create("Test1");
  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_0);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  tcase_add_test(tc, test_22);
  tcase_add_test(tc, test_23);
  tcase_add_test(tc, test_24);
  tcase_add_test(tc, test_25);
  tcase_add_test(tc, test_26);
  tcase_add_test(tc, test_27);
  tcase_add_test(tc, test_28);
  tcase_add_test(tc, test_29);
  tcase_add_test(tc, test_30);
  tcase_add_test(tc, test_31);
  tcase_add_test(tc, test_32);

  srunner_run_all(sr, CK_ENV);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf;
}

int main(void) {
  int nf = 0;
  nf += test();
  return nf;
}