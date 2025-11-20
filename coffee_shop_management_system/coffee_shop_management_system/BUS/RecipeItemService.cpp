#include "RecipeItemService.h"
#include "DAL/RecipeItemDAO.h"
#include "DAL/IngredientDAO.h"
#include <QDebug>

vector<RecipeItem> RecipeItemService::getAllRecipeItems() {
    return RecipeItemDAO::getAll();
}

optional<RecipeItem> RecipeItemService::getRecipeItem(int id) {
    if (id <= 0) return nullopt;
    return RecipeItemDAO::getById(id);
}

vector<RecipeItem> RecipeItemService::getRecipeItemsByProduct(int productId) {
    if (productId <= 0) return {};
    return RecipeItemDAO::getByProductId(productId);
}

bool RecipeItemService::addRecipeItem(const RecipeItem& item) {
    // Business rules:
    if (item.getProductId() <= 0) return false;
    if (item.getIngredientId() <= 0) return false;
    if (item.getQuantityPerUnit() <= 0) return false;

    return RecipeItemDAO::insert(item);
}

bool RecipeItemService::updateRecipeItem(const RecipeItem& item) {
    if (item.getRecipeItemId() <= 0) return false;
    if (item.getProductId() <= 0) return false;
    if (item.getIngredientId() <= 0) return false;
    if (item.getQuantityPerUnit() <= 0) return false;

    return RecipeItemDAO::update(item);
}

bool RecipeItemService::deleteRecipeItem(int id) {
    if (id <= 0) return false;
    return RecipeItemDAO::remove(id);
}

vector<RecipeItem> RecipeItemService::searchByIngredientId(int ingredientId) {
    vector<RecipeItem> all = RecipeItemDAO::getAll();
    vector<RecipeItem> result;

    for (const RecipeItem& ri : all) {
        if (ri.getIngredientId() == ingredientId)
            result.push_back(ri);
    }

    return result;
}

double RecipeItemService::calculateCostForProduct(int productId) {
    if (productId <= 0) return 0;

    // Lấy tất cả nguyên liệu của sản phẩm
    vector<RecipeItem> items = RecipeItemDAO::getByProductId(productId);

    double total = 0;

    for (const RecipeItem& item : items) {

        // 1. Lấy ingredient từ DAL
        auto optIng = IngredientDAO::getById(item.getIngredientId());
        if (!optIng.has_value()) continue;

        // 2. Lấy giá costPerUnit từ DTO Ingredient
        double unitPrice = optIng->getCostPerUnit();

        // 3. Tính giá vốn
        total += item.getQuantityPerUnit() * unitPrice;
    }

    return total;
}

