#include "Product.h"

int Product::getProductId() const { return productId; }
int Product::getCategoryId() const { return categoryId; }
QString Product::getName() const { return name; }
double Product::getPrice() const { return price; }
QString Product::getImagePath() const { return imagePath; }

void Product::setProductId(int id) { productId = id; }
void Product::setCategoryId(int id) { categoryId = id; }
void Product::setName(const QString& n) { name = n; }
void Product::setPrice(double p) { price = p; }
void Product::setImagePath(const QString& path) { imagePath = path; }
