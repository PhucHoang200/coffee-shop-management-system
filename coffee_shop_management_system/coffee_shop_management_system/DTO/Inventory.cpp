#include "Inventory.h"

int Inventory::getInventoryId() const { return inventoryId; }
int Inventory::getIngredientId() const { return ingredientId; }
double Inventory::getQuantity() const { return quantity; }

void Inventory::setInventoryId(int id) { inventoryId = id; }
void Inventory::setIngredientId(int id) { ingredientId = id; }
void Inventory::setQuantity(double qty) { quantity = qty; }
