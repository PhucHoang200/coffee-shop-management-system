#pragma once

#include <QWidget>
#include "ui_InventoryWidget.h"

class InventoryWidget : public QWidget
{
	Q_OBJECT

public:
	InventoryWidget(QWidget *parent = nullptr);
	~InventoryWidget();

private:
	Ui::InventoryWidgetClass ui;
};

