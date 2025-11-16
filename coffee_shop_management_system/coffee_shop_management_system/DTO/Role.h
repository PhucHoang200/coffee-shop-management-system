#ifndef ROLE_H
#define ROLE_H

#include <QString>

class Role {
private:
    int roleId;
    QString roleName;

public:
    Role() = default;
    Role(int id, const QString& name);

    int getRoleId() const;
    QString getRoleName() const;

    void setRoleId(int id);
    void setRoleName(const QString& name);
};

#endif
