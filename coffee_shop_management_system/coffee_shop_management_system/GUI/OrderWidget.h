#include <QWidget>
#include <QMap>
#include "DTO/CartItemModel.h"
#include "ui_OrderWidget.h"
#include <QScrollArea>
#include <QVBoxLayout>

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget* parent = nullptr);
    ~OrderWidget();

private:
    Ui::OrderWidgetClass ui;

    QWidget* cartContainer;
    QVBoxLayout* cartLayout;
    QLabel* totalLabel = nullptr;

    // GIỎ HÀNG: key = productId, value = CartItemModel
    QList<CartItemModel> cart; // thay QMap<int, CartItemModel>
    void updateTotalLabel();

private slots:
    void loadProductsGrid(const QString& keyword = "");
    void onProductClicked(int id, const QString& name, double price, const QString& imagePath);
    void refreshCartUI();
    double calculateTotal() const;
    void onCheckoutClicked();
};
