#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category {
private:
    int categoryId;
    QString name;
    QString description;

public:
    Category() = default;

    int getCategoryId() const;
    QString getName() const;
    QString getDescription() const;

    void setCategoryId(int id);
    void setName(const QString& name);
    void setDescription(const QString& desc);
};

#endif
