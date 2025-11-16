#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {
private:
    int inventoryId;
    int ingredientId;
    double quantity;

public:
    Inventory() = default;

    int getInventoryId() const;
    int getIngredientId() const;
    double getQuantity() const;

    void setInventoryId(int id);
    void setIngredientId(int id);
    void setQuantity(double qty);
};

#endif
