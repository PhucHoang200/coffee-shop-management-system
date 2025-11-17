#pragma once
#include <vector>
#include <optional>
#include <QString>
#include "DTO/Order.h"

class OrderDAO {
public:
    static std::vector<Order> getAll();
    static std::optional<Order> getById(int id);
    static bool insert(const Order& o);
    static bool update(const Order& o);
    static bool remove(int id);
};
