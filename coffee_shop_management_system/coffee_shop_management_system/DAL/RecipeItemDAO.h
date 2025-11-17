#pragma once
#include <vector>
#include <optional>
#include "DTO/RecipeItem.h"

class RecipeItemDAO {
public:
    static std::vector<RecipeItem> getAll();
    static std::optional<RecipeItem> getById(int id);
    static std::vector<RecipeItem> getByProductId(int productId);
    static bool insert(const RecipeItem& item);
    static bool update(const RecipeItem& item);
    static bool remove(int id);
};
