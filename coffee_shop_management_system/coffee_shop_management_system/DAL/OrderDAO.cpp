#include "OrderDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "DbConnection.h"

using namespace std;

vector<Order> OrderDAO::getAll() {
    vector<Order> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT OrderID, CustomerName, CustomerPhone, CreatedAt, Total "
        "FROM Orders ORDER BY OrderID DESC"
    )) {
        qDebug() << "OrdersDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Order o;
        o.setOrderId(q.value("OrderID").toInt());
        o.setCustomerName(q.value("CustomerName").toString());
        o.setCustomerPhone(q.value("CustomerPhone").toString());
        o.setCreatedAt(q.value("CreatedAt").toDateTime());
        o.setTotal(q.value("Total").toDouble());
        list.push_back(o);
    }

    return list;
}

optional<Order> OrderDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT OrderID, CustomerName, CustomerPhone, CreatedAt, Total "
        "FROM Orders WHERE OrderID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "OrdersDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Order o;
        o.setOrderId(q.value("OrderID").toInt());
        o.setCustomerName(q.value("CustomerName").toString());
        o.setCustomerPhone(q.value("CustomerPhone").toString());
        o.setCreatedAt(q.value("CreatedAt").toDateTime());
        o.setTotal(q.value("Total").toDouble());
        return o;
    }

    return nullopt;
}

int OrderDAO::insert(const Order& o) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return -1; // trả về -1 nếu fail

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO Orders (CustomerName, CustomerPhone, Total) "
        "VALUES (:name, :phone, :total)"
    );

    q.bindValue(":name", o.getCustomerName());
    q.bindValue(":phone", o.getCustomerPhone());
    q.bindValue(":total", o.getTotal());

    if (!q.exec()) {
        qDebug() << "OrdersDAO.insert error:" << q.lastError().text();
        return -1;
    }

    return q.lastInsertId().toInt(); // <-- trả về OrderId mới
}

bool OrderDAO::update(const Order& o) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE Orders SET CustomerName = :name, CustomerPhone = :phone, "
        "Total = :total WHERE OrderID = :id"
    );

    q.bindValue(":name", o.getCustomerName());
    q.bindValue(":phone", o.getCustomerPhone());
    q.bindValue(":total", o.getTotal());
    q.bindValue(":id", o.getOrderId());

    if (!q.exec()) {
        qDebug() << "OrdersDAO.update error:" << q.lastError().text();
        return false;
    }

    return true;
}

bool OrderDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Orders WHERE OrderID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "OrdersDAO.remove error:" << q.lastError().text();
        return false;
    }

    return true;
}
