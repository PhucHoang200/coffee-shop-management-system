#pragma once
#include <vector>
#include <optional>
#include "DTO/Inventory.h"

class InventoryDAO {
public:
    static std::vector<Inventory> getAll();
    static std::optional<Inventory> getById(int id);
    static std::optional<Inventory> getByIngredientId(int ingredientId);
    static bool insert(const Inventory& inv);
    static bool update(const Inventory& inv);
    static bool remove(int id);
};
