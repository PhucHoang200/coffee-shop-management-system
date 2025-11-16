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

    // --- THÊM STYLE TẠI ĐÂY ---
    QString style =
        "QLineEdit {"
        "   border: 1px solid #CCCCCC;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "   background: white;"
        "}"
        "QLineEdit:focus {"
        "   border: 1px solid #0078D7;"
        "}"

        "QPushButton {"
        "   background-color: #0078D7;"
        "   color: white;"
        "   border-radius: 10px;"
        "   padding: 6px 12px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #005A9E;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #003F6B;"
        "}";

    this->setStyleSheet(style);
    // ----------------------------------

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
