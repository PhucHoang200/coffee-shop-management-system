    #ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include <vector>
#include <QString>
#include "DTO/Product.h"

using namespace std;

class ProductService {
public:
    static vector<Product> getAllProducts();
    static optional<Product> getProduct(int productId);
    static bool addProduct(const Product& p);
    static bool updateProduct(const Product& p);
    static bool deleteProduct(int productId);

    // Search dùng DSA (QuickSort + BinarySearch)
    static vector<Product> searchProducts(const QString& keyword);
};

#endif // PRODUCTSERVICE_H