#pragma once
#include <vector>
#include "DTO/Product.h"
#include "DbConnection.h"
#include <QSqlError>
#include <QString>
using namespace std;

class ProductDAO {
private:
    static void quickSort(vector<Product>& arr, int left, int right);
    static int partition(vector<Product>& arr, int left, int right);
    static int binarySearchPrefix(const vector<Product>& arr, const QString& prefix);
public:
    // CRUD
    static vector<Product> getAll();
    static optional<Product> getById(int productId);
    static bool insert(const Product& p);
    static bool update(const Product& p);
    static bool remove(int productId);


    // Search
    static vector<Product> searchByName(const QString& keyword);
};
