#pragma once
#include <QMainWindow>
#include "DTO/User.h"

namespace Ui { class StaffDashboard; }

class StaffDashboard : public QMainWindow
{
    Q_OBJECT
public:
    explicit StaffDashboard(const User& loggedUser, QWidget* parent = nullptr);
    ~StaffDashboard();

private:
    Ui::StaffDashboard* ui;
    User m_user;
};
