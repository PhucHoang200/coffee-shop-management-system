#pragma once
#include <QWidget>
#include "DTO/Product.h"

class ProductItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductItemWidget(const Product& product, QWidget* parent = nullptr);

private:
    Product m_product;
};
