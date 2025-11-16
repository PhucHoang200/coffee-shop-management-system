#include "Order.h"

int Order::getOrderId() const { return orderId; }
QString Order::getCustomerName() const { return customerName; }
QString Order::getCustomerPhone() const { return customerPhone; }
int Order::getTableId() const { return tableId; }
int Order::getCreatedBy() const { return createdBy; }
QDateTime Order::getCreatedAt() const { return createdAt; }
QString Order::getStatus() const { return status; }
double Order::getTotal() const { return total; }

void Order::setOrderId(int id) { orderId = id; }
void Order::setCustomerName(const QString& name) { customerName = name; }
void Order::setCustomerPhone(const QString& phone) { customerPhone = phone; }
void Order::setTableId(int id) { tableId = id; }
void Order::setCreatedBy(int id) { createdBy = id; }
void Order::setCreatedAt(const QDateTime& dt) { createdAt = dt; }
void Order::setStatus(const QString& st) { status = st; }
void Order::setTotal(double t) { total = t; }
