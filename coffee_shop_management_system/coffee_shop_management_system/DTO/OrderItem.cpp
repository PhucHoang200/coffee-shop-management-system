#include "OrderItem.h"

int OrderItem::getOrderItemId() const { return orderItemId; }
int OrderItem::getOrderId() const { return orderId; }
int OrderItem::getProductId() const { return productId; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getUnitPrice() const { return unitPrice; }

void OrderItem::setOrderItemId(int id) { orderItemId = id; }
void OrderItem::setOrderId(int id) { orderId = id; }
void OrderItem::setProductId(int id) { productId = id; }
void OrderItem::setQuantity(int qty) { quantity = qty; }
void OrderItem::setUnitPrice(double price) { unitPrice = price; }
