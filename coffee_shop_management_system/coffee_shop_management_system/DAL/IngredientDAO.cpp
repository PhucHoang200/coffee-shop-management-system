#include "IngredientDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "DbConnection.h"

using namespace std;

vector<Ingredient> IngredientDAO::getAll() {
    vector<Ingredient> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT IngredientID, Name, Unit, CostPerUnit "
        "FROM Ingredients ORDER BY Name"
    )) {
        qDebug() << "IngredientsDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Ingredient ing;
        ing.setIngredientId(q.value("IngredientID").toInt());
        ing.setName(q.value("Name").toString());
        ing.setUnit(q.value("Unit").toString());
        ing.setCostPerUnit(q.value("CostPerUnit").toDouble());
        list.push_back(ing);
    }

    return list;
}

optional<Ingredient> IngredientDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT IngredientID, Name, Unit, CostPerUnit "
        "FROM Ingredients WHERE IngredientID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "IngredientsDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Ingredient ing;
        ing.setIngredientId(q.value("IngredientID").toInt());
        ing.setName(q.value("Name").toString());
        ing.setUnit(q.value("Unit").toString());
        ing.setCostPerUnit(q.value("CostPerUnit").toDouble());
        return ing;
    }

    return nullopt;
}

optional<Ingredient> IngredientDAO::getByName(const QString& name) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT IngredientID, Name, Unit, CostPerUnit "
        "FROM Ingredients WHERE Name = :name"
    );
    q.bindValue(":name", name);

    if (!q.exec()) {
        qDebug() << "IngredientsDAO.getByName error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Ingredient ing;
        ing.setIngredientId(q.value("IngredientID").toInt());
        ing.setName(q.value("Name").toString());
        ing.setUnit(q.value("Unit").toString());
        ing.setCostPerUnit(q.value("CostPerUnit").toDouble());
        return ing;
    }

    return nullopt;
}

bool IngredientDAO::insert(const Ingredient& ing) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO Ingredients (Name, Unit, CostPerUnit) "
        "VALUES (:name, :unit, :cost)"
    );
    q.bindValue(":name", ing.getName());
    q.bindValue(":unit", ing.getUnit());
    q.bindValue(":cost", ing.getCostPerUnit());

    if (!q.exec()) {
        qDebug() << "IngredientsDAO.insert error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool IngredientDAO::update(const Ingredient& ing) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE Ingredients SET Name = :name, Unit = :unit, CostPerUnit = :cost "
        "WHERE IngredientID = :id"
    );
    q.bindValue(":name", ing.getName());
    q.bindValue(":unit", ing.getUnit());
    q.bindValue(":cost", ing.getCostPerUnit());
    q.bindValue(":id", ing.getIngredientId());

    if (!q.exec()) {
        qDebug() << "IngredientsDAO.update error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool IngredientDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Ingredients WHERE IngredientID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "IngredientsDAO.remove error:" << q.lastError().text();
        return false;
    }
    return true;
}
