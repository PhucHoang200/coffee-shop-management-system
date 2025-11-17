#include "UserDAO.h"
#include "DbConnection.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <DTO/User.h>
using namespace std;


optional<User> UserDAO::findByUsername(const QString& username) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return std::nullopt;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare(R"(
        SELECT u.UserID, u.Username, u.PasswordHash, u.FullName, u.RoleID, r.RoleName
        FROM Users u
        LEFT JOIN Roles r ON u.RoleID = r.RoleID
        WHERE u.Username = :username
    )");
    q.bindValue(":username", username);

    if (!q.exec()) {
        qDebug() << "UserDAO.findByUsername exec error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        User u;
        u.setUserId(q.value("UserID").toInt());
        u.setUsername(q.value("Username").toString());
        u.setPasswordHash(q.value("PasswordHash").toByteArray());
        u.setFullName(q.value("FullName").toString());
        u.setRoleId(q.value("RoleID").toInt());

        return u;
    }

    return nullopt;
}

vector<User> UserDAO::getAll() {
    vector<User> list;

    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec(
        "SELECT UserID, Username, PasswordHash, FullName, RoleID, CreatedAt "
        "FROM Users ORDER BY Username"
    )) {
        qDebug() << "UsersDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        User u;
        u.setUserId(q.value("UserID").toInt());
        u.setUsername(q.value("Username").toString());
        u.setPasswordHash(q.value("PasswordHash").toByteArray());
        u.setFullName(q.value("FullName").toString());
        u.setRoleId(q.value("RoleID").toInt());
        u.setCreatedAt(q.value("CreatedAt").toDateTime());
        list.push_back(u);
    }

    return list;
}

optional<User> UserDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "SELECT UserID, Username, PasswordHash, FullName, RoleID, CreatedAt "
        "FROM Users WHERE UserID = :id"
    );
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "UsersDAO.getById error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        User u;
        u.setUserId(q.value("UserID").toInt());
        u.setUsername(q.value("Username").toString());
        u.setPasswordHash(q.value("PasswordHash").toByteArray());
        u.setFullName(q.value("FullName").toString());
        u.setRoleId(q.value("RoleID").toInt());
        u.setCreatedAt(q.value("CreatedAt").toDateTime());
        return u;
    }

    return nullopt;
}

bool UserDAO::insert(const User& u) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "INSERT INTO Users (Username, PasswordHash, FullName, RoleID) "
        "VALUES (:usr, :pwd, :name, :role)"
    );
    q.bindValue(":usr", u.getUsername());
    q.bindValue(":pwd", u.getPasswordHash());
    q.bindValue(":name", u.getFullName());
    q.bindValue(":role", u.getRoleId());

    if (!q.exec()) {
        qDebug() << "UsersDAO.insert error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool UserDAO::update(const User& u) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare(
        "UPDATE Users SET Username = :usr, PasswordHash = :pwd, FullName = :name, "
        "RoleID = :role WHERE UserID = :id"
    );
    q.bindValue(":usr", u.getUsername());
    q.bindValue(":pwd", u.getPasswordHash());
    q.bindValue(":name", u.getFullName());
    q.bindValue(":role", u.getRoleId());
    q.bindValue(":id", u.getUserId());

    if (!q.exec()) {
        qDebug() << "UsersDAO.update error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool UserDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect())
        return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Users WHERE UserID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "UsersDAO.remove error:" << q.lastError().text();
        return false;
    }
    return true;
}
