#include "GUI/OrderWidget.h"
#include "BUS/ProductService.h"
#include "DAL/OrderDAO.h"
#include "DAL/OrderItemDAO.h"
#include "DAL/RecipeItemDAO.h"
#include "DAL/InventoryDAO.h"

#include "DTO/CartItemModel.h"
#include "DTO/Product.h" 

#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QSpinBox>

using namespace std;

OrderWidget::OrderWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.searchEdit->setStyleSheet(
        "QLineEdit {"
        "  padding-left: 25px;"  /* tạo khoảng trống cho icon */
        "  background-image: url(C:/coffee_shop/coffee-shop-management-system/coffee_shop_management_system/coffee_shop_management_system/icons/search.png);"
        "  background-position: left center;"
        "  background-repeat: no-repeat;"
        "  background-size: 16px 16px;"  /* resize icon vừa lineEdit */
        "}"
    );

    // ScrollArea chứa các sản phẩm trong giỏ
    cartContainer = new QWidget(this);
    cartLayout = new QVBoxLayout(cartContainer);
    cartContainer->setLayout(cartLayout);

    ui.cartScrollArea->setWidget(cartContainer);
    ui.cartScrollArea->setWidgetResizable(true);
    ui.cartScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui.cartScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // QLabel totalLabel dùng sẵn trong UI, nằm cố định bên ngoài ScrollArea
    updateTotalLabel();

    loadProductsGrid();

    // Kết nối nút thanh toán
    connect(ui.checkoutButton, &QPushButton::clicked, this, &OrderWidget::onCheckoutClicked);

    connect(ui.searchEdit, &QLineEdit::textChanged,
        this, &OrderWidget::loadProductsGrid);
}

OrderWidget::~OrderWidget()
{}

// ===============================================
// 1. LOAD SẢN PHẨM DẠNG GRID CÓ HÌNH ẢNH
// ===============================================

//void OrderWidget::loadProductsGrid(const QString& keyword)
//{
//    vector<Product> products = ProductService::getAllProducts();
//
//    QGridLayout* grid = new QGridLayout();
//    grid->setSpacing(16);
//
//    int row = 0, col = 0;
//    const int maxCol = 3;
//
//    for (const auto& p : products)
//    {
//        // --- Card widget ---
//        QWidget* card = new QWidget();
//        card->setFixedSize(170, 210);
//        card->setObjectName("productCard");
//
//        QVBoxLayout* vbox = new QVBoxLayout(card);
//        vbox->setContentsMargins(8, 8, 8, 8);
//        vbox->setSpacing(6);
//
//        // --- Hình ảnh ---
//        QLabel* imgLabel = new QLabel();
//        QPixmap pix(p.getImagePath());
//        imgLabel->setPixmap(pix.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        imgLabel->setAlignment(Qt::AlignCenter);
//
//        vbox->addWidget(imgLabel);
//
//        // --- Hàng tên + giá ---
//        QWidget* infoRow = new QWidget();
//        QHBoxLayout* hbox = new QHBoxLayout(infoRow);
//        hbox->setContentsMargins(4, 0, 4, 0);
//
//        QLabel* nameLabel = new QLabel(p.getName());
//        nameLabel->setStyleSheet("font-weight: bold;");
//        nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//
//        QLabel* priceLabel = new QLabel(QString::number(p.getPrice(), 'f', 0) + "đ");
//        priceLabel->setStyleSheet("color: #333; font-size: 13px;");
//
//        hbox->addWidget(nameLabel);
//        hbox->addWidget(priceLabel);
//
//        vbox->addWidget(infoRow);
//
//        // --- Hover effect bằng CSS ---
//        card->setStyleSheet(
//            "#productCard {"
//            "   background-color: white;"
//            "   border-radius: 10px;"
//            "   border: 1px solid #ddd;"
//            "   transition: 0.2s;"
//            "}"
//            "#productCard:hover {"
//            "   background-color: #f7f7f7;"
//            "   border: 1px solid #aaa;"
//            "}"
//        );
//
//        // --- Shadow effect để nổi lên khi di chuột ---
//        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(card);
//        effect->setBlurRadius(15);
//        effect->setOffset(0, 0);
//        effect->setColor(QColor(0, 0, 0, 90));
//        card->setGraphicsEffect(effect);
//
//        // --- Tạo nút trong suốt phủ toàn bộ card ---
//        QPushButton* overlay = new QPushButton(card);
//        overlay->setStyleSheet("background: transparent; border: none;");
//        overlay->setGeometry(0, 0, 170, 210);
//        overlay->setCursor(Qt::PointingHandCursor);
//
//        overlay->setProperty("productId", p.getProductId());
//        overlay->setProperty("productName", p.getName());
//        overlay->setProperty("productPrice", p.getPrice());
//        overlay->setProperty("productImage", p.getImagePath());
//
//        connect(overlay, &QPushButton::clicked, this, [=]() {
//            onProductClicked(
//                overlay->property("productId").toInt(),
//                overlay->property("productName").toString(),
//                overlay->property("productPrice").toDouble(),
//                overlay->property("productImage").toString()
//            );
//            });
//
//        // --- Thêm vào grid ---
//        grid->addWidget(card, row, col);
//
//        if (++col == maxCol) { col = 0; row++; }
//    }
//
//    ui.scrollAreaWidgetContents->setLayout(grid);
//}

void OrderWidget::loadProductsGrid(const QString& keyword)
{
    vector<Product> products;

    if (keyword.trimmed().isEmpty()) {
        products = ProductService::getAllProducts();
    }
    else {
        products = ProductService::searchProducts(keyword);
    }

    // XÓA GRID CŨ
    QLayout* oldLayout = ui.scrollAreaWidgetContents->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (item->widget()) delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // TẠO GRID MỚI
    QGridLayout* grid = new QGridLayout();
    grid->setSpacing(16);

    int row = 0, col = 0;
    const int maxCol = 3;

    for (const auto& p : products)
    {
        // — CARD widget giống như trước — 
        QWidget* card = new QWidget();
        card->setFixedSize(170, 210);
        card->setObjectName("productCard");

        QVBoxLayout* vbox = new QVBoxLayout(card);
        vbox->setContentsMargins(8, 8, 8, 8);
        vbox->setSpacing(6);

        QLabel* imgLabel = new QLabel();
        QPixmap pix(p.getImagePath());
        imgLabel->setPixmap(pix.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgLabel->setAlignment(Qt::AlignCenter);
        vbox->addWidget(imgLabel);

        QWidget* infoRow = new QWidget();
        infoRow->setFixedHeight(30);   // đảm bảo không bị đẩy xuống dòng

        QHBoxLayout* hbox = new QHBoxLayout(infoRow);
        hbox->setContentsMargins(4, 0, 4, 0);
        hbox->setSpacing(2);

        QLabel* nameLabel = new QLabel(p.getName());
        nameLabel->setStyleSheet("font-weight: bold;");
        nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QLabel* priceLabel = new QLabel(QString::number(p.getPrice(), 'f', 0) + "đ");
        priceLabel->setStyleSheet("color: #333; font-size: 13px;");
        priceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        priceLabel->setMinimumWidth(50);  // luôn đủ chỗ bên phải

        hbox->addWidget(nameLabel, 1);  // stretch 1
        hbox->addWidget(priceLabel, 0); // không co giãn

        vbox->addWidget(infoRow);


        // hover
        card->setStyleSheet(
            "#productCard { background:white; border-radius:10px; border:1px solid #ddd; }"
            "#productCard:hover { background:#f7f7f7; border:1px solid #aaa; }"
        );

        // overlay button
        QPushButton* overlay = new QPushButton(card);
        overlay->setStyleSheet("background:transparent; border:none;");
        overlay->setGeometry(0, 0, 170, 210);
        overlay->setCursor(Qt::PointingHandCursor);

        overlay->setProperty("productId", p.getProductId());
        overlay->setProperty("productName", p.getName());
        overlay->setProperty("productPrice", p.getPrice());
        overlay->setProperty("productImage", p.getImagePath());

        connect(overlay, &QPushButton::clicked, this, [=]() {
            onProductClicked(
                overlay->property("productId").toInt(),
                overlay->property("productName").toString(),
                overlay->property("productPrice").toDouble(),
                overlay->property("productImage").toString()
            );
            });

        grid->addWidget(card, row, col);

        if (++col == maxCol) { col = 0; row++; }
    }

    ui.scrollAreaWidgetContents->setLayout(grid);
}


void OrderWidget::onProductClicked(int id, const QString& name, double price, const QString& imagePath)
{
    bool found = false;
    for (auto& item : cart) {
        if (item.productId == id) {
            item.quantity++;
            found = true;
            break;
        }
    }

    if (!found) {
        CartItemModel newItem;
        newItem.productId = id;
        newItem.productName = name;
        newItem.productPrice = price;
        newItem.quantity = 1;
        newItem.imagePath = imagePath;
        cart.append(newItem); // Thêm vào cuối → hiển thị từ trên xuống
    }

    refreshCartUI();
}

void OrderWidget::refreshCartUI()
{
    if (!cartLayout) return;

    // Xóa toàn bộ row hiện tại
    QLayoutItem* item;
    while ((item = cartLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    // Duyệt theo QList (thứ tự thêm)
    for (int i = 0; i < cart.size(); ++i) {
        const CartItemModel& itemData = cart[i];

        QWidget* rowWidget = new QWidget();
        QHBoxLayout* hbox = new QHBoxLayout(rowWidget);
        hbox->setContentsMargins(5, 2, 5, 2);
        hbox->setSpacing(10);

        QLabel* imgLabel = new QLabel();
        QPixmap pix(itemData.imagePath);
        imgLabel->setPixmap(pix.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        hbox->addWidget(imgLabel);

        QLabel* nameLabel = new QLabel(itemData.productName);
        nameLabel->setFixedWidth(120);
        hbox->addWidget(nameLabel);

        QLabel* priceLabel = new QLabel(QString::number(itemData.productPrice, 'f', 2));
        priceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        priceLabel->setFixedWidth(60);
        hbox->addWidget(priceLabel);

        QSpinBox* qtySpin = new QSpinBox();
        qtySpin->setMinimum(1);
        qtySpin->setMaximum(999);
        qtySpin->setValue(itemData.quantity);
        qtySpin->setFixedWidth(60);
        hbox->addWidget(qtySpin);

        connect(qtySpin, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int val) {
            cart[i].quantity = val; // Cập nhật theo chỉ số
            updateTotalLabel();
            });

        QPushButton* removeBtn = new QPushButton("Xóa");
        removeBtn->setFixedWidth(50);
        hbox->addWidget(removeBtn);

        connect(removeBtn, &QPushButton::clicked, this, [=]() {
            cart.removeAt(i); // Xóa theo index
            refreshCartUI();
            });

        cartLayout->addWidget(rowWidget);
    }

    updateTotalLabel();
}


// ===============================================
// 3. CẬP NHẬT TOTAL LABEL
// ===============================================
void OrderWidget::updateTotalLabel()
{
    ui.totalLabel->setText("Tổng cộng: " + QString::number(calculateTotal(), 'f', 2));
}


// ===============================================
// 4. TÍNH TỔNG
// ===============================================

double OrderWidget::calculateTotal() const
{
    double total = 0.0;
    for (const auto& item : cart) {
        total += item.productPrice * item.quantity;
    }
    return total;
}


// ===============================================
// 5. THANH TOÁN
// ===============================================
void OrderWidget::onCheckoutClicked()
{
    // 1. Lấy thông tin khách hàng từ UI
    QString customerName = ui.customerNameEdit->text().trimmed();
    QString customerPhone = ui.customerPhoneEdit->text().trimmed();

    // Kiểm tra hợp lệ
    if (customerName.isEmpty() || customerPhone.isEmpty()) {
        QMessageBox::warning(this, "Thông tin chưa đầy đủ", "Vui lòng nhập tên và số điện thoại khách hàng.");
        return;
    }

    if (cart.isEmpty()) {
        QMessageBox::warning(this, "Giỏ hàng trống", "Vui lòng chọn ít nhất 1 sản phẩm.");
        return;
    }

    // 2. Tạo đơn hàng mới
    Order order;
    order.setCustomerName(customerName);
    order.setCustomerPhone(customerPhone);
    order.setCreatedAt(QDateTime::currentDateTime());
    order.setTotal(calculateTotal());

    int orderId = OrderDAO::insert(order);
    if (orderId == -1) {
        QMessageBox::critical(this, "Lỗi", "Không thể tạo đơn hàng.");
        return;
    }

    // 3. Thêm sản phẩm vào OrderItems và trừ nguyên liệu trong Inventory
    for (const auto& item : cart) {
        // Thêm vào OrderItems
        OrderItem orderItem;
        orderItem.setOrderId(orderId);
        orderItem.setProductId(item.productId);
        orderItem.setQuantity(item.quantity);
        orderItem.setUnitPrice(item.productPrice);
        OrderItemDAO::insert(orderItem);

        // Lấy RecipeItems
        vector<RecipeItem> recipeItems = RecipeItemDAO::getByProductId(item.productId);
        for (const auto& recipeItem : recipeItems) {
            int ingredientId = recipeItem.getIngredientId();
            double requiredQty = recipeItem.getQuantityPerUnit() * item.quantity;

            auto inventoryOpt = InventoryDAO::getByIngredientId(ingredientId);
            if (!inventoryOpt.has_value()) continue;

            Inventory inventory = inventoryOpt.value();
            inventory.setQuantity(inventory.getQuantity() - requiredQty);
            InventoryDAO::update(inventory);
        }
    }


    // 4. Xóa giỏ hàng và reset UI
    cart.clear();
    refreshCartUI();

    // Reset tên và số điện thoại
    ui.customerNameEdit->clear();
    ui.customerPhoneEdit->clear();

    QMessageBox::information(this, "Thành công", "Đơn hàng đã được tạo thành công!");
}