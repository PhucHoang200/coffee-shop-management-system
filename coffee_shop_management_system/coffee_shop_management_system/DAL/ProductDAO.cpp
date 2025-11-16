#include "ProductDAO.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <vector>
#include "DTO/Product.h"
#include "DbConnection.h"
#include <QSqlError>
#include <QString>
using namespace std;

vector<Product> ProductDAO::getAll() {
    vector<Product> list;
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return list;
    }

    QSqlQuery q(DbConnection::database());
    if (!q.exec("SELECT ProductID, CategoryID, Name, Price, ImagePath FROM Products ORDER BY Name")) {
        qDebug() << "ProductDAO.getAll exec error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Product p;
        p.setProductId(q.value("ProductID").toInt());
        p.setCategoryId(q.value("CategoryID").toInt());
        p.setName(q.value("Name").toString());
        p.setPrice(q.value("Price").toDouble());
        p.setImagePath(q.value("ImagePath").toString());
        list.push_back(p);
    }
    return list;
}

optional<Product> ProductDAO::getById(int productId) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return nullopt;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("SELECT ProductID, CategoryID, Name, Price, ImagePath FROM Products WHERE ProductID = :id");
    q.bindValue(":id", productId);
    if (!q.exec()) {
        qDebug() << "ProductDAO.getById exec error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Product p;
        p.setProductId(q.value("ProductID").toInt());
        p.setCategoryId(q.value("CategoryID").toInt());
        p.setName(q.value("Name").toString());
        p.setPrice(q.value("Price").toDouble());
        p.setImagePath(q.value("ImagePath").toString());
        return p;
    }
    return nullopt;
}

bool ProductDAO::insert(const Product& p) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return false;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("INSERT INTO Products (CategoryID, Name, Price, ImagePath) VALUES (:cat, :name, :price, :img)");
    q.bindValue(":cat", p.getCategoryId());
    q.bindValue(":name", p.getName());
    q.bindValue(":price", p.getPrice());
    q.bindValue(":img", p.getImagePath());

    if (!q.exec()) {
        qDebug() << "ProductDAO.insert exec error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ProductDAO::update(const Product& p) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return false;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare(R"(
        UPDATE Products SET CategoryID = :cat, Name = :name, Price = :price, ImagePath = :img
        WHERE ProductID = :id
    )");
    q.bindValue(":cat", p.getCategoryId());
    q.bindValue(":name", p.getName());
    q.bindValue(":price", p.getPrice());
    q.bindValue(":img", p.getImagePath());
    q.bindValue(":id", p.getProductId());

    if (!q.exec()) {
        qDebug() << "ProductDAO.update exec error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ProductDAO::remove(int productId) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return false;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Products WHERE ProductID = :id");
    q.bindValue(":id", productId);
    if (!q.exec()) {
        qDebug() << "ProductDAO.remove exec error:" << q.lastError().text();
        return false;
    }
    return true;
}

vector<Product> ProductDAO::searchByName(const QString& keyword) {
    vector<Product> list;
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return list;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("SELECT ProductID, CategoryID, Name, Price, ImagePath FROM Products WHERE Name LIKE :kw ORDER BY Name");
    q.bindValue(":kw", QString("%") + keyword + "%");
    if (!q.exec()) {
        qDebug() << "ProductDAO.searchByName exec error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Product p;
        p.setProductId(q.value("ProductID").toInt());
        p.setCategoryId(q.value("CategoryID").toInt());
        p.setName(q.value("Name").toString());
        p.setPrice(q.value("Price").toDouble());
        p.setImagePath(q.value("ImagePath").toString());
        list.push_back(p);
    }
    return list;
}
