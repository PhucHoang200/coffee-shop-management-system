#pragma once
#include <QString>

struct CartItemModel {
    int productId;
    QString productName;
    double productPrice;
    int quantity;
	QString imagePath; // Thêm trường imagePath để lưu đường dẫn hình ảnh sản phẩm
};
#pragma once
