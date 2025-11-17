#pragma once
#include <vector>
#include <optional>
#include <QString>
#include "DTO/Ingredient.h"

class IngredientDAO {
public:
    static std::vector<Ingredient> getAll();
    static std::optional<Ingredient> getById(int id);
    static std::optional<Ingredient> getByName(const QString& name);
    static bool insert(const Ingredient& ing);
    static bool update(const Ingredient& ing);
    static bool remove(int id);
};
