#include "CategoryService.h"
#include "DAL/CategoryDAO.h"
#include <QDebug>

vector<Category> CategoryService::getAllCategories() {
    return CategoryDAO::getAll();
}

optional<Category> CategoryService::getCategory(int categoryId) {
    if (categoryId <= 0) return nullopt;
    return CategoryDAO::getById(categoryId);
}

optional<Category> CategoryService::getCategoryByName(const QString& name) {
    if (name.trimmed().isEmpty()) return nullopt;
    return CategoryDAO::getByName(name);
}

bool CategoryService::addCategory(const Category& c) {
    // Business rules
    if (c.getName().trimmed().isEmpty()) return false;

    // Kiểm tra trùng tên category
    auto exists = CategoryDAO::getByName(c.getName());
    if (exists.has_value()) {
        qDebug() << "CategoryService.addCategory: duplicate name";
        return false;
    }

    return CategoryDAO::insert(c);
}

bool CategoryService::updateCategory(const Category& c) {
    if (c.getCategoryId() <= 0) return false;
    if (c.getName().trimmed().isEmpty()) return false;

    // Kiểm tra trùng tên category (trừ chính nó)
    auto exists = CategoryDAO::getByName(c.getName());
    if (exists.has_value() && exists->getCategoryId() != c.getCategoryId()) {
        qDebug() << "CategoryService.updateCategory: duplicate name";
        return false;
    }

    return CategoryDAO::update(c);
}

bool CategoryService::deleteCategory(int categoryId) {
    if (categoryId <= 0) return false;

    return CategoryDAO::remove(categoryId);
}

vector<Category> CategoryService::searchCategories(const QString& keyword) {
    if (keyword.trimmed().isEmpty())
        return CategoryDAO::getAll();

    vector<Category> all = CategoryDAO::getAll();
    vector<Category> result;

    QString key = keyword.trimmed().toLower();

    for (const Category& c : all) {
        if (c.getName().toLower().contains(key)) {
            result.push_back(c);
        }
    }

    return result;
}
