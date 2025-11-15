#pragma once
#include <QString>

class User {
public:
    int userId = 0;
    QString username;
    QByteArray passwordHash; // raw bytes (32 bytes SHA-256)
    QString fullName;
    int roleId = 0;
    QString roleName;
};
