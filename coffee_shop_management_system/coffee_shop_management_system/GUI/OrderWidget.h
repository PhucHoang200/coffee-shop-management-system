#pragma once

#include <QWidget>
#include "ui_OrderWidget.h"

class OrderWidget : public QWidget
{
	Q_OBJECT

public:
	OrderWidget(QWidget *parent = nullptr);
	~OrderWidget();

private:
	Ui::OrderWidgetClass ui;
};

