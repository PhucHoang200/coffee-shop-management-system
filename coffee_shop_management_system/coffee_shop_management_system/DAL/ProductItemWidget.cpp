#include "DAL/ProductItemWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDir>

ProductItemWidget::ProductItemWidget(const Product& product, QWidget* parent)
    : QWidget(parent), m_product(product)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    // ========== 1. HIỂN THỊ ẢNH ==========
    QLabel* imageLabel = new QLabel(this);
    imageLabel->setFixedSize(150, 150);
    imageLabel->setScaledContents(true);

    QString relativePath = product.getImagePath();
    QString fullPath;

    // Nếu là đường dẫn tương đối -> ghép vào thư mục Debug/x64
    if (!QDir::isAbsolutePath(relativePath))
    {
        QString appDir = QDir::currentPath();   // ví dụ: C:/project/x64/Debug
        fullPath = appDir + "/" + relativePath;
    }
    else
    {
        fullPath = relativePath;
    }

    QPixmap pix(fullPath);

    if (pix.isNull()) {
        qDebug() << "[ERROR] Load ảnh thất bại tại:" << fullPath;
        imageLabel->setText("Không thể load ảnh");
    }
    else {
        imageLabel->setPixmap(pix);
    }

    // ========== 2. TÊN + GIÁ ==========
    QLabel* name = new QLabel(product.getName());
    QLabel* price = new QLabel(QString::number(product.getPrice()) + " VND");

    // ========== 3. ADD VÀO LAYOUT ==========
    layout->addWidget(imageLabel);
    layout->addWidget(name);
    layout->addWidget(price);

    setLayout(layout);
}
