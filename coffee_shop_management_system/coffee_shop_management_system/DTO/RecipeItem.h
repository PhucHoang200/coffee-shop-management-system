#ifndef RECIPEITEM_H
#define RECIPEITEM_H

class RecipeItem {
private:
    int recipeItemId;
    int productId;
    int ingredientId;
    double quantityPerUnit;

public:
    RecipeItem() = default;

    int getRecipeItemId() const;
    int getProductId() const;
    int getIngredientId() const;
    double getQuantityPerUnit() const;

    void setRecipeItemId(int id);
    void setProductId(int id);
    void setIngredientId(int id);
    void setQuantityPerUnit(double qty);
};

#endif
