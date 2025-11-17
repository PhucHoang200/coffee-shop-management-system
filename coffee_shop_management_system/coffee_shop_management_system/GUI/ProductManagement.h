#pragma once

#include <QWidget>
#include "ui_ProductManagement.h"

class ProductManagement : public QWidget
{
	Q_OBJECT

public:
	ProductManagement(QWidget *parent = nullptr);
	~ProductManagement();

private:
	Ui::ProductManagementClass ui;
	void loadProductsGrid();
	void onEditProduct(int id);
	void onDeleteProduct(int id);
};

