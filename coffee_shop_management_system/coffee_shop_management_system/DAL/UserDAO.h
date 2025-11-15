#pragma once
#include "../dto/User.h"
#include <optional>

class UserDAO {
public:
    // Tìm user theo username; trả std::optional<User>
    static std::optional<User> findByUsername(const QString& username);
};
