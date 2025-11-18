#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H

#include <vector>
#include <optional>
#include <QString>
#include "DTO/Category.h"

using namespace std;

class CategoryService {
public:
    static vector<Category> getAllCategories();
    static optional<Category> getCategory(int categoryId);
    static optional<Category> getCategoryByName(const QString& name);

    static bool addCategory(const Category& c);
    static bool updateCategory(const Category& c);
    static bool deleteCategory(int categoryId);

    // Nếu bạn muốn sau này Search dùng DSA (QS + BS)
    static vector<Category> searchCategories(const QString& keyword);
};

#endif // CATEGORYSERVICE_H
