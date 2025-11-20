#include "ProductService.h"
#include "DAL/ProductDAO.h"
#include <QDebug>

vector<Product> ProductService::getAllProducts() {
    return ProductDAO::getAll();
}

optional<Product> ProductService::getProduct(int productId) {
    return ProductDAO::getById(productId);
}

bool ProductService::addProduct(const Product& p) {
    // Business rules example: name not empty, price positive
    if (p.getName().trimmed().isEmpty()) return false;
    if (p.getPrice() < 0) return false;
    return ProductDAO::insert(p);
}

bool ProductService::updateProduct(const Product& p) {
    if (p.getProductId() <= 0) return false;
    if (p.getName().trimmed().isEmpty()) return false;
    if (p.getPrice() < 0) return false;
    return ProductDAO::update(p);
}

bool ProductService::deleteProduct(int productId) {
    if (productId <= 0) return false;
    return ProductDAO::remove(productId);
}

vector<Product> ProductService::searchProducts(const QString& keyword) {
    return ProductDAO::searchByName(keyword);
}

vector<Product> ProductService::getProductsByCategory(int categoryId) {
    return ProductDAO::getByCategory(categoryId);
}
