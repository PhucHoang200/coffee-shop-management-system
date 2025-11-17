#include "RoleDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "DbConnection.h"
#include <QDebug>

using namespace std;

vector<Role> RolesDAO::getAll() {
    vector<Role> list;
    if (!DbConnection::database().isOpen() && !DbConnection::connect()) return list;

    QSqlQuery q(DbConnection::database());
    if (!q.exec("SELECT RoleID, RoleName FROM Roles ORDER BY RoleName")) {
        qDebug() << "RolesDAO.getAll error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Role r;
        r.setRoleId(q.value("RoleID").toInt());
        r.setRoleName(q.value("RoleName").toString());
        list.push_back(r);
    }
    return list;
}

optional<Role> RolesDAO::getById(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect()) return nullopt;

    QSqlQuery q(DbConnection::database());
    q.prepare("SELECT RoleID, RoleName FROM Roles WHERE RoleID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) return nullopt;
    if (q.next()) {
        Role r;
        r.setRoleId(q.value("RoleID").toInt());
        r.setRoleName(q.value("RoleName").toString());
        return r;
    }
    return nullopt;
}

bool RolesDAO::insert(const Role& r) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect()) return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("INSERT INTO Roles (RoleName) VALUES (:name)");
    q.bindValue(":name", r.getRoleName());

    if (!q.exec()) {
        qDebug() << "RolesDAO.insert error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool RolesDAO::update(const Role& r) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect()) return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("UPDATE Roles SET RoleName = :name WHERE RoleID = :id");
    q.bindValue(":name", r.getRoleName());
    q.bindValue(":id", r.getRoleId());

    if (!q.exec()) {
        qDebug() << "RolesDAO.update error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool RolesDAO::remove(int id) {
    if (!DbConnection::database().isOpen() && !DbConnection::connect()) return false;

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Roles WHERE RoleID = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "RolesDAO.remove error:" << q.lastError().text();
        return false;
    }
    return true;
}
