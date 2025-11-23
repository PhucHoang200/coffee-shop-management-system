#include "GUI/AdminDashboard.h"
#include "ui_AdminDashboard.h"

#include <QVBoxLayout>

// Giao diện thật (bạn phải include đúng file)
#include <GUI/ProductManagement.h>
#include <GUI/OrderWidget.h>
#include <GUI/InventoryWidget.h>
#include <GUI/EmployeeWidget.h>
#include <GUI/ReportWidget.h>
#include <GUI/HomeWidget.h>

AdminDashboard::AdminDashboard(const User& loggedUser, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
    , m_user(loggedUser)
{
    ui->setupUi(this);

    // Xóa layout cũ nếu .ui tạo sẵn
    if (ui->frame_2->layout())
        delete ui->frame_2->layout();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    ui->frame_2->setLayout(layout);

    // ---- KHỞI TẠO TẤT CẢ CÁC PAGE ----
    homePage = new HomeWidget(ui->frame_2);
    orderPage = nullptr;
    productPage = nullptr;
    inventoryPage = nullptr;
    employeePage = nullptr;
    reportPage = nullptr;

    // ---- Kết nối signal từ HomeWidget ----
    connect(homePage, &HomeWidget::navigateToPage, this, [=](int i) {
        switch (i) {
        case 0: on_button1_clicked(); break;
        case 1: on_button2_clicked(); break;
        case 2: on_button3_clicked(); break;
        case 3: on_button4_clicked(); break;
        case 4: on_button5_clicked(); break;
        case 5: on_button6_clicked(); break;
        }
        });



    // ---- Load trang mặc định (Home) ----
    loadPage(homePage);
    ui->button1->setChecked(true);

    // ---- Set title ----
    setWindowTitle("Admin Dashboard - " + m_user.getFullName());

    // ---- Setup button group ----
    ui->button1->setCheckable(true);
    ui->button2->setCheckable(true);
    ui->button3->setCheckable(true);
    ui->button4->setCheckable(true);
    ui->button5->setCheckable(true);
    ui->button6->setCheckable(true);

    QButtonGroup* group = new QButtonGroup(this);
    group->setExclusive(true);

    group->addButton(ui->button1);
    group->addButton(ui->button2);
    group->addButton(ui->button3);
    group->addButton(ui->button4);
    group->addButton(ui->button5);
    group->addButton(ui->button6);
}

AdminDashboard::~AdminDashboard() {
    delete ui;
}

// ========================
// LOAD WIDGET VÀO FRAME
// ========================
void AdminDashboard::loadPage(QWidget* page)
{
    QLayout* layout = ui->frame_2->layout();

    // Clear layout cũ
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget())
            w->hide(); // không delete → tránh crash vì chúng ta dùng lại widget
        delete item;
    }

    // Thêm widget mới
    layout->addWidget(page);
    page->show();
}

// ========================
// BUTTON SLOTS
// ========================

void AdminDashboard::on_button1_clicked()
{
    loadPage(homePage);
    homePage->resetMenuButtons();

}

void AdminDashboard::on_button2_clicked()
{
    if (!orderPage)
        orderPage = new OrderWidget(ui->frame_2);
    loadPage(orderPage);
}

void AdminDashboard::on_button3_clicked()
{
    if (!productPage)
        productPage = new ProductManagement(ui->frame_2);
    loadPage(productPage);
}

void AdminDashboard::on_button4_clicked()
{
    if (!inventoryPage)
        inventoryPage = new InventoryWidget(ui->frame_2);
    loadPage(inventoryPage);
}

void AdminDashboard::on_button5_clicked()
{
    if (!employeePage)
        employeePage = new EmployeeWidget(ui->frame_2);
    loadPage(employeePage);
}

void AdminDashboard::on_button6_clicked()
{
    if (!reportPage)
        reportPage = new ReportWidget(ui->frame_2);
    loadPage(reportPage);
}

