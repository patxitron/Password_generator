#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <random>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_generate_button_clicked();

private:
    Ui::MainWindow *ui_;
    std::random_device random_device_;
    std::mt19937 random_generator_;
};

#endif // MAINWINDOW_HPP
