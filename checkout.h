#ifndef CHECKOUT_H
#define CHECKOUT_H
#include <QDialog>

namespace Ui {
class CheckOut;
}

class CheckOut : public QDialog
{
    Q_OBJECT

public:
    explicit CheckOut(QWidget *parent = nullptr);
    ~CheckOut();
    Ui::CheckOut *ui;

    double balance;
    double total;
    QString purchased_items[50];
    std::map<QString, double> items_map;    // Map that holds the food name and price for both meat and chicken options.

    void set_purchased_items(QString[]);    // Setter for the array containing the items purchased.
    void set_items_map(std::map<QString, double>);
    void set_window();      // Setter for the checkout window.

private slots:
    void on_recharge_button_clicked();
    void on_place_order_button_clicked();
};

#endif // CHECKOUT_H
