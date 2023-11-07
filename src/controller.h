#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "s21_smartcalc.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  Controller(std::string str) { calc.setExpression(str); }
  Controller(std::string str, double var) {
    calc.setExpression(str);
    calc.setVariable(var);
  }
  ~Controller() = default;

  void setStr(std::string exp) { calc.setExpression(exp); }
  void setVar(double var) { calc.setVariable(var); }
  double eval() { return calc.eval(); }
  void parse() { calc.parse_args(); }
  void sort() { calc.sort_stack(); }
  double count() { return calc.count_result(); }
  void clear_buffer() { calc.clear(); }

  double PMT_anu(double P, double r, int n) { return calc.PMT_anu(P, r, n); }
  double Total_Interest_Paid_anu(double P, double r, int n) {
    return calc.Total_Interest_Paid_anu(P, r, n);
  }
  double Total_Loan_Amount_anu(double P, double r, int n) {
    return calc.Total_Loan_Amount_anu(P, r, n);
  }
  double PMT_diff(double P, double r, int n) { return calc.PMT_diff(P, r, n); }
  double Total_Interest_Paid_diff(double P, double r, int n) {
    return calc.Total_Interest_Paid_diff(P, r, n);
  }
  double Total_Loan_Amount_diff(double P, double r, int n) {
    return calc.Total_Loan_Amount_diff(P, r, n);
  }

 private:
  Calculator calc;
};
}  // namespace s21

#endif
