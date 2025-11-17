#pragma once
#include <vector>
#include <optional>
#include <QString>
#include "DTO/Category.h"

class CategoryDAO {
public:
    static std::vector<Category> getAll();
    static std::optional<Category> getById(int id);
    static std::optional<Category> getByName(const QString& name);
    static bool insert(const Category& c);
    static bool update(const Category& c);
    static bool remove(int id);
};
