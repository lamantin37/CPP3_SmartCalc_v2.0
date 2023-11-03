#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <list>
#include <variant>
#include <functional>
#include <cmath>

class Calculator {
public:
    Calculator() = default;
    Calculator(std::string str) : expression(str) {};
    ~Calculator() {};

    void parse_args() {
        size_t index = 0;
        while (index < expression.size()) {
            auto operand = std::find_if(operands_map.begin(), operands_map.end(),
                [&](const auto& op) { return expression.compare(index, op.first.size(), op.first) == 0; });
            if (operand != operands_map.end()) {
                tmp_mixed_lexeme_list.push_back(operand->first);
                index += operand->first.size();
            } else if (std::isdigit(expression[index])) {
                std::size_t num_end;
                tmp_mixed_lexeme_list.push_back(std::stod(expression.substr(index), &num_end));
                index += num_end;
            } else if (std::isalpha(expression[index])) {
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
            if (std::holds_alternative<std::string>(item)) {
                const auto& op = std::get<std::string>(item);
                if (op == "(") {
                    operators_stack.push_back(op);
                } else if (op == ")") {
                    while (!operators_stack.empty() && operators_stack.back() != "(") {
                        value_stack.push_back(operators_stack.back());
                        operators_stack.pop_back();
                    }
                    if (!operators_stack.empty() && operators_stack.back() == "(") {
                        operators_stack.pop_back();
                    } else {
                        throw std::invalid_argument("bad ')'");
                    }
                } else {
                    int priority_ = operands_map[op];
                    while (!operators_stack.empty() && operands_map[operators_stack.back()] > priority_) {
                        value_stack.push_back(operators_stack.back());
                        operators_stack.pop_back();
                    }
                    operators_stack.push_back(op);
                }
            } else {
                value_stack.push_back(std::get<double>(item));
            }
        }

        if (std::find(operators_stack.begin(), operators_stack.end(), "(") != std::end(operators_stack)) {
            throw std::invalid_argument("bad '('");
        }

        while (!operators_stack.empty()) {
            value_stack.push_back(operators_stack.back());
            operators_stack.pop_back();
        }

        tmp_mixed_lexeme_list = value_stack;
        return 0;
    }

    double count_result() {
        std::vector<double> values_;
        for (const auto& item : tmp_mixed_lexeme_list) {
            if (std::holds_alternative<std::string>(item)) {
                const auto& op = std::get<std::string>(item);
                if (function_map.find(op) != function_map.end()) {
                    auto it = function_map.find(op);
                    if (std::holds_alternative<std::function<double(double, double)>>(it->second)) {
                        auto binaryFunc = std::get<std::function<double(double, double)>>(it->second);
                        if (values_.size() >= 2) {
                            double param2 = values_.back();
                            values_.pop_back();
                            double param1 = values_.back();
                            values_.pop_back();
                            double result = binaryFunc(param1, param2);
                            values_.push_back(result);
                        } else {
                            throw std::invalid_argument("something wrong 2");
                        }
                    } else if (std::holds_alternative<std::function<double(double)>>(it->second)) {
                        auto unaryFunc = std::get<std::function<double(double)>>(it->second);
                        if (!values_.empty()) {
                            double param1 = values_.back();
                            values_.pop_back();
                            double result = unaryFunc(param1);
                            values_.push_back(result);
                        } else {
                            throw std::invalid_argument("something wrong 1");
                        }
                    }
                }
            } else if (std::holds_alternative<double>(item)) {
                values_.push_back(std::get<double>(item));
            }
        }
        if (values_.size() != 1) throw std::invalid_argument("something wrong 3");
        return values_.front();
    }

    void setExpression(std::string str) {
        expression = str;
    }

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
        {"(", 1},    {")", 1}
    };
    std::unordered_map<std::string, std::variant<std::function<double(double, double)>, std::function<double(double)>>> function_map = {
        {"cos", std::function<double(double)>([](double x) { return std::cos(x); })},
        {"sin", std::function<double(double)>([](double x) { return std::sin(x); })},
        {"tan", std::function<double(double)>([](double x) { return std::tan(x); })},
        {"acos", std::function<double(double)>([](double x) { return std::acos(x); })},
        {"asin", std::function<double(double)>([](double x) { return std::asin(x); })},
        {"atan", std::function<double(double)>([](double x) { return std::atan(x); })},
        {"sqrt", std::function<double(double)>([](double x) { return std::sqrt(x); })},
        {"ln", std::function<double(double)>([](double x) { return std::log(x); })},
        {"log", std::function<double(double)>([](double x) { return std::log10(x); })},
        {"mod", std::function<double(double, double)>([](double x, double y) { return std::fmod(x, y); })},
        {"+", std::function<double(double, double)>([](double x, double y) { return x + y; })},
        {"-", std::function<double(double, double)>([](double x, double y) { return x - y; })},
        {"*", std::function<double(double, double)>([](double x, double y) { return x * y; })},
        {"/", std::function<double(double, double)>([](double x, double y) { return x / y; })},
        {"^", std::function<double(double, double)>([](double x, double y) { return std::pow(x, y); })}
    };
    std::vector<std::variant<std::string, double>> tmp_mixed_lexeme_list;
};

int main() {
    std::string expression = "10 * (2 + (3 ^ sin(0.5 * (2*4))))";
    Calculator calc(expression);
    std::cout << calc.eval() << std::endl;

    return 0;
}

