#include "homepage.h"
#include "ui_homepage.h"
#include "checkout.h"
#include <QVBoxLayout>


// Initializing arrays with food names
QString HomePage::meat_foods_names[8] = { "Meat Shawerma", "Steak", "Tacos", "Barbecue Ribs", "Roast Beef", "Lamb Chops", "Meatloaf", "Meat burger"};
QString HomePage::chicken_foods_names[8] = { "Chicken Curry", "Fried Chicken and White Rice", "Chicken Wings", "Chicken burger", "Chicken Teriyaki", "Chicken Shawarma", "Chicken Adobo", "Chicken Satay" };

// Initializing arrays with food prices
double HomePage::meat_prices[8] = {189, 120, 160, 100, 170, 210, 195, 97};
double HomePage::chicken_prices[8] = {126, 138, 112, 123, 115, 114, 115, 89};


HomePage::HomePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomePage)

{
    ui->setupUi(this);

    // Setting cart icon in home page
    QPixmap icon_path(":/pictures/cart.png");
    ui->cart_icon->setPixmap(icon_path);

    // Creating layouts for the meat and chicken scrolla areas
    QHBoxLayout* meat_layout = new QHBoxLayout();
    QHBoxLayout* chicken_layout = new QHBoxLayout();

    // Method that displays the item name, price, picture and button in each layout (widget inside scroll area)
    display_options(meat_layout, ui->meat_scroll_area, meat_foods_names, meat_prices);
    display_options(chicken_layout, ui->chicken_scroll_area, chicken_foods_names, chicken_prices);

    // Connecting method that adds item details to the cart scroll area to the "add to cart" button
    connect(ui->checkout, &QPushButton::clicked, this, &HomePage::on_checkout_clicked);

    // Connecting the method that closes all windows once the checkout window is closed
    connect(checkout_page, &QDialog::finished, this, &QApplication::closeAllWindows);

    // Setting style sheet for tab widget so that the tabs aren't visible
    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 0; height: 0; margin: 0; padding: 0; border: none; }");
    ui->tabWidget->hide();
    ui->tabWidget->removeTab(1);

}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::set_labels() {

    ui->balance_label->setText("LE " + QString::number(balance));
    ui->username_label->setText("WELCOME BACK " + username.toUpper());
}

// Methods that adds the item selected to the cart scroll area
void HomePage::add_cart(QPushButton* button, QString food_name, double price) {

connect(button, &QPushButton::clicked, [=]() {

    // Incrementing the label that holds the number of items in the cart
    int current_items = ui->items_cart->text().toInt();
    ui->items_cart->setText(QString::number(current_items + 1));

    /***** CART SCROLL AREA *****/

    // Casting the layout of the scroll area to a QVBoxLayout pointer
    QVBoxLayout* scroll_area_layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaCart_5->layout());
    // Box layout that will hold the label and the remove button so that they're displayed next to each other
    QHBoxLayout* layout = new QHBoxLayout();
    // Creating components for the scroll area
    QLabel* name_label = new QLabel(food_name);
    QLabel* price_label = new QLabel("LE " + QString::number(price));
    QPushButton* remove_button = new QPushButton("-");

    // Creating a layout in case the scroll area layout is pointing to none
    if (!scroll_area_layout) {
        scroll_area_layout = new QVBoxLayout(ui->scrollAreaCart_5);
        ui->scrollAreaCart_5->setLayout(scroll_area_layout);
    }

    // Setting the stylesheet and alignment for the labels
    name_label->setStyleSheet("background-color:white; color:black; font:700 14pt \"Helvetica\";");
    price_label->setStyleSheet("background-color:white; color:black;font:700 14pt \"Helvetica\";");
    remove_button->setStyleSheet("color:black; border-radius:4px;border:2px solid black;font:700 14pt \"Helvetica\";");

    price_label->setAlignment(Qt::AlignCenter);
    remove_button->setFixedSize(20,20);

    // Function that removes the components of the item in the scroll area if the removed button is pushed
    connect(remove_button, &QPushButton::clicked, [=]() {

        for (int i = 0; i < sizeof(items_added)/sizeof(items_added[0]); i++) {
            if (items_added[i] == food_name) {
                items_added[i] = "";
                break;
            }
        }

    // Removing components from scroll area
    scroll_area_layout->removeWidget(name_label);
    delete name_label;

    scroll_area_layout->removeWidget(price_label);
    delete price_label;

    scroll_area_layout->removeWidget(remove_button);
    delete remove_button;

    // Subtracting the item price from the total (variable that holds the sum of the items added to the cart)
    total -= price;

    // Once the item is deleted, we have to decrement the number of items in the cart.
    int current_items = ui->items_cart->text().toInt();
    ui->items_cart->setText(QString::number(current_items - 1));
    });

    // Adding cart components to the box layout
    layout->setAlignment(Qt::AlignLeft);
    layout->addWidget(name_label);
    layout->addWidget(price_label);
    layout->addWidget(remove_button);

    // Adding box layout to scroll area layout
    scroll_area_layout->addLayout(layout);
    scroll_area_layout->setAlignment(Qt::AlignTop);

    // Items_added is a list<QString> that holds the items the user adds to the cart so I can later use them in the checkout page.
    for (int i = 0; i < 50; i++) {
        if (items_added[i] == "") {
            items_added[i] = food_name;
            break;
        }
    }

    // Adding the price of the item to the total.
    total += price;
    });

}

// Method that displays food names, prices and button to add product.
void HomePage::display_options(QHBoxLayout* layout, QScrollArea* scrollArea, QString label_array[], double price_array[]) {

    for (int i = 0; i < 8; i++) {
        // Setting vertical scroll bar off so you can only scroll horizontally.
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Creating components
        QVBoxLayout* box_layout = new QVBoxLayout();

        QLabel* food_name = new QLabel(label_array[i]);
        QLabel* food_price = new QLabel("LE" + QString::number(price_array[i]));
        QLabel* food_picture = new QLabel();
        QPushButton* button = new QPushButton("Add to cart");

        // Setting label style sheet, alignment and size.
        food_name->setStyleSheet("background-color:rgb(196, 204, 214); color:black;border:0px;font:700 13pt \"Helvetica\"");
        food_name->setFixedSize(341, 20);
        food_name->setAlignment(Qt::AlignLeft);

        food_price->setStyleSheet("background-color:rgb(196, 204, 214); color:black;border:0px;font:700 13pt \"Helvetica\"");
        food_price->setFixedSize(341, 20);
        food_price->setAlignment(Qt::AlignLeft);

        food_picture->setStyleSheet("border:0px;");
        food_picture->setFixedSize(341, 231);

        button->setStyleSheet("color:black;border:1px solid black;background-color:white;font:700 15pt \"Times New Roman\"");
        button->setFixedSize(155, 35);

        // Adding the picture to food_picture label
        QString path = ":/pictures/";
        QPixmap picture(path + label_array[i] + ".jpg");
        food_picture->setPixmap(picture);

        // Connecting the "Add to Cart" button to the "add to cart" method.
        HomePage::add_cart(button, label_array[i], price_array[i]);

        // Adding components to the box layout
        box_layout->setAlignment(Qt::AlignCenter);
        box_layout->addWidget(food_picture);
        box_layout->addWidget(food_name);
        box_layout->addWidget(food_price);
        box_layout->addWidget(button);

        // Adding box layout to the main layout
        layout->setAlignment(Qt::AlignCenter);
        layout->addLayout(box_layout);

        // Creating a widget that will hold the box containing the button and the labels and putting it on the scroll area.
        QWidget* box_widget = new QWidget();
        box_widget->setLayout(layout);

        // Setting the box widget as the scroll area's content widget.
        scrollArea->setWidget(box_widget);
    }
}

void HomePage::on_checkout_clicked() {
    // Checking if the items_added array is empty
    bool has_items = std::any_of(std::begin(items_added), std::end(items_added), [](const QString& str) {
        return !str.isEmpty();});

    if (!has_items) {
        // Displaying an error message if the array is empty
        ui->empty_cart_message->setText("Please make sure you add items to your cart first");
        ui->empty_cart_message->show();
    } else {
        // Hiding the error message if the array isn't empty and passing homepage data to the checkout page
        ui->empty_cart_message->hide();
        checkout_page->balance = balance;
        checkout_page->total = total;
        checkout_page->set_purchased_items(items_added);
        checkout_page->set_items_map(items_map);
        checkout_page->set_window();

        // Open checkout page
        checkout_page->show();

    }

}

void HomePage::on_show_cart_clicked() {

        if (ui->tabWidget->isVisible()) {
            // If the tab widget is visible, we change the label to "+" and we hide it
            ui->show_cart->setText("+");
            ui->tabWidget->hide();

        } else {
            // If the tab widget is not visible, we change the label to "-" and we show it
            ui->show_cart->setText("-");
            ui->tabWidget->show();
        }
}

