#include <cairomm/context.h>
#include <gtkmm.h>

#include "controller.h"

class GradientBackground : public Gtk::DrawingArea {
 public:
  GradientBackground() {
    signal_draw().connect([this](const Cairo::RefPtr<Cairo::Context> &cr) {
      int width = get_allocated_width();
      int height = get_allocated_height();

      double angle = 30.0;

      double start_x = 0;
      double start_y = 0;
      double end_x = width * cos(angle * M_PI / 180);
      double end_y = height * sin(angle * M_PI / 180);

      Cairo::RefPtr<Cairo::LinearGradient> gradient =
          Cairo::LinearGradient::create(start_x, start_y, end_x, end_y);
      gradient->add_color_stop_rgba(0.0, 1.0, 0.0, 0.0, 1.0);
      gradient->add_color_stop_rgba(1.0, 0.0, 0.0, 0.0, 1.0);

      cr->set_source(gradient);
      cr->rectangle(0, 0, width, height);
      cr->fill();

      return true;
    });
  }
};

class MyButtonBox : public Gtk::Box {
 public:
  MyButtonBox(Gtk::Orientation orientation, int spacing)
      : Gtk::Box(orientation, spacing) {
    set_valign(Gtk::ALIGN_CENTER);
    set_margin_top(20);
    set_margin_bottom(20);
    set_margin_start(20);
    set_margin_end(20);
  }
};

class MyButton : public Gtk::Button {
 public:
  MyButton(const std::string &label, int size) : Gtk::Button(label) {
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(R"(
            button {
                border: 2px solid rgba(255, 255, 255, 0.7);
                color: white;
                font-size: 18px;
                padding: 10px 20px;
                margin: 5px;
            }
            button:hover {
                background-color: rgba(255, 255, 255, 0.2);
                color: white;
            }
        )");

    get_style_context()->add_provider(css_provider,
                                      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    set_size_request(-1, size);
  }
};

class CalculatorWindow : public Gtk::Window {
 public:
  CalculatorWindow() {
    set_default_size(800, 700);
    set_title("Calculator");

    GradientBackground *background_calc = new GradientBackground();
    Gtk::Overlay *calc_overlay = new Gtk::Overlay();

    Gtk::Box *vbox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    vbox->set_margin_top(10);
    vbox->set_margin_left(20);
    vbox->set_margin_right(20);
    vbox->set_margin_bottom(20);

    Gtk::Grid *grid = new Gtk::Grid();
    entry = new Gtk::Entry();
    entry->set_placeholder_text("Введите выражение...");

    entry->signal_activate().connect(
        [this]() { entry->set_placeholder_text(""); });

    MyButton *button_calculate = new MyButton("Рассчитать", 40);
    entry->set_hexpand(true);
    entry->set_margin_bottom(5);

    button_calculate->signal_clicked().connect([this]() {
      std::string expression = entry->get_text();
      controller.clear_buffer();
      controller.setStr(expression);
      calculation_requested = true;
      this->queue_draw();
    });

    grid->set_column_homogeneous(true);
    grid->set_row_homogeneous(true);
    grid->attach(*entry, 0, 0, 1, 1);
    grid->attach(*button_calculate, 0, 1, 1, 1);

    vbox->pack_start(*grid, Gtk::PACK_SHRINK, 0);

    Gtk::DrawingArea *graph_area = new Gtk::DrawingArea();
    graph_area->set_margin_top(25);
    graph_area->set_margin_bottom(20);
    graph_area->set_margin_right(20);
    graph_area->set_margin_left(20);

    vbox->pack_start(*graph_area, Gtk::PACK_EXPAND_WIDGET, 0);

    Gtk::Grid *grid1 = new Gtk::Grid();

    x_limit_min = new Gtk::Entry();
    x_limit_min->set_placeholder_text("Минимальное X");
    x_limit_min->set_margin_bottom(5);
    x_limit_min->set_margin_right(5);

    x_limit_max = new Gtk::Entry();
    x_limit_max->set_placeholder_text("Максимальное X");
    x_limit_max->set_margin_bottom(5);
    x_limit_max->set_margin_left(5);

    y_limit_min = new Gtk::Entry();
    y_limit_min->set_placeholder_text("Минимальное Y");
    y_limit_min->set_margin_top(5);
    y_limit_min->set_margin_right(5);

    y_limit_max = new Gtk::Entry();
    y_limit_max->set_placeholder_text("Максимальное Y");
    y_limit_max->set_margin_top(5);
    y_limit_max->set_margin_left(5);

    grid1->set_column_homogeneous(true);
    grid1->set_row_homogeneous(true);

    x_limit_min->signal_activate().connect(
        [this]() { x_limit_min->set_placeholder_text(""); });

    x_limit_max->signal_activate().connect(
        [this]() { x_limit_max->set_placeholder_text(""); });

    y_limit_min->signal_activate().connect(
        [this]() { y_limit_min->set_placeholder_text(""); });

    y_limit_max->signal_activate().connect(
        [this]() { y_limit_max->set_placeholder_text(""); });

    grid1->attach(*x_limit_min, 0, 0, 1, 1);
    grid1->attach(*x_limit_max, 1, 0, 1, 1);
    grid1->attach(*y_limit_min, 0, 1, 1, 1);
    grid1->attach(*y_limit_max, 1, 1, 1, 1);

    vbox->pack_start(*grid1, Gtk::PACK_SHRINK, 0);

    graph_area->signal_draw().connect(
        [graph_area, this](const Cairo::RefPtr<Cairo::Context> &cr) -> bool {
          int width = graph_area->get_allocated_width();
          int height = graph_area->get_allocated_height();
          double step = 0.005;
          double x_min = -10, x_max = 10;
          double y_min = -5, y_max = 5;

          std::string x_limit_min_text = x_limit_min->get_text();
          std::string x_limit_max_text = x_limit_max->get_text();
          std::string y_limit_min_text = y_limit_min->get_text();
          std::string y_limit_max_text = y_limit_max->get_text();

          if (!x_limit_min_text.empty()) {
            x_min = std::stod(x_limit_min_text);
          }
          if (!x_limit_max_text.empty()) {
            x_max = std::stod(x_limit_max_text);
          }
          if (!y_limit_min_text.empty()) {
            y_min = std::stod(y_limit_min_text);
          }
          if (!y_limit_max_text.empty()) {
            y_max = std::stod(y_limit_max_text);
          }

          cr->save();
          cr->set_source_rgb(1.0, 1.0, 1.0);
          cr->paint();
          cr->restore();

          cr->set_source_rgb(0.0, 0.0, 0.0);
          cr->set_line_width(1.0);

          double y_axis = height - (0 - y_min) * (height / (y_max - y_min));
          cr->move_to(0, y_axis);
          cr->line_to(width, y_axis);

          double x_axis = (0 - x_min) * (width / (x_max - x_min));
          cr->move_to(x_axis, 0);
          cr->line_to(x_axis, height);

          cr->stroke();

          controller.parse();
          try {
            controller.sort();
            if (calculation_requested) {
              double y_prev = 0.f;
              for (double x = x_min; x < x_max; x += step) {
                controller.setVar(x);
                try {
                  double result = controller.count();

                  if (!std::isinf(result) && !std::isnan(result)) {
                    double x_fixed = (x - x_min) * (width / (x_max - x_min));
                    double y_fixed =
                        height - (result - y_min) * (height / (y_max - y_min));
                    if ((y_prev >= y_max && y_fixed <= y_min) ||
                        (y_prev <= y_min && y_fixed >= y_max)) {
                      cr->stroke();
                    } else {
                      cr->line_to(x_fixed, y_fixed);
                    }
                    y_prev = y_fixed;
                  }
                } catch (const std::exception &ex) {
                }
              }

              cr->stroke();

              calculation_requested = false;
            }
          } catch (const std::exception &ex) {
          }

          return true;
        });

    calc_overlay->add(*background_calc);
    calc_overlay->add_overlay(*vbox);

    add(*calc_overlay);
    show_all();
  }

 private:
  s21::Controller controller;
  Gtk::Entry *entry;
  bool calculation_requested = false;
  Gtk::Entry *x_limit_min;
  Gtk::Entry *x_limit_max;
  Gtk::Entry *y_limit_min;
  Gtk::Entry *y_limit_max;
};

class DisplayLoanInfo : public Gtk::Window {
 public:
  DisplayLoanInfo(double PMT, double Total_Interest_Paid,
                  double Total_Loan_Amount) {
    set_default_size(425, 240);
    set_resizable(false);
    set_title("Loan Info");

    GradientBackground *background_loan_info = new GradientBackground();
    Gtk::Overlay *loan_info_overlay = new Gtk::Overlay();

    Gtk::Box *vbox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    vbox->set_margin_top(10);
    vbox->set_margin_left(20);
    vbox->set_margin_right(20);
    vbox->set_margin_bottom(20);

    Gtk::Label *label_pmt = new Gtk::Label("Ежемесячный платеж: ");
    Gtk::Label *label_interest = new Gtk::Label("Общая сумма процентов: ");
    Gtk::Label *label_total = new Gtk::Label("Общая сумма кредита: ");

    Gtk::Label *pmt_value = new Gtk::Label(std::to_string(PMT));
    Gtk::Label *interest_value =
        new Gtk::Label(std::to_string(Total_Interest_Paid));
    Gtk::Label *total_value = new Gtk::Label(std::to_string(Total_Loan_Amount));

    vbox->pack_start(*label_pmt, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*pmt_value, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*label_interest, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*interest_value, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*label_total, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*total_value, Gtk::PACK_SHRINK, 0);

    loan_info_overlay->add(*background_loan_info);
    loan_info_overlay->add_overlay(*vbox);
    add(*loan_info_overlay);
    show_all();
  }
};

class LoanWindow : public Gtk::Window {
 public:
  LoanWindow() {
    set_default_size(425, 240);
    set_resizable(false);
    set_title("Loan Calculator");

    GradientBackground *background_loan = new GradientBackground();
    Gtk::Overlay *loan_overlay = new Gtk::Overlay();

    Gtk::Box *vbox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    vbox->set_margin_top(10);
    vbox->set_margin_left(20);
    vbox->set_margin_right(20);
    vbox->set_margin_bottom(20);

    Gtk::Grid *grid = new Gtk::Grid();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);

    Gtk::Label *label_amount = new Gtk::Label("Сумма кредита:");
    Gtk::Label *label_term = new Gtk::Label("Срок (в месяцах):");
    Gtk::Label *label_interest = new Gtk::Label("Процентная ставка (%):");
    Gtk::Label *label_loan_type = new Gtk::Label("Тип кредита:");

    entry_amount = new Gtk::Entry();
    spin_term = new Gtk::SpinButton();
    spin_term->set_digits(0);
    spin_term->set_range(1, 360);
    spin_term->set_increments(1, 10);

    spin_interest = new Gtk::SpinButton();
    spin_interest->set_digits(2);
    spin_interest->set_range(0, 100);
    spin_interest->set_increments(0.1, 1);

    combo_loan_type = new Gtk::ComboBoxText();
    combo_loan_type->append("annuity", "Аннуитетный");
    combo_loan_type->append("differentiated", "Дифференцированный");
    combo_loan_type->set_active(0);

    grid->attach(*label_amount, 0, 0, 1, 1);
    grid->attach(*entry_amount, 1, 0, 1, 1);
    grid->attach(*label_term, 0, 1, 1, 1);
    grid->attach(*spin_term, 1, 1, 1, 1);
    grid->attach(*label_interest, 0, 2, 1, 1);
    grid->attach(*spin_interest, 1, 2, 1, 1);
    grid->attach(*label_loan_type, 0, 3, 1, 1);
    grid->attach(*combo_loan_type, 1, 3, 1, 1);

    vbox->pack_start(*grid, Gtk::PACK_SHRINK, 0);

    Gtk::Button *button_calculate = new Gtk::Button("Рассчитать", 40);
    button_calculate->signal_clicked().connect([this]() {
      std::string loan_type = combo_loan_type->get_active_text();

      std::string loan_str = entry_amount->get_text();
      double loan = std::stod(loan_str);

      std::string term_str = spin_term->get_text();
      int term = std::stoi(term_str);

      std::string interest_rate_str = spin_interest->get_text();
      double interest_rate = std::stod(interest_rate_str);

      if (loan_type == "Аннуитетный") {
        PMT = controller.PMT_anu(loan, interest_rate, term);
        Total_Interest_Paid =
            controller.Total_Interest_Paid_anu(loan, interest_rate, term);
        Total_Loan_Amount =
            controller.Total_Loan_Amount_anu(loan, interest_rate, term);
      } else {
        PMT = controller.PMT_diff(loan, interest_rate, term);
        Total_Interest_Paid =
            controller.Total_Interest_Paid_diff(loan, interest_rate, term);
        Total_Loan_Amount =
            controller.Total_Loan_Amount_diff(loan, interest_rate, term);
      }
      DisplayLoanInfo *info_window =
          new DisplayLoanInfo(PMT, Total_Interest_Paid, Total_Loan_Amount);
    });

    grid->attach(*button_calculate, 0, 4, 2, 1);

    loan_overlay->add(*background_loan);
    loan_overlay->add_overlay(*vbox);

    add(*loan_overlay);
    show_all();
  }

 private:
  Gtk::Entry *entry_amount;
  Gtk::SpinButton *spin_term;
  Gtk::SpinButton *spin_interest;
  Gtk::ComboBoxText *combo_loan_type;
  double PMT;
  double Total_Interest_Paid;
  double Total_Loan_Amount;
  s21::Controller controller;
};

class DisplayDepositInfo : public Gtk::Window {
 public:
  DisplayDepositInfo(double PMT, double Total_Interest_Paid,
                     double Total_Loan_Amount) {
    set_default_size(425, 240);
    set_resizable(false);
    set_title("Deposit Info");

    GradientBackground *background_loan_info = new GradientBackground();
    Gtk::Overlay *loan_info_overlay = new Gtk::Overlay();

    Gtk::Box *vbox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    vbox->set_margin_top(10);
    vbox->set_margin_left(20);
    vbox->set_margin_right(20);
    vbox->set_margin_bottom(20);

    Gtk::Label *label_pmt = new Gtk::Label("Начисленные проценты: ");
    Gtk::Label *label_interest = new Gtk::Label("Сумма налога: ");
    Gtk::Label *label_total = new Gtk::Label("Сумма на вкладе: ");

    Gtk::Label *pmt_value = new Gtk::Label(std::to_string(PMT));
    Gtk::Label *interest_value =
        new Gtk::Label(std::to_string(Total_Interest_Paid));
    Gtk::Label *total_value = new Gtk::Label(std::to_string(Total_Loan_Amount));

    vbox->pack_start(*label_pmt, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*pmt_value, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*label_interest, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*interest_value, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*label_total, Gtk::PACK_SHRINK, 0);
    vbox->pack_start(*total_value, Gtk::PACK_SHRINK, 0);

    loan_info_overlay->add(*background_loan_info);
    loan_info_overlay->add_overlay(*vbox);
    add(*loan_info_overlay);
    show_all();
  }
};

class DepositWindow : public Gtk::Window {
 public:
  DepositWindow() {
    set_default_size(500, 325);
    set_resizable(false);
    set_title("Deposit Calculator");

    GradientBackground *background_deposit = new GradientBackground();
    Gtk::Overlay *deposit_overlay = new Gtk::Overlay();

    Gtk::Box *vbox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    vbox->set_margin_top(10);
    vbox->set_margin_left(20);
    vbox->set_margin_right(20);
    vbox->set_margin_bottom(20);

    Gtk::Grid *grid = new Gtk::Grid();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);

    Gtk::Label *label_principal = new Gtk::Label("Сумма вклада:");
    Gtk::Label *label_term = new Gtk::Label("Срок размещения (в месяцах):");
    Gtk::Label *label_interest = new Gtk::Label("Процентная ставка (%):");
    Gtk::Label *label_tax_rate = new Gtk::Label("Налоговая ставка (%):");
    Gtk::Label *label_compound = new Gtk::Label("Капитализация процентов:");
    Gtk::Label *label_inw =
        new Gtk::Label("Сумма частичных пополнений/снятий:");

    entry_principal = new Gtk::Entry();
    spin_term = new Gtk::SpinButton();
    spin_term->set_digits(0);
    spin_term->set_range(1, 360);
    spin_term->set_increments(1, 10);

    spin_interest = new Gtk::SpinButton();
    spin_interest->set_digits(2);
    spin_interest->set_range(0, 100);
    spin_interest->set_increments(0.1, 1);

    spin_tax_rate = new Gtk::SpinButton();
    spin_tax_rate->set_digits(2);
    spin_tax_rate->set_range(0, 100);
    spin_tax_rate->set_increments(0.1, 1);

    combo_compound = new Gtk::ComboBoxText();
    combo_compound->append("annually", "Ежегодно");
    combo_compound->append("quarterly", "Ежеквартально");
    combo_compound->append("monthly", "Ежемесячно");
    combo_compound->set_active(0);

    input_with = new Gtk::SpinButton();
    input_with->set_digits(2);
    input_with->set_range(0, 100);
    input_with->set_increments(0.1, 1);

    grid->attach(*label_principal, 0, 0, 1, 1);
    grid->attach(*entry_principal, 1, 0, 1, 1);
    grid->attach(*label_term, 0, 1, 1, 1);
    grid->attach(*spin_term, 1, 1, 1, 1);
    grid->attach(*label_interest, 0, 2, 1, 1);
    grid->attach(*spin_interest, 1, 2, 1, 1);
    grid->attach(*label_tax_rate, 0, 3, 1, 1);
    grid->attach(*spin_tax_rate, 1, 3, 1, 1);
    grid->attach(*label_compound, 0, 4, 1, 1);
    grid->attach(*combo_compound, 1, 4, 1, 1);
    grid->attach(*label_inw, 0, 5, 1, 1);
    grid->attach(*input_with, 1, 5, 1, 1);

    Gtk::Button *button_calculate = new Gtk::Button("Рассчитать", 40);
    button_calculate->signal_clicked().connect([this]() {
      double principal = std::stod(entry_principal->get_text());
      int term = spin_term->get_value_as_int();
      double interest_rate = spin_interest->get_value();
      double tax_rate = spin_tax_rate->get_value();
      std::string compound_option = combo_compound->get_active_text();
      double input_withdraw = input_with->get_value();

      double earned_interest = controller.CalculateEarnedInterest(
          principal, interest_rate, term, input_withdraw, compound_option);
      double tax_amount = controller.CalculateTax(earned_interest, tax_rate);
      double total_amount = controller.CalculateTotalAmount(
          principal, earned_interest, tax_amount, input_withdraw);

      DisplayDepositInfo *info_window =
          new DisplayDepositInfo(earned_interest, tax_amount, total_amount);
    });
    grid->attach(*button_calculate, 0, 6, 2, 1);

    vbox->pack_start(*grid, Gtk::PACK_SHRINK, 0);

    deposit_overlay->add(*background_deposit);
    deposit_overlay->add_overlay(*vbox);

    add(*deposit_overlay);
    show_all();
  }

 private:
  Gtk::Entry *entry_principal;
  Gtk::SpinButton *spin_term;
  Gtk::SpinButton *spin_interest;
  Gtk::SpinButton *spin_tax_rate;
  Gtk::ComboBoxText *combo_compound;
  Gtk::SpinButton *input_with;
  s21::Controller controller;
};

bool on_delete_event(GdkEventAny *event) { return false; }

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.example.gtkmmexample");

  Gtk::Window window;
  window.set_default_size(320, 400);
  window.set_resizable(false);
  window.set_title("SmartCalc");
  Gtk::Overlay overlay;

  GradientBackground background;
  overlay.add(background);

  MyButtonBox buttonBox(Gtk::ORIENTATION_VERTICAL, 10);

  MyButton button_calculator("Калькулятор", 100);
  MyButton button_loan_calculator("Кредитный калькулятор", 100);
  MyButton button_deposit_calculator("Депозитный калькулятор", 100);

  buttonBox.pack_start(button_calculator, Gtk::PACK_SHRINK, 0);
  buttonBox.pack_start(button_loan_calculator, Gtk::PACK_SHRINK, 0);
  buttonBox.pack_start(button_deposit_calculator, Gtk::PACK_SHRINK, 0);

  button_calculator.signal_clicked().connect(
      [&]() { CalculatorWindow *calc_window = new CalculatorWindow(); });

  button_loan_calculator.signal_clicked().connect(
      [&]() { LoanWindow *loan_window = new LoanWindow(); });

  button_deposit_calculator.signal_clicked().connect(
      [&]() { DepositWindow *deposit_window = new DepositWindow(); });

  overlay.add_overlay(buttonBox);
  window.signal_delete_event().connect(sigc::ptr_fun(&on_delete_event));
  window.add(overlay);
  window.show_all();

  return app->run(window);
}
