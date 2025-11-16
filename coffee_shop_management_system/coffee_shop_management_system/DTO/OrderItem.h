#ifndef ORDERITEM_H
#define ORDERITEM_H

class OrderItem {
private:
    int orderItemId;
    int orderId;
    int productId;
    int quantity;
    double unitPrice;

public:
    OrderItem() = default;

    int getOrderItemId() const;
    int getOrderId() const;
    int getProductId() const;
    int getQuantity() const;
    double getUnitPrice() const;

    void setOrderItemId(int id);
    void setOrderId(int id);
    void setProductId(int id);
    void setQuantity(int qty);
    void setUnitPrice(double price);
};

#endif
