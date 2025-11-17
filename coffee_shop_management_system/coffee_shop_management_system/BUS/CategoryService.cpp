#include "CategoryService.h"

Category CategoryService::getCategoryById(int id)
{
    Category c;
    c.setCategoryId(id);
    c.setName("Khong ro");

    return c;
}
