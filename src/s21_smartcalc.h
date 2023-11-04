#ifndef S21SMARTCALC_H
#define S21SMARTCALC_H

#include <cmath>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace s21 {
class Calculator {
 public:
  Calculator() = default;
  Calculator(std::string str) : expression(str) {}
  ~Calculator() {}

  void parse_args() {
    size_t index = 0;
    while (index < expression.size()) {
      auto operand = std::find_if(
          operands_map.begin(), operands_map.end(), [&](const auto& op) {
            return expression.compare(index, op.first.size(), op.first) == 0;
          });
      if (operand != operands_map.end()) {
        tmp_mixed_lexeme_list.push_back(operand->first);
        index += operand->first.size();
      } else if (isdigit(expression[index])) {
        std::size_t num_end;
        tmp_mixed_lexeme_list.push_back(
            stod(expression.substr(index), &num_end));
        index += num_end;
      } else if (isalpha(expression[index])) {
        tmp_mixed_lexeme_list.push_back(std::string(1, expression[index++]));
      } else {
        ++index;
      }
    }
  }

  int sort_stack() {
    std::vector<std::variant<std::string, double>> value_stack;
    std::vector<std::string> operators_stack;
    for (const auto& item : tmp_mixed_lexeme_list) {
      auto op = std::get_if<std::string>(&item);
      if (!op) {
        value_stack.push_back(std::get<double>(item));
      } else if (*op == "(") {
        operators_stack.push_back(*op);
      } else if (*op == ")") {
        while (!operators_stack.empty() && operators_stack.back() != "(")
          value_stack.push_back(operators_stack.back()),
              operators_stack.pop_back();
        if (operators_stack.empty() || operators_stack.back() != "(")
          throw std::invalid_argument("bad ')'");
        operators_stack.pop_back();
      } else {
        int priority = operands_map[*op];
        while (!operators_stack.empty() &&
               operands_map[operators_stack.back()] > priority)
          value_stack.push_back(operators_stack.back()),
              operators_stack.pop_back();
        operators_stack.push_back(*op);
      }
    }
    if (std::count(operators_stack.begin(), operators_stack.end(), "("))
      throw std::invalid_argument("bad '('");
    value_stack.insert(value_stack.end(), operators_stack.rbegin(),
                       operators_stack.rend());
    tmp_mixed_lexeme_list = value_stack;
    return 0;
  }

  double count_result() {
    std::vector<double> values;
    for (const auto& item : tmp_mixed_lexeme_list) {
      if (std::holds_alternative<std::string>(item)) {
        const auto& op = std::get<std::string>(item);
        auto& f = function_map[op];
        if (std::holds_alternative<std::function<double(double)>>(f)) {
          if (values.empty()) throw std::invalid_argument("something wrong 1");
          values.back() =
              std::get<std::function<double(double)>>(f)(values.back());
        } else if (std::holds_alternative<
                       std::function<double(double, double)>>(f)) {
          auto& binaryFunc = std::get<std::function<double(double, double)>>(f);
          if (values.size() < 2)
            throw std::invalid_argument("something wrong 2");
          double param2 = values.back();
          values.pop_back();
          values.back() = binaryFunc(values.back(), param2);
        }
      } else {
        values.push_back(std::get<double>(item));
      }
    }
    if (values.size() != 1) throw std::invalid_argument("something wrong 3");
    return values.front();
  }

  void setExpression(std::string str) { expression = str; }

  double eval() {
    parse_args();
    sort_stack();
    return count_result();
  }

 private:
  std::string expression;
  std::unordered_map<std::string, int> operands_map = {
      {"cos", 5},  {"sin", 5},  {"tan", 5}, {"acos", 5}, {"asin", 5},
      {"atan", 5}, {"sqrt", 5}, {"ln", 5},  {"log", 5},  {"mod", 5},
      {"+", 2},    {"-", 2},    {"*", 3},   {"/", 3},    {"^", 4},
      {"(", 1},    {")", 1}};
  std::unordered_map<std::string,
                     std::variant<std::function<double(double, double)>,
                                  std::function<double(double)>>>
      function_map = {
          {"cos",
           std::function<double(double)>([](double x) { return std::cos(x); })},
          {"sin",
           std::function<double(double)>([](double x) { return std::sin(x); })},
          {"tan",
           std::function<double(double)>([](double x) { return std::tan(x); })},
          {"acos", std::function<double(double)>(
                       [](double x) { return std::acos(x); })},
          {"asin", std::function<double(double)>(
                       [](double x) { return std::asin(x); })},
          {"atan", std::function<double(double)>(
                       [](double x) { return std::atan(x); })},
          {"sqrt", std::function<double(double)>(
                       [](double x) { return std::sqrt(x); })},
          {"ln",
           std::function<double(double)>([](double x) { return std::log(x); })},
          {"log", std::function<double(double)>(
                      [](double x) { return std::log10(x); })},
          {"mod", std::function<double(double, double)>(
                      [](double x, double y) { return std::fmod(x, y); })},
          {"+", std::function<double(double, double)>(
                    [](double x, double y) { return x + y; })},
          {"-", std::function<double(double, double)>(
                    [](double x, double y) { return x - y; })},
          {"*", std::function<double(double, double)>(
                    [](double x, double y) { return x * y; })},
          {"/", std::function<double(double, double)>(
                    [](double x, double y) { return x / y; })},
          {"^", std::function<double(double, double)>(
                    [](double x, double y) { return std::pow(x, y); })}};
  std::vector<std::variant<std::string, double>> tmp_mixed_lexeme_list;
};
};  // namespace s21

#endif