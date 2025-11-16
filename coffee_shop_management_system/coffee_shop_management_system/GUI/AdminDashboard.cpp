#include "AdminDashboard.h"
#include "ui_AdminDashboard.h"

AdminDashboard::AdminDashboard(const User& loggedUser, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
    , m_user(loggedUser)
{
    ui->setupUi(this);

    // Ví dụ hiển thị tên
    setWindowTitle("Admin Dashboard - " + m_user.getFullName());
}

AdminDashboard::~AdminDashboard() {
    delete ui;
}
