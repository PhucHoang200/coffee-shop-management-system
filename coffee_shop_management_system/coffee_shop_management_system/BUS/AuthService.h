#pragma once
#include "DTO/User.h"
#include <optional>

class AuthService {
public:
    // Trả User nếu login thành công, ngược lại nullopt
    static std::optional<User> login(const QString& username, const QString& passwordPlain);
    // Helper: tạo hash SHA256
    static QByteArray hashPassword(const QString& passwordPlain);
};
