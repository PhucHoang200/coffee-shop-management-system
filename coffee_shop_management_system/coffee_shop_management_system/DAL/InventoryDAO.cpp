#include "InventoryDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "DbConnection.h"

using namespace std;

vector<Inventory> InventoryDAO::getAll() {
    vector<Inventory> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT InventoryID, IngredientID, Quantity "
        "FROM Inventory ORDER BY IngredientID"
    )) {
        qDebug() << "InventoryDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Inventory inv;
        inv.setInventoryId(q.value("InventoryID").toInt());
        inv.setIngredientId(q.value("IngredientID").toInt());
        inv.setQuantity(q.value("Quantity").toDouble());
        list.push_back(inv);
    }

    return list;
}

optional<Inventory> InventoryDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT InventoryID, IngredientID, Quantity "
        "FROM Inventory WHERE InventoryID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "InventoryDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Inventory inv;
        inv.setInventoryId(q.value("InventoryID").toInt());
        inv.setIngredientId(q.value("IngredientID").toInt());
        inv.setQuantity(q.value("Quantity").toDouble());
        return inv;
    }

    return nullopt;
}

optional<Inventory> InventoryDAO::getByIngredientId(int ingredientId) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT InventoryID, IngredientID, Quantity "
        "FROM Inventory WHERE IngredientID = :ing"
    );
    q.bindValue(":ing", ingredientId);

    if (!q.exec()) {
        qDebug() << "InventoryDAO.getByIngredientId error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Inventory inv;
        inv.setInventoryId(q.value("InventoryID").toInt());
        inv.setIngredientId(q.value("IngredientID").toInt());
        inv.setQuantity(q.value("Quantity").toDouble());
        return inv;
    }

    return nullopt;
}

bool InventoryDAO::insert(const Inventory& inv) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO Inventory (IngredientID, Quantity) "
        "VALUES (:ing, :qty)"
    );
    q.bindValue(":ing", inv.getIngredientId());
    q.bindValue(":qty", inv.getQuantity());

    if (!q.exec()) {
        qDebug() << "InventoryDAO.insert error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool InventoryDAO::update(const Inventory& inv) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE Inventory SET IngredientID = :ing, Quantity = :qty "
        "WHERE InventoryID = :id"
    );
    q.bindValue(":ing", inv.getIngredientId());
    q.bindValue(":qty", inv.getQuantity());
    q.bindValue(":id", inv.getInventoryId());

    if (!q.exec()) {
        qDebug() << "InventoryDAO.update error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool InventoryDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Inventory WHERE InventoryID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "InventoryDAO.remove error:" << q.lastError().text();
        return false;
    }
    return true;
}
