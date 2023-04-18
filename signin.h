#ifndef SIGNIN_H
#define SIGNIN_H
#include <QMainWindow>

namespace Ui {
class SignIn;
}

class SignIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_SigninButton_clicked();

private:
    Ui::SignIn *ui;
    QString username_array[6] = {"Ahmed", "Mohamed", "Reem", "Mariam", "Rosanna", "Milo"};
    QString password_array[6] = {"ahmed1", "mohamed1", "reem1", "mariam1", "rosanna1", "milo2018"};
    double balance_array[6] = {100, 200, 300, 400, 500, 1010010};
};

#endif // SIGNIN_H
