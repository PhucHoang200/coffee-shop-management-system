#include "RecipeItemDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "DbConnection.h"

using namespace std;

vector<RecipeItem> RecipeItemDAO::getAll() {
    vector<RecipeItem> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT RecipeItemID, ProductID, IngredientID, QuantityPerUnit "
        "FROM RecipeItems ORDER BY ProductID"
    )) {
        qDebug() << "RecipeItemsDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        RecipeItem ri;
        ri.setRecipeItemId(q.value("RecipeItemID").toInt());
        ri.setProductId(q.value("ProductID").toInt());
        ri.setIngredientId(q.value("IngredientID").toInt());
        ri.setQuantityPerUnit(q.value("QuantityPerUnit").toDouble());
        list.push_back(ri);
    }

    return list;
}

optional<RecipeItem> RecipeItemDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT RecipeItemID, ProductID, IngredientID, QuantityPerUnit "
        "FROM RecipeItems WHERE RecipeItemID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "RecipeItemsDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        RecipeItem ri;
        ri.setRecipeItemId(q.value("RecipeItemID").toInt());
        ri.setProductId(q.value("ProductID").toInt());
        ri.setIngredientId(q.value("IngredientID").toInt());
        ri.setQuantityPerUnit(q.value("QuantityPerUnit").toDouble());
        return ri;
    }

    return nullopt;
}

vector<RecipeItem> RecipeItemDAO::getByProductId(int productId) {
    vector<RecipeItem> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT RecipeItemID, ProductID, IngredientID, QuantityPerUnit "
        "FROM RecipeItems WHERE ProductID = :pid"
    );
    q.bindValue(":pid", productId);

    if (!q.exec()) {
        qDebug() << "RecipeItemsDAO.getByProductId error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        RecipeItem ri;
        ri.setRecipeItemId(q.value("RecipeItemID").toInt());
        ri.setProductId(q.value("ProductID").toInt());
        ri.setIngredientId(q.value("IngredientID").toInt());
        ri.setQuantityPerUnit(q.value("QuantityPerUnit").toDouble());
        list.push_back(ri);
    }

    return list;
}

bool RecipeItemDAO::insert(const RecipeItem& item) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO RecipeItems (ProductID, IngredientID, QuantityPerUnit) "
        "VALUES (:pid, :ing, :qty)"
    );

    q.bindValue(":pid", item.getProductId());
    q.bindValue(":ing", item.getIngredientId());
    q.bindValue(":qty", item.getQuantityPerUnit());

    if (!q.exec()) {
        qDebug() << "RecipeItemsDAO.insert error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool RecipeItemDAO::update(const RecipeItem& item) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE RecipeItems "
        "SET ProductID = :pid, IngredientID = :ing, QuantityPerUnit = :qty "
        "WHERE RecipeItemID = :id"
    );

    q.bindValue(":pid", item.getProductId());
    q.bindValue(":ing", item.getIngredientId());
    q.bindValue(":qty", item.getQuantityPerUnit());
    q.bindValue(":id", item.getRecipeItemId());

    if (!q.exec()) {
        qDebug() << "RecipeItemsDAO.update error:" << q.lastError().text();
        return false;
    }

    return true;
}

bool RecipeItemDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM RecipeItems WHERE RecipeItemID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "RecipeItemsDAO.remove error:" << q.lastError().text();
        return false;
    }
    return true;
}
