#include "signin.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SignIn w;
    w.show();
    return a.exec();
}

