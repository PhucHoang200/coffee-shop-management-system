#pragma once
#include <vector>
#include <optional>
#include <QString>
#include "DTO/Role.h"

class RolesDAO {
public:
    static std::vector<Role> getAll();
    static std::optional<Role> getById(int id);
    static bool insert(const Role& r);
    static bool update(const Role& r);
    static bool remove(int id);
};
