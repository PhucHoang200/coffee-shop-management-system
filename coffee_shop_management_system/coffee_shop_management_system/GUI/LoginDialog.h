#pragma once
#include <QDialog>
#include <optional>
#include "DTO/User.h"

namespace Ui { class LoginDialog; }

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();
    std::optional<User> loggedUser() const;

private slots:
    void on_btnLogin_clicked();
    void on_btnCancel_clicked();

private:
    Ui::LoginDialog* ui;
    std::optional<User> m_loggedUser;

    void showError(const QString& msg);
};
