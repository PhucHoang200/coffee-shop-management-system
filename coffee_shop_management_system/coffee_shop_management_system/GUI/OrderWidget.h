#include <QWidget>
#include <QMap>
#include "DTO/CartItemModel.h"
#include "ui_OrderWidget.h"

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget* parent = nullptr);
    ~OrderWidget();

private:
    Ui::OrderWidgetClass ui;

    // GIỎ HÀNG: key = productId, value = CartItemModel
    QMap<int, CartItemModel> cart;

private slots:
    void loadProductsGrid();
    void onProductClicked(int id, const QString& name, double price, const QString& imagePath);
    void refreshCartUI();
    double calculateTotal() const;
    void onCheckoutClicked();
};
