#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "./ui_homepage.h"
#include "checkout.h"
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class HomePage; }
QT_END_NAMESPACE

class HomePage : public QMainWindow
{
    Q_OBJECT

public:

    HomePage(QWidget *parent = nullptr);
    ~HomePage();
    HomePage(HomePage* other);

    CheckOut* checkout_page = new CheckOut(this);

    QString username;
    double balance;
    double total = 0;

    // Meat arrays
    static QString meat_foods_names[8];
    static double meat_prices[8];

    // Chicken arrays
    static QString chicken_foods_names[8];
    static double chicken_prices[8];

    // Array containing the items added to the cart
    QString items_added[50];

    // Map of item names and prices
    std::map<QString, double> items_map = {
                                           {"Meat Shawerma", 189}, {"Steak", 120}, {"Tacos", 160}, {"Barbecue Ribs", 100},
                                           {"Roast Beef", 170}, {"Lamb Chops", 210}, {"Meatloaf", 195},{"Meat burger", 97},
                                           {"Chicken Curry", 126}, {"Fried Chicken and White Rice", 138}, {"Chicken Wings", 112},
                                           {"Chicken burger", 123}, {"Chicken Teriyaki", 115}, {"Chicken Shawarma", 98},
                                           {"Chicken Adobo", 114}, {"Chicken Satay", 89}
    };

    void set_labels();

private slots:
    void on_checkout_clicked();   
    void on_show_cart_clicked();

private:

    Ui::HomePage *ui;
    void add_cart(QPushButton* button,  QString food_name, double price);
    void display_options(QHBoxLayout* layout, QScrollArea* scrollArea, QString label_array[], double price_array[]);

};
#endif // HOMEPAGE_H

