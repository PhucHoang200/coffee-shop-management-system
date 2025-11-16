#include <QApplication>
#include "GUI/LoginDialog.h"
#include <QMessageBox>
#include "DAL/DbConnection.h"
#include "DTO/User.h"
#include <DTO/Role.h>
#include "GUI/AdminDashboard.h"
#include "GUI/StaffDashboard.h"
#include <QSqlError>
#include <QSqlDatabase>
#include <GUI/ProductManagement.h>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //Kết nối DB sớm
    if (!DbConnection::connect()) {

        QMessageBox::critical(
            nullptr,
            "DB Error",
            QString("Không thể kết nối SQL Server.\n\nChi tiết lỗi:\n%1")
            .arg(DbConnection::database().lastError().text())
        );

        return 1;
    }

    LoginDialog dlg;
    if (dlg.exec() != QDialog::Accepted)
        return 0;

    auto optUser = dlg.loggedUser();
    if (!optUser.has_value())
        return 1;

    User u = optUser.value();

    // Mở form theo ROLE
    if (u.getRoleId() == 1) {
        AdminDashboard w(u);  // truyền user vào
        w.show();
        return a.exec();
    }
    else if (u.getRoleId() == 2) {
        StaffDashboard w(u);
        w.show();
        return a.exec();
    }
    else {
        QMessageBox::warning(nullptr, "Role Error",
            "User không có role hợp lệ.");
        return 1;
    }
}
