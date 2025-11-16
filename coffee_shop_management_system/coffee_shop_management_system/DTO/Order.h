#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDateTime>

class Order {
private:
    int orderId;
    QString customerName;
    QString customerPhone;
    int tableId;
    int createdBy;
    QDateTime createdAt;
    QString status;
    double total;

public:
    Order() = default;

    int getOrderId() const;
    QString getCustomerName() const;
    QString getCustomerPhone() const;
    int getTableId() const;
    int getCreatedBy() const;
    QDateTime getCreatedAt() const;
    QString getStatus() const;
    double getTotal() const;

    void setOrderId(int id);
    void setCustomerName(const QString& name);
    void setCustomerPhone(const QString& phone);
    void setTableId(int id);
    void setCreatedBy(int id);
    void setCreatedAt(const QDateTime& dt);
    void setStatus(const QString& st);
    void setTotal(double t);
};

#endif
