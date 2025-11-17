#pragma once

#include <QWidget>
#include "ui_HomeWidget.h"

class HomeWidget : public QWidget
{
	Q_OBJECT

public:
	HomeWidget(QWidget *parent = nullptr);
	~HomeWidget();

private:
	Ui::HomeWidgetClass ui;
};

