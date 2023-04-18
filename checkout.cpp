#include "ui_checkout.h"
#include "checkout.h"
#include<iostream>
#include<QVBoxLayout>


CheckOut::CheckOut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOut)
{
    ui->setupUi(this);

}

CheckOut::~CheckOut()
{
    delete ui;
}

void CheckOut::set_window() {

    this->setWindowTitle("Checkout");

    QVBoxLayout* layout = new QVBoxLayout;

    // Looping through the items in the purchased_items array
    for (auto const& item : purchased_items) {

        if(item != nullptr) {

            QHBoxLayout* box_layout = new QHBoxLayout();

            // Create a label for the item name and price
            QLabel* food_name = new QLabel(item);
            QLabel* food_price = new QLabel("LE " + QString::number(items_map[item]));

            // Setting the style sheets for the labels
            food_name->setStyleSheet("background-color:white; color:black; font:700 15pt \"helvica\";");
            food_price->setStyleSheet("background-color:white; color:black;font:700 15pt \"helvica\";");
            food_price->setAlignment(Qt::AlignRight);


            box_layout->addWidget(food_name);
            box_layout->addWidget(food_price);

            layout->addLayout(box_layout);
            layout->setAlignment(Qt::AlignTop);
            continue;

        }
    }

    ui->checkout_scrollarea->setLayout(layout);
    this->ui->items_in_cart->setWidget(ui->checkout_scrollarea);

    this->ui->total_label->setText("LE " + QString::number(total));
    this->ui->balance_label->setText("LE " + QString::number(balance));

}

void CheckOut::set_purchased_items(QString array[]) {
    for (int i = 0; i < 50; i++){
            if (array[i].isEmpty()) {
                continue;
            }
            purchased_items[i] = array[i];
    }
}

void CheckOut::set_items_map(std::map<QString, double> map) {
    for (const auto& [item, price] : map) {
            items_map[item] = price;
    }
}

void CheckOut::on_recharge_button_clicked()
{
    double amount = ui->recharge_amount->text().toDouble();

    if (amount > 0) {
        balance += amount;
        ui->balance_label->setText("LE " + QString::number(balance));
        ui->message_label->hide();

    } else {
        ui->message_label->setText("Invalid amount.");
        ui->message_label->setStyleSheet("color:red;");
    }
}

void CheckOut::on_place_order_button_clicked()
{
    if (total > balance) {
        ui->message_label->setText("Sorry, you can't proceed without recharging your balance.");
        ui->message_label->show();
    } else {
        balance -= total;

        ui->total_label->setText("0");
        ui->balance_label->setText("LE" + QString::number(balance));

        ui->items_in_cart->takeWidget()->deleteLater();

        ui->message_label->show();
        ui->message_label->setText("Purchased Successfuly.Enjoy your meal.");
    }
}

