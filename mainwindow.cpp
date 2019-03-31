#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QString>
#include <QByteArray>

namespace {

static char const symbol_dictionary[] = "_-=+{}[]@!";
static char const regular_dictionary[] = "0123456789ABCDEFGHJKLMNPRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

} // Anonymous

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    random_device_(),
    random_generator_(random_device_())
{
    ui_->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::on_generate_button_clicked()
{
    size_t length = static_cast<size_t>(ui_->length_spin_box->value());
    QString result(length, QChar(' '));
    std::uniform_int_distribution<size_t> distribution(0, sizeof(regular_dictionary) - 1);
    for (size_t i = 0; i < length; i++) {
        result.replace(i, 1, QChar(regular_dictionary[distribution(random_generator_)]));
    }
    if (ui_->symbols_check_box->isChecked()) {
        size_t symbols = 0;
        std::uniform_int_distribution<size_t> symbol_distribution(0, sizeof(symbol_dictionary) - 1);
        std::uniform_int_distribution<size_t> symbol_placement(0, length - 1);
        if (length < 15) {
            symbols = 1;
        } else if (length < 32) {
            symbols = 2;
        } else {
            symbols = 3;
        }
        for (size_t i = 0; i < symbols; i++) {
            result.replace(symbol_placement(random_generator_), 1, symbol_dictionary[symbol_distribution(random_generator_)]);
        }
    }
    ui_->result_line_edit->setText(result);
}
