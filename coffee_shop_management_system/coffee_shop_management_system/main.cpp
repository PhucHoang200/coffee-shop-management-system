#include "coffee_shop_management_system.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    coffee_shop_management_system window;
    window.show();
    return app.exec();
}
