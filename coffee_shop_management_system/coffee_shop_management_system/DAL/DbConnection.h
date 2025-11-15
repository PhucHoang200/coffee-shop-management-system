#pragma once
#include <QSqlDatabase>

class DbConnection {
public:
    static bool connect();
    static void disconnect();
    static QSqlDatabase& database();
private:
    static QSqlDatabase db;
};
