#include "Ingredient.h"

int Ingredient::getIngredientId() const { return ingredientId; }
QString Ingredient::getName() const { return name; }
QString Ingredient::getUnit() const { return unit; }
double Ingredient::getCostPerUnit() const { return costPerUnit; }

void Ingredient::setIngredientId(int id) { ingredientId = id; }
void Ingredient::setName(const QString& n) { name = n; }
void Ingredient::setUnit(const QString& u) { unit = u; }
void Ingredient::setCostPerUnit(double c) { costPerUnit = c; }
