#ifndef RECIPEITEMSERVICE_H
#define RECIPEITEMSERVICE_H

#include <vector>
#include <optional>
#include "DTO/RecipeItem.h"

using namespace std;

class RecipeItemService {
public:
    static vector<RecipeItem> getAllRecipeItems();
    static optional<RecipeItem> getRecipeItem(int id);
    static vector<RecipeItem> getRecipeItemsByProduct(int productId);

    static bool addRecipeItem(const RecipeItem& item);
    static bool updateRecipeItem(const RecipeItem& item);
    static bool deleteRecipeItem(int id);

    // Optional: Search dùng DSA (nếu sau này bạn muốn)
    static vector<RecipeItem> searchByIngredientId(int ingredientId);
};

#endif // RECIPEITEMSERVICE_H
