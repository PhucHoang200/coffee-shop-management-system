#pragma once
#include <QMainWindow>
#include "DTO/User.h"
#include <QButtonGroup>

namespace Ui { class AdminDashboard; }

class AdminDashboard : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminDashboard(const User& loggedUser, QWidget* parent = nullptr);
    ~AdminDashboard();

private:
    Ui::AdminDashboard* ui;
    User m_user;  // Lưu thông tin user đăng nhập
};
