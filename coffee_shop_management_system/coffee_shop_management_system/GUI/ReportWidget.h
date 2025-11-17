#pragma once

#include <QWidget>
#include "ui_ReportWidget.h"

class ReportWidget : public QWidget
{
	Q_OBJECT

public:
	ReportWidget(QWidget *parent = nullptr);
	~ReportWidget();

private:
	Ui::ReportWidgetClass ui;
};

