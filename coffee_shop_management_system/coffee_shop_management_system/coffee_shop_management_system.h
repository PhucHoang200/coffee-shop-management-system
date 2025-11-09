#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_coffee_shop_management_system.h"

class coffee_shop_management_system : public QMainWindow
{
    Q_OBJECT

public:
    coffee_shop_management_system(QWidget *parent = nullptr);
    ~coffee_shop_management_system();

private:
    Ui::coffee_shop_management_systemClass ui;
};

