#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H

#include "DTO/Category.h"

class CategoryService
{
public:
    static Category getCategoryById(int id);
};

#endif
