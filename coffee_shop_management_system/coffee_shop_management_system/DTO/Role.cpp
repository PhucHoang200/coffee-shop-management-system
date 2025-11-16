#include "Role.h"

Role::Role(int id, const QString& name)
    : roleId(id), roleName(name) {}

int Role::getRoleId() const { return roleId; }
QString Role::getRoleName() const { return roleName; }

void Role::setRoleId(int id) { roleId = id; }
void Role::setRoleName(const QString& name) { roleName = name; }
