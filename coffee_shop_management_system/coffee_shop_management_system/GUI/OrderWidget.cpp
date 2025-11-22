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

using namespace std;

OrderWidget::OrderWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    loadProductsGrid();

	// Kết nối nút thanh toán
	connect(ui.checkoutButton, &QPushButton::clicked, this, &OrderWidget::onCheckoutClicked);
}

OrderWidget::~OrderWidget()
{}

// ===============================================
// 1. LOAD SẢN PHẨM DẠNG GRID CÓ HÌNH ẢNH
// ===============================================
void OrderWidget::loadProductsGrid()
{
    // Lấy danh sách sản phẩm (giả sử getAllProducts() trả về QVector<Product>)
    vector<Product> products = ProductService::getAllProducts();

    QGridLayout* grid = new QGridLayout();
    int row = 0, col = 0;
    const int maxCol = 3;

    for (const auto& p : products)
    {
        // Widget container cho mỗi sản phẩm
        QWidget* productWidget = new QWidget();
        QVBoxLayout* vbox = new QVBoxLayout(productWidget);

        // QLabel hiển thị hình ảnh
        QLabel* imgLabel = new QLabel();
        QPixmap pix(p.getImagePath()); // Giả sử Product có getImagePath()
        imgLabel->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgLabel->setAlignment(Qt::AlignCenter);
        vbox->addWidget(imgLabel);

        // QPushButton tên sản phẩm
        QPushButton* btn = new QPushButton(p.getName());
        btn->setProperty("productId", p.getProductId());
        btn->setProperty("productName", p.getName());
        btn->setProperty("productPrice", p.getPrice());

        // Style button
        btn->setStyleSheet(
            "QPushButton { padding: 6px; border-radius: 4px; border: 1px solid #ccc; }"
            "QPushButton:hover { background-color: rgba(0,0,0,0.05); }"
        );
        vbox->addWidget(btn);

        // Click event
        connect(btn, &QPushButton::clicked, this, [=]() {
            onProductClicked(
                btn->property("productId").toInt(),
                btn->property("productName").toString(),
                btn->property("productPrice").toDouble(),
                p.getImagePath() // thêm đường dẫn hình ảnh
            );
            });

        // Thêm vào grid
        grid->addWidget(productWidget, row, col);

        if (++col == maxCol) { col = 0; row++; }
    }

    ui.scrollAreaWidgetContents->setLayout(grid);
}



// ===============================================
// 2. XỬ LÝ CLICK → THÊM GIỎ HÀNG
// ===============================================
void OrderWidget::onProductClicked(int id, const QString& name, double price, const QString& imagePath)
{
    if (cart.contains(id)) {
        cart[id].quantity++;
    }
    else {
        CartItemModel item;
        item.productId = id;
        item.productName = name;
        item.productPrice = price;
        item.quantity = 1;
        item.imagePath = imagePath; // Thêm trường imagePath vào CartItemModel
        cart.insert(item.productId, item);
    }

    refreshCartUI();
}

// ===============================================
// 3. CẬP NHẬT GIAO DIỆN GIỎ HÀNG (TRONG FRAME CÓ SẴN)
// ===============================================
void OrderWidget::refreshCartUI()
{
    // Xóa layout cũ nếu có
    QLayout* oldLayout = ui.frame->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget* w = item->widget())
                delete w;
            delete item;
        }
        delete oldLayout;
    }

    QVBoxLayout* vbox = new QVBoxLayout(ui.frame); // frame có sẵn

    for (auto it = cart.begin(); it != cart.end(); ++it) {
        const CartItemModel& item = it.value();

        // Widget container cho mỗi sản phẩm trong giỏ
        QWidget* rowWidget = new QWidget();
        QHBoxLayout* hbox = new QHBoxLayout(rowWidget);

        // 1. Hình ảnh
        QLabel* imgLabel = new QLabel();
        QPixmap pix(item.imagePath);
        imgLabel->setPixmap(pix.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        hbox->addWidget(imgLabel);

        // 2. Tên + số lượng
        QLabel* nameLabel = new QLabel(item.productName + " x" + QString::number(item.quantity));
        nameLabel->setMinimumWidth(150);
        hbox->addWidget(nameLabel);

        // 3. Giá
        QLabel* priceLabel = new QLabel(QString::number(item.productPrice * item.quantity, 'f', 2));
        priceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        priceLabel->setMinimumWidth(80);
        hbox->addWidget(priceLabel);

        vbox->addWidget(rowWidget);
    }

    // Tổng cộng
    QLabel* totalLabel = new QLabel("Tổng cộng: " + QString::number(calculateTotal(), 'f', 2));
    totalLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    vbox->addWidget(totalLabel);

    ui.frame->setLayout(vbox);
}

// ===============================================
// 4. TÍNH TỔNG
// ===============================================
double OrderWidget::calculateTotal() const
{
    double total = 0.0;

    for (auto it = cart.begin(); it != cart.end(); ++it) {
        const CartItemModel& item = it.value();
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
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        const CartItemModel& item = it.value();

        // Thêm vào OrderItems
        OrderItem orderItem;
        orderItem.setOrderId(orderId);
        orderItem.setProductId(item.productId);
        orderItem.setQuantity(item.quantity);
        orderItem.setUnitPrice(item.productPrice);
        OrderItemDAO::insert(orderItem);

        // Lấy RecipeItems cho sản phẩm
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