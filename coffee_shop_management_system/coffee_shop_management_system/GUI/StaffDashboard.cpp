#include "StaffDashboard.h"
#include "ui_StaffDashboard.h"

StaffDashboard::StaffDashboard(const User& loggedUser, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::StaffDashboard)
    , m_user(loggedUser)
{
    ui->setupUi(this);

    setWindowTitle("Staff Dashboard - " + m_user.fullName);
}

StaffDashboard::~StaffDashboard() {
    delete ui;
}
