#pragma once
#include <vector>
#include <optional>
#include "DTO/OrderItem.h"

class OrderItemDAO {
public:
    static std::vector<OrderItem> getAll();
    static std::vector<OrderItem> getByOrderId(int orderId);
    static std::optional<OrderItem> getById(int id);
    static bool insert(const OrderItem& item);
    static bool update(const OrderItem& item);
    static bool remove(int id);
    static bool removeByOrderId(int orderId); // tiện dụng khi xóa hóa đơn
};
