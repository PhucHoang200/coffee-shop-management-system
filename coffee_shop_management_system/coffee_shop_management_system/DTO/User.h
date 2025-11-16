#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
private:
    int userId;
    QString username;
    QByteArray passwordHash;
    QString fullName;
    int roleId;
    QDateTime createdAt;

public:
    User() = default;

    int getUserId() const;
    QString getUsername() const;
    QByteArray getPasswordHash() const;
    QString getFullName() const;
    int getRoleId() const;
    QDateTime getCreatedAt() const;

    void setUserId(int id);
    void setUsername(const QString& name);
    void setPasswordHash(const QByteArray& hash);
    void setFullName(const QString& name);
    void setRoleId(int id);
    void setCreatedAt(const QDateTime& dt);
};

#endif
