#pragma once

#include <QWidget>
#include "ui_EmployeeWidget.h"

class EmployeeWidget : public QWidget
{
	Q_OBJECT

public:
	EmployeeWidget(QWidget *parent = nullptr);
	~EmployeeWidget();

private:
	Ui::EmployeeWidgetClass ui;
};

