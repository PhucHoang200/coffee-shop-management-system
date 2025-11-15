#include "UserDAO.h"
#include "DbConnection.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>


std::optional<User> UserDAO::findByUsername(const QString& username) {
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
        return std::nullopt;
    }

    if (q.next()) {
        User u;
        u.userId = q.value("UserID").toInt();
        u.username = q.value("Username").toString();
        u.passwordHash = q.value("PasswordHash").toByteArray();
        u.fullName = q.value("FullName").toString();
        u.roleId = q.value("RoleID").toInt();
        u.roleName = q.value("RoleName").toString();
        return u;
    }

    return std::nullopt;
}
