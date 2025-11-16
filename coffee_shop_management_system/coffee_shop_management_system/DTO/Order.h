#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDateTime>

class Order {
private:
    int orderId;
    QString customerName;
    QString customerPhone;
    QDateTime createdAt;
    double total;

public:
    Order() = default;

    int getOrderId() const;
    QString getCustomerName() const;
    QString getCustomerPhone() const;
    QDateTime getCreatedAt() const;
    double getTotal() const;

    void setOrderId(int id);
    void setCustomerName(const QString& name);
    void setCustomerPhone(const QString& phone);
    void setCreatedAt(const QDateTime& dt);
    void setTotal(double t);
};

#endif
