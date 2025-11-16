#pragma once
#include <vector>
#include "DTO/Product.h"
#include "DbConnection.h"
#include <QSqlError>
#include <QString>
using namespace std;

class ProductDAO {
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
