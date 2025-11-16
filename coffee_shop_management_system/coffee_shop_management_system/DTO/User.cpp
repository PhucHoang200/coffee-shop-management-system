#include "User.h"

int User::getUserId() const { return userId; }
QString User::getUsername() const { return username; }
QByteArray User::getPasswordHash() const { return passwordHash; }
QString User::getFullName() const { return fullName; }
int User::getRoleId() const { return roleId; }
QDateTime User::getCreatedAt() const { return createdAt; }

void User::setUserId(int id) { userId = id; }
void User::setUsername(const QString& name) { username = name; }
void User::setPasswordHash(const QByteArray& hash) { passwordHash = hash; }
void User::setFullName(const QString& name) { fullName = name; }
void User::setRoleId(int id) { roleId = id; }
void User::setCreatedAt(const QDateTime& dt) { createdAt = dt; }
