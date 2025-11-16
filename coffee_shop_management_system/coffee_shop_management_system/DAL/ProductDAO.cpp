#include "ProductDAO.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <vector>
#include "DTO/Product.h"
#include "DbConnection.h"
#include <QSqlError>
#include <QString>
using namespace std;

// Hoán đổi 2 Product
static void swapProduct(Product& a, Product& b) {
    Product temp = a;
    a = b;
    b = temp;
}

int ProductDAO::partition(vector<Product>& arr, int left, int right) {
    QString pivot = arr[right].getName();
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j].getName().compare(pivot, Qt::CaseInsensitive) < 0) {
            i++;
            swapProduct(arr[i], arr[j]);
        }
    }
    swapProduct(arr[i + 1], arr[right]);
    return i + 1;
}

void ProductDAO::quickSort(vector<Product>& arr, int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}

// Tìm vị trí đầu tiên có prefix (lower bound)
int ProductDAO::binarySearchPrefix(const vector<Product>& arr, const QString& prefix) {
    int left = 0, right = arr.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        QString name = arr[mid].getName().toLower();
        QString pre = prefix.toLower();

        if (name.startsWith(pre)) {
            result = mid;
            right = mid - 1; // tìm xem còn cái nào trước đó nữa không
        }
        else if (name < pre) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;  // -1 nếu không có
}

vector<Product> ProductDAO::getAll() {
    vector<Product> list;
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return list;
    }

    QSqlQuery q(DbConnection::database());
    if (!q.exec("SELECT ProductID, CategoryID, Name, Price, ImagePath FROM Products ORDER BY Name")) {
        qDebug() << "ProductDAO.getAll exec error:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Product p;
        p.setProductId(q.value("ProductID").toInt());
        p.setCategoryId(q.value("CategoryID").toInt());
        p.setName(q.value("Name").toString());
        p.setPrice(q.value("Price").toDouble());
        p.setImagePath(q.value("ImagePath").toString());
        list.push_back(p);
    }

    // Sort bằng QuickSort thủ công
    if (!list.empty()) {
        quickSort(list, 0, list.size() - 1);
    }

    return list;
}

optional<Product> ProductDAO::getById(int productId) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return nullopt;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("SELECT ProductID, CategoryID, Name, Price, ImagePath FROM Products WHERE ProductID = :id");
    q.bindValue(":id", productId);
    if (!q.exec()) {
        qDebug() << "ProductDAO.getById exec error:" << q.lastError().text();
        return nullopt;
    }

    if (q.next()) {
        Product p;
        p.setProductId(q.value("ProductID").toInt());
        p.setCategoryId(q.value("CategoryID").toInt());
        p.setName(q.value("Name").toString());
        p.setPrice(q.value("Price").toDouble());
        p.setImagePath(q.value("ImagePath").toString());
        return p;
    }
    return nullopt;
}

bool ProductDAO::insert(const Product& p) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return false;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("INSERT INTO Products (CategoryID, Name, Price, ImagePath) VALUES (:cat, :name, :price, :img)");
    q.bindValue(":cat", p.getCategoryId());
    q.bindValue(":name", p.getName());
    q.bindValue(":price", p.getPrice());
    q.bindValue(":img", p.getImagePath());

    if (!q.exec()) {
        qDebug() << "ProductDAO.insert exec error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ProductDAO::update(const Product& p) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return false;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare(R"(
        UPDATE Products SET CategoryID = :cat, Name = :name, Price = :price, ImagePath = :img
        WHERE ProductID = :id
    )");
    q.bindValue(":cat", p.getCategoryId());
    q.bindValue(":name", p.getName());
    q.bindValue(":price", p.getPrice());
    q.bindValue(":img", p.getImagePath());
    q.bindValue(":id", p.getProductId());

    if (!q.exec()) {
        qDebug() << "ProductDAO.update exec error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ProductDAO::remove(int productId) {
    if (!DbConnection::database().isOpen()) {
        if (!DbConnection::connect()) return false;
    }

    QSqlQuery q(DbConnection::database());
    q.prepare("DELETE FROM Products WHERE ProductID = :id");
    q.bindValue(":id", productId);
    if (!q.exec()) {
        qDebug() << "ProductDAO.remove exec error:" << q.lastError().text();
        return false;
    }
    return true;
}

// Tìm kiếm theo keyword nhập vào → tìm prefix (case-insensitive)
vector<Product> ProductDAO::searchByName(const QString& keyword) {
    vector<Product> all = getAll();
    vector<Product> result;

    if (keyword.trimmed().isEmpty()) return all;

    int start = binarySearchPrefix(all, keyword);

    if (start == -1) return result;

    QString kw = keyword.toLower();

    // Lấy tất cả sản phẩm bắt đầu bằng prefix
    for (int i = start; i < all.size(); i++) {
        if (all[i].getName().toLower().startsWith(kw)) {
            result.push_back(all[i]);
        }
        else {
            break;
        }
    }

    return result;
}
