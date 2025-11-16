#include "Order.h"

int Order::getOrderId() const { return orderId; }
QString Order::getCustomerName() const { return customerName; }
QString Order::getCustomerPhone() const { return customerPhone; }
QDateTime Order::getCreatedAt() const { return createdAt; }
double Order::getTotal() const { return total; }

void Order::setOrderId(int id) { orderId = id; }
void Order::setCustomerName(const QString& name) { customerName = name; }
void Order::setCustomerPhone(const QString& phone) { customerPhone = phone; }
void Order::setCreatedAt(const QDateTime& dt) { createdAt = dt; }
void Order::setTotal(double t) { total = t; }
