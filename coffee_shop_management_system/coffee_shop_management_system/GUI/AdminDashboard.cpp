#include "AdminDashboard.h"
#include "ui_AdminDashboard.h"
#include <QButtonGroup>

AdminDashboard::AdminDashboard(const User& loggedUser, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
    , m_user(loggedUser)
{
    ui->setupUi(this);

    // Ví dụ hiển thị tên
    setWindowTitle("Admin Dashboard - " + m_user.getFullName());

    // --- Bắt đầu đặt checkable và nhóm button ---
    ui->button1->setCheckable(true);
    ui->button2->setCheckable(true);
    ui->button3->setCheckable(true);

    QButtonGroup* group = new QButtonGroup(this);
    group->setExclusive(true);   // Chỉ 1 nút được chọn
    group->addButton(ui->button1);
    group->addButton(ui->button2);
    group->addButton(ui->button3);
}

AdminDashboard::~AdminDashboard() {
    delete ui;
}
