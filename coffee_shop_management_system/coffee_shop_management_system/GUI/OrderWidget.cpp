#include "GUI/OrderWidget.h"
#include "DAL/ProductItemWidget.h"
#include "BUS/ProductService.h"
#include <QGridLayout>

OrderWidget::OrderWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    // Load danh sách sản phẩm dạng grid
    loadProductsGrid();
}

OrderWidget::~OrderWidget()
{}

void OrderWidget::loadProductsGrid()
{
    // 1. Lấy danh sách SP từ ProductService
    vector<Product> products = ProductService::getAllProducts();

    // 2. Tạo grid layout
    QGridLayout* grid = new QGridLayout();

    int row = 0;
    int col = 0;
    const int maxCol = 3; // mỗi hàng 3 sản phẩm

    // 3. Duyệt list sản phẩm và thêm vào grid
    for (int i = 0; i < products.size(); i++)
    {
        ProductItemWidget* item = new ProductItemWidget(products[i]);
        grid->addWidget(item, row, col);

        col++;
        if (col >= maxCol) {
            col = 0;
            row++;
        }
    }

    // 4. Gán layout vào scrollAreaWidgetContents
    ui.scrollAreaWidgetContents->setLayout(grid);
}