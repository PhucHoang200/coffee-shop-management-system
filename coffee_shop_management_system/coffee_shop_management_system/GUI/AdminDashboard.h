#pragma once
#include <QMainWindow>
#include "DTO/User.h"
#include <QButtonGroup>

class ProductManagement;
class OrderWidget;
class InventoryWidget;
class EmployeeWidget;
class ReportWidget;
class HomeWidget;   // Trang chủ

namespace Ui { class AdminDashboard; }

class AdminDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminDashboard(const User& loggedUser, QWidget* parent = nullptr);
    ~AdminDashboard();

private slots:
    void on_button1_clicked(); // Home
    void on_button2_clicked(); // Orders
    void on_button3_clicked(); // Products
    void on_button4_clicked(); // Inventory
    void on_button5_clicked(); // Employees
    void on_button6_clicked(); // Reports

private:
    Ui::AdminDashboard* ui;
    User m_user;

    // Khai báo widget giao diện
    HomeWidget* homePage;
    OrderWidget* orderPage;
    ProductManagement* productPage;
    InventoryWidget* inventoryPage;
    EmployeeWidget* employeePage;
    ReportWidget* reportPage;

    void loadPage(QWidget* page);
};
