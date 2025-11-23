#pragma once

#include <QWidget>
#include "ui_HomeWidget.h"

class HomeWidget : public QWidget
{
	Q_OBJECT

public:
	HomeWidget(QWidget *parent = nullptr);
	~HomeWidget();
	void resetMenuButtons();

private:
	Ui::HomeWidgetClass ui;
	std::vector<QPushButton*> buttons;

signals:
	void navigateToPage(int index);

};

