#include "OrderItemDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "DbConnection.h"

using namespace std;

vector<OrderItem> OrderItemDAO::getAll() {
    vector<OrderItem> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT OrderItemID, OrderID, ProductID, Quantity, UnitPrice "
        "FROM OrderItems ORDER BY OrderItemID"
    )) {
        qDebug() << "OrderItemsDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        OrderItem oi;
        oi.setOrderItemId(q.value("OrderItemID").toInt());
        oi.setOrderId(q.value("OrderID").toInt());
        oi.setProductId(q.value("ProductID").toInt());
        oi.setQuantity(q.value("Quantity").toInt());
        oi.setUnitPrice(q.value("UnitPrice").toDouble());
        list.push_back(oi);
    }

    return list;
}

vector<OrderItem> OrderItemDAO::getByOrderId(int orderId) {
    vector<OrderItem> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT OrderItemID, OrderID, ProductID, Quantity, UnitPrice "
        "FROM OrderItems WHERE OrderID = :oid ORDER BY OrderItemID"
    );
    q.bindValue(":oid", orderId);

    if (!q.exec()) {
        qDebug() << "OrderItemsDAO.getByOrderId error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        OrderItem oi;
        oi.setOrderItemId(q.value("OrderItemID").toInt());
        oi.setOrderId(q.value("OrderID").toInt());
        oi.setProductId(q.value("ProductID").toInt());
        oi.setQuantity(q.value("Quantity").toInt());
        oi.setUnitPrice(q.value("UnitPrice").toDouble());
        list.push_back(oi);
    }

    return list;
}

optional<OrderItem> OrderItemDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT OrderItemID, OrderID, ProductID, Quantity, UnitPrice "
        "FROM OrderItems WHERE OrderItemID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "OrderItemsDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        OrderItem oi;
        oi.setOrderItemId(q.value("OrderItemID").toInt());
        oi.setOrderId(q.value("OrderID").toInt());
        oi.setProductId(q.value("ProductID").toInt());
        oi.setQuantity(q.value("Quantity").toInt());
        oi.setUnitPrice(q.value("UnitPrice").toDouble());
        return oi;
    }

    return nullopt;
}

bool OrderItemDAO::insert(const OrderItem& item) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO OrderItems (OrderID, ProductID, Quantity, UnitPrice) "
        "VALUES (:oid, :pid, :qty, :price)"
    );
    q.bindValue(":oid", item.getOrderId());
    q.bindValue(":pid", item.getProductId());
    q.bindValue(":qty", item.getQuantity());
    q.bindValue(":price", item.getUnitPrice());

    if (!q.exec()) {
        qDebug() << "OrderItemsDAO.insert error:" << q.lastError().text();
        return false;
    }

    return true;
}

bool OrderItemDAO::update(const OrderItem& item) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE OrderItems SET "
        "OrderID = :oid, ProductID = :pid, Quantity = :qty, UnitPrice = :price "
        "WHERE OrderItemID = :id"
    );
    q.bindValue(":oid", item.getOrderId());
    q.bindValue(":pid", item.getProductId());
    q.bindValue(":qty", item.getQuantity());
    q.bindValue(":price", item.getUnitPrice());
    q.bindValue(":id", item.getOrderItemId());

    if (!q.exec()) {
        qDebug() << "OrderItemsDAO.update error:" << q.lastError().text();
        return false;
    }

    return true;
}

bool OrderItemDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM OrderItems WHERE OrderItemID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "OrderItemsDAO.remove error:" << q.lastError().text();
        return false;
    }

    return true;
}

bool OrderItemDAO::removeByOrderId(int orderId) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM OrderItems WHERE OrderID = :oid");
    q.bindValue(":oid", orderId);

    if (!q.exec()) {
        qDebug() << "OrderItemsDAO.removeByOrderId error:" << q.lastError().text();
        return false;
    }

    return true;
}
