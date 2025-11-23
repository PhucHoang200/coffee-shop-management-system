#include "HomeWidget.h"
#include <QPalette>
#include <QPixmap>
#include <QDebug>

HomeWidget::HomeWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // ========================================================
    // 1. Đặt hình nền
    // ========================================================
    QString imagePath = "C:/coffee_shop/coffee-shop-management-system/"
        "coffee_shop_management_system/"
        "coffee_shop_management_system/"
        "anh_cafe_db/back_ground.jpg";

    QPixmap bg(imagePath);

    if (!bg.isNull()) {
        bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette pal;
        pal.setBrush(QPalette::Window, QBrush(bg));
        setAutoFillBackground(true);
        setPalette(pal);
    }
    else {
        qDebug() << "Không load được hình nền:" << imagePath;
    }

    // ========================================================
    // 2. Lấy 6 button trong UI
    // ========================================================
    buttons = {
        ui.button1,
        ui.button2,
        ui.button3,
        ui.button4,
        ui.button5,
        ui.button6
    };

    // ========================================================
    // 3. Gán Style Sheet (trong suốt + hover + click)
    // ========================================================
    const QString btnStyle =
        "QPushButton {"
        "   background-color: rgba(255, 255, 255, 76);"   /* 50% trong suốt = 128/255 */
        "   padding: 6px;"
        "   font-size: 22px;"
        "   color: white;"
        "   border-radius: 12px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 0);"     /* TRONG SUỐT HOÀN TOÀN */
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 80);"    /* Nhấn → hơi sáng */
        "}";



    // ========================================================
    // 4. Gán style + connect emit navigateToPage(i)
    // ========================================================
    for (int i = 0; i < buttons.size(); ++i)
    {
        QPushButton* btn = buttons[i];
        btn->setCheckable(true);
        btn->setStyleSheet(btnStyle);

        connect(btn, &QPushButton::clicked, this, [=]() {
            emit navigateToPage(i);      // báo sang AdminDashboard
            });
    }
}

// ============================================================
// Reset trạng thái 6 button khi quay lại HomeWidget
// ============================================================
void HomeWidget::resetMenuButtons()
{
    for (QPushButton* btn : buttons)
        btn->setChecked(false);
}

HomeWidget::~HomeWidget()
{}
