#pragma once

#include <QWidget>
#include "ui_OrderManagement.h"

class OrderManagement : public QWidget
{
	Q_OBJECT

public:
	OrderManagement(QWidget *parent = nullptr);
	~OrderManagement();

private:
	Ui::OrderManagementClass ui;
};

