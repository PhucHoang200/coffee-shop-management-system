#include "CategoryDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "DbConnection.h"

using namespace std;

vector<Category> CategoryDAO::getAll() {
    vector<Category> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT CategoryID, Name, Description "
        "FROM Categories ORDER BY CategoryName"
    )) {
        qDebug() << "CategoriesDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Category c;
        c.setCategoryId(q.value("CategoryID").toInt());
        c.setName(q.value("Name").toString());
        c.setDescription(q.value("Description").toString());
        list.push_back(c);
    }

    return list;
}

optional<Category> CategoryDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT CategoryID, Name, Description "
        "FROM Categories WHERE CategoryID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "CategoriesDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Category c;
        c.setCategoryId(q.value("CategoryID").toInt());
        c.setName(q.value("Name").toString());
        c.setDescription(q.value("Description").toString());
        return c;
    }

    return nullopt;
}

optional<Category> CategoryDAO::getByName(const QString& name) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT CategoryID, Name, Description "
        "FROM Categories WHERE Name = :name"
    );
    q.bindValue(":name", name);

    if (!q.exec()) {
        qDebug() << "CategoriesDAO.getByName error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Category c;
        c.setCategoryId(q.value("CategoryID").toInt());
        c.setName(q.value("Name").toString());
        c.setDescription(q.value("Description").toString());
        return c;
    }

    return nullopt;
}

bool CategoryDAO::insert(const Category& c) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO Categories (Name, Description) "
        "VALUES (:name, :desc)"
    );
    q.bindValue(":name", c.getName());
    q.bindValue(":desc", c.getDescription());

    if (!q.exec()) {
        qDebug() << "CategoriesDAO.insert error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool CategoryDAO::update(const Category& c) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE Categories SET Name = :name, Description = :desc "
        "WHERE CategoryID = :id"
    );
    q.bindValue(":name", c.getName());
    q.bindValue(":desc", c.getDescription());
    q.bindValue(":id", c.getCategoryId());

    if (!q.exec()) {
        qDebug() << "CategoriesDAO.update error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool CategoryDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Categories WHERE CategoryID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "CategoriesDAO.remove error:" << q.lastError().text();
        return false;
    }
    return true;
}
