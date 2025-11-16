#include "RecipeItem.h"

int RecipeItem::getRecipeItemId() const { return recipeItemId; }
int RecipeItem::getProductId() const { return productId; }
int RecipeItem::getIngredientId() const { return ingredientId; }
double RecipeItem::getQuantityPerUnit() const { return quantityPerUnit; }

void RecipeItem::setRecipeItemId(int id) { recipeItemId = id; }
void RecipeItem::setProductId(int id) { productId = id; }
void RecipeItem::setIngredientId(int id) { ingredientId = id; }
void RecipeItem::setQuantityPerUnit(double qty) { quantityPerUnit = qty; }
