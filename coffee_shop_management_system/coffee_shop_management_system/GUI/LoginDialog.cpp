#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QMessageBox>
#include "BUS/AuthService.h"
#include "DAL/DbConnection.h"
#include "GUI/AdminDashboard.h"
#include "GUI/StaffDashboard.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->editPassword->setEchoMode(QLineEdit::Password);

    // DB connect
    if (!DbConnection::connect()) {
        QMessageBox::critical(this, "DB Error",
            "Không thể kết nối SQL Server. Kiểm tra ODBC và dịch vụ SQL.");
    }

    // Gán sự kiện cho 2 nút
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::on_btnLogin_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &LoginDialog::on_btnCancel_clicked);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

std::optional<User> LoginDialog::loggedUser() const {
    return m_loggedUser;
}

void LoginDialog::showError(const QString& msg) {
    QMessageBox::warning(this, "Login Failed", msg);
}

void LoginDialog::on_btnCancel_clicked() {
    reject();
}

void LoginDialog::on_btnLogin_clicked() {
    QString username = ui->editUsername->text().trimmed();
    QString password = ui->editPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        showError("Vui lòng nhập Username và Password.");
        return;
    }

    auto opt = AuthService::login(username, password);
    if (!opt.has_value()) {
        showError("Tên đăng nhập hoặc mật khẩu không đúng.");
        return;
    }

    m_loggedUser = opt.value();

    // Đăng nhập thành công — tự đóng LoginDialog
    accept();
}
