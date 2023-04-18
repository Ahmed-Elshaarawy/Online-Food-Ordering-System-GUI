#include "signin.h"
#include "ui_signin.h"
#include "homepage.h"

SignIn::SignIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);

    // Setting icon in sign in page
    QPixmap icon_path(":/pictures/user.png");
    ui->icon->setPixmap(icon_path);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_SigninButton_clicked()
{
    // Get the username and password entered by the user
    QString username = ui->username->text();
    QString password = ui->password->text();

    bool username_found = false;     // Flag that signals wheather or not the username is found in the array

    // Loop through the array of usernames
    for (int i = 0; i < 5; i++) {

        if (username_array[i] == username) {
            username_found = true;

            if (password_array[i] == password) {

                // Display message and balance if both username and password were found in the arays
                ui->message_label->setText("Login successfuly");
                ui->balance_label->setText("LE " + QString::number(balance_array[i]));

                // Create pointer to homepage class
                HomePage *homepage = new HomePage(this);

                // Set the variables in the homepage class to the values in this class
                homepage->balance = balance_array[i];
                homepage->username = username_array[i];
                homepage->set_labels();

                // Open window
                homepage->show();

            } else {
                // If username is correct but password isn't display error message
                ui->message_label->setText("Password is incorrect");
                break;
            }
        }
    }

    if (!username_found) {
        // If username is not found in the array (doesn't exist) display error message
        ui->message_label->setText("Username is incorrect");
    }
}
