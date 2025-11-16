#include "Category.h"

int Category::getCategoryId() const { return categoryId; }
QString Category::getName() const { return name; }
QString Category::getDescription() const { return description; }

void Category::setCategoryId(int id) { categoryId = id; }
void Category::setName(const QString& n) { name = n; }
void Category::setDescription(const QString& desc) { description = desc; }
