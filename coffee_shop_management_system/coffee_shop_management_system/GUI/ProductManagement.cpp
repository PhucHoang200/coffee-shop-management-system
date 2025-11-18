#include "GUI/ProductManagement.h"
#include "BUS/ProductService.h"
#include "BUS/CategoryService.h"
#include "BUS/RecipeService.h"
#include "DTO/Category.h"
#include "DTO/Product.h"


#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QHBoxLayout>

ProductManagement::ProductManagement(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    loadProductsGrid();
}

ProductManagement::~ProductManagement()
{
}

void ProductManagement::loadProductsGrid()
{
    // Xóa layout cũ nếu có
    if (ui.scrollAreaWidgetContents->layout())
        delete ui.scrollAreaWidgetContents->layout();

    // 1. Lấy danh sách sản phẩm
    vector<Product> products = ProductService::getAllProducts();

    // 2. Tạo grid layout cho dạng 1 hàng nhiều cột
    QGridLayout* grid = new QGridLayout();
    grid->setColumnStretch(5, 1);   // giúp căn chỉnh đẹp

    int row = 0;

    // ======= HEADER ==========
    grid->addWidget(new QLabel("Mã SP"), row, 0);
    grid->addWidget(new QLabel("Tên SP"), row, 1);
    grid->addWidget(new QLabel("Loại SP"), row, 2);
    grid->addWidget(new QLabel("Giá vốn"), row, 3);
    grid->addWidget(new QLabel("Giá bán"), row, 4);
    grid->addWidget(new QLabel("Hành động"), row, 5);

    row++;

    // 3. Load từng sản phẩm vào một dòng
    for (auto& p : products)
    {
        // --- Lấy dữ liệu category ---
        Category cat = CategoryService::getCategory(p.getCategoryId());

        // --- Tính giá vốn (cost) từ Recipe ---
        double costPrice = RecipeService::calculateCostForProduct(p.getProductId());

        // ============ Thêm từng cột ============
        // Cột 0: Mã SP
        QLabel* lblId = new QLabel(QString::number(p.getProductId()));
        grid->addWidget(lblId, row, 0);

        // Cột 1: Tên SP
        QLabel* lblName = new QLabel(p.getName());
        grid->addWidget(lblName, row, 1);

        // Cột 2: Loại sản phẩm
        QLabel* lblCategory = new QLabel(cat.getName());
        grid->addWidget(lblCategory, row, 2);

        // Cột 3: Giá vốn
        QLabel* lblCost = new QLabel(QString::number(costPrice, 'f', 0));
        grid->addWidget(lblCost, row, 3);

        // Cột 4: Giá bán
        QLabel* lblPrice = new QLabel(QString::number(p.getPrice(), 'f', 0));
        grid->addWidget(lblPrice, row, 4);

        // Cột 5: Hành động (nút 3 chấm)
        QPushButton* btnMore = new QPushButton("⋮");  // dấu 3 chấm dọc
        btnMore->setFixedWidth(30);

        // Tạo menu popup
        QMenu* menu = new QMenu(btnMore);
        menu->addAction("Chỉnh sửa", [this, id = p.getProductId()]() {
            onEditProduct(id);
            });
        menu->addAction("Xóa", [this, id = p.getProductId()]() {
            onDeleteProduct(id);
            });

        // Khi bấm nút → show menu
        QObject::connect(btnMore, &QPushButton::clicked, [=]() {
            menu->exec(btnMore->mapToGlobal(QPoint(0, btnMore->height())));
            });

        grid->addWidget(btnMore, row, 5);

        row++;
    }

    // 4. Gán layout vào scroll area
    ui.scrollAreaWidgetContents->setLayout(grid);
}

// =============================
// Các hàm xử lý menu 3 chấm
// =============================
void ProductManagement::onEditProduct(int id)
{
    // TODO: mở dialog chỉnh sửa sản phẩm
}

void ProductManagement::onDeleteProduct(int id)
{
    // TODO: xác nhận rồi gọi ProductService::deleteProduct(id);
}
