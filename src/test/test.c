#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "../calculate.h"
#include "../reverse_polish_notation.h"
#include "../stack.h"
#include "../valid.h"

START_TEST(sum) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = 1029.0;
  char mass[] = "245+784";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(sub) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = -700.0;
  char mass[] = "-650-50";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(mult) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = 25;
  char mass[] = "5*5";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(power) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = 25;
  char mass[] = "5^2";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(mod) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = 0.8;
  char mass[] = "3.1mod2.3";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(mul) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = 5;
  char mass[] = "25/5";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(cosx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = cos(x_value);
  char mass[] = "cos(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(sinx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = sin(x_value);
  char mass[] = "sin(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(tanx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = tan(x_value);
  char mass[] = "tan(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(acosx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = acos(x_value);
  char mass[] = "acos(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(asinx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = asin(x_value);
  char mass[] = "asin(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(atanx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = atan(x_value);
  char mass[] = "atan(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(lnx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = log(x_value);
  char mass[] = "log(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(lgx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  double right_res = log10(x_value);
  char mass[] = "ln(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(sqrtx) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 196.0;
  double result = 14.0;
  double right_res = sqrt(x_value);
  char mass[] = "sqrt(x)";
  output = validation_array(mass);
  ck_assert_int_eq(output, OK);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_nonnull(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, OK);
  ck_assert_double_lt(fabs(result - right_res), 1e-07);
  free(lexem_arr);
}
END_TEST

START_TEST(memory) {
  int output = OK;
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char *mass = NULL;
  output = validation_array(mass);
  ck_assert_int_eq(output, MEMORY_ERROR);
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  ck_assert_ptr_null(lexem_arr);
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, MEMORY_ERROR);
  free(lexem_arr);
}
END_TEST

START_TEST(syntax) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "1.2.+4";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}
END_TEST

START_TEST(syntax1) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "cosx";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}

START_TEST(syntax2) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "1+)(2";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}

START_TEST(syntax3) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "asinx";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}

START_TEST(syntax4) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "2++3";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}

START_TEST(syntax5) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "1.2x";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}

START_TEST(syntax8) {
  int number_lexem = 0;
  double x_value = 1.0;
  double result = 0.0;
  char mass[] = "++6";
  int output = validation_array(mass);
  if(output == OK) {
  lexem *lexem_arr = reverse_polish_notation(mass, &number_lexem);
  if(lexem_arr != NULL) {
  output = calculate(lexem_arr, number_lexem, &result, x_value);
  ck_assert_int_eq(output, SYNTAX_ERROR);
  free(lexem_arr);
  }
  }
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, sum);
  tcase_add_test(tc1_1, sub);
  tcase_add_test(tc1_1, mult);
  tcase_add_test(tc1_1, power);
  tcase_add_test(tc1_1, mod);
  tcase_add_test(tc1_1, mul);
  tcase_add_test(tc1_1, cosx);
  tcase_add_test(tc1_1, sinx);
  tcase_add_test(tc1_1, tanx);
  tcase_add_test(tc1_1, acosx);
  tcase_add_test(tc1_1, asinx);
  tcase_add_test(tc1_1, atanx);
  tcase_add_test(tc1_1, lnx);
  tcase_add_test(tc1_1, lgx);
  tcase_add_test(tc1_1, sqrtx);
  tcase_add_test(tc1_1, memory);
  tcase_add_test(tc1_1, syntax);
  tcase_add_test(tc1_1, syntax1);
  tcase_add_test(tc1_1, syntax2);
  tcase_add_test(tc1_1, syntax3);
  tcase_add_test(tc1_1, syntax4);
  tcase_add_test(tc1_1, syntax5);
  tcase_add_test(tc1_1, syntax8);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}