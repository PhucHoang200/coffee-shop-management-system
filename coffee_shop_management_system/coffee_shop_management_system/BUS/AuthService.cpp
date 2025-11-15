#include "AuthService.h"
#include "../dal/UserDAO.h"
#include <QCryptographicHash>
#include <QDebug>

QByteArray AuthService::hashPassword(const QString& passwordPlain) {
    QByteArray data = passwordPlain.toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    return hash; // 32 bytes
}

std::optional<User> AuthService::login(const QString& username, const QString& passwordPlain) {
    auto opt = UserDAO::findByUsername(username);
    if (!opt.has_value()) return std::nullopt;

    User u = opt.value();
    QByteArray providedHash = hashPassword(passwordPlain);

    // Compare raw bytes
    if (u.passwordHash == providedHash) {
        // success
        return u;
    }
    else {
        return std::nullopt;
    }
}
