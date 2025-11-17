#pragma once
#include "DTO/User.h"
#include <optional>
using namespace std;

class UserDAO {
public:
    // Tìm user theo username; trả std::optional<User>
    static optional<User> findByUsername(const QString& username);

    static std::vector<User> getAll();
    static std::optional<User> getById(int id);
    static bool insert(const User& u);
    static bool update(const User& u);
    static bool remove(int id);
};
