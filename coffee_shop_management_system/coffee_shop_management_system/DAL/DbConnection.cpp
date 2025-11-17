#include "DbConnection.h"
#include <QSqlError>
#include <QDebug>

QSqlDatabase DbConnection::db = QSqlDatabase();

bool DbConnection::connect() {
    if (db.isOpen())
        return true;

    if (QSqlDatabase::contains("CafePOSConnection"))
        db = QSqlDatabase::database("CafePOSConnection");
    else
        db = QSqlDatabase::addDatabase("QODBC", "CafePOSConnection");

    // ⭐ FIX: Connection string phải EXACTLY như sau (Không dư dấu ; cuối)
    QString connStr = QStringLiteral(
        "Driver={ODBC Driver 17 for SQL Server};"
        //"Server=localhost\\SQLEXPRESS;"
        "Server=DESKTOP-DE6G2CH\\SQLEXPRESS;"
        "Database=CafeDB;"
        "Trusted_Connection=Yes;"
        "TrustServerCertificate=Yes;"
    );


    db.setDatabaseName(connStr);

    if (!db.open()) {
        qDebug() << "❌ SQL connect failed:" << db.lastError().text();
        return false;
    }

    qDebug() << "✅ Connected to SQL Server Express.";
    return true;
}

void DbConnection::disconnect() {
    if (db.isOpen()) db.close();
}

QSqlDatabase& DbConnection::database() {
    return db;
}
