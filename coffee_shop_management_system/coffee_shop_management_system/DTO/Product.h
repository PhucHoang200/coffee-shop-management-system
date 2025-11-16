#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product {
private:
    int productId;
    int categoryId;
    QString name;
    double price;
    QString imagePath;

public:
    Product() = default;

    int getProductId() const;
    int getCategoryId() const;
    QString getName() const;
    double getPrice() const;
    QString getImagePath() const;

    void setProductId(int id);
    void setCategoryId(int id);
    void setName(const QString& n);
    void setPrice(double p);
    void setImagePath(const QString& path);
};

#endif
