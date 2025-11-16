#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>

class Ingredient {
private:
    int ingredientId;
    QString name;
    QString unit;
    double costPerUnit;

public:
    Ingredient() = default;

    int getIngredientId() const;
    QString getName() const;
    QString getUnit() const;
    double getCostPerUnit() const;

    void setIngredientId(int id);
    void setName(const QString& n);
    void setUnit(const QString& u);
    void setCostPerUnit(double c);
};

#endif
