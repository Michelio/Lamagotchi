#ifndef FLEX_GRID_LAYOUT_H
#define FLEX_GRID_LAYOUT_H

#include <QLayout>

namespace Lamagotchi
{

namespace Ui
{

class FlexGridLayout : public QLayout
{
    Q_OBJECT

public:
    FlexGridLayout(QWidget* parent = nullptr, int spacing = 3, int margin = 3);
    ~FlexGridLayout();

    void addItem(QLayoutItem* item) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect& rect) override;
    QLayoutItem* itemAt(int index) const override;
    QLayoutItem* takeAt(int index) override;
    int count() const override;

private:
    QList<QLayoutItem*> itemList;
    QWidget* m_parent;
    int minCellWidth = 0;
    int spacing;
    int numRows;
    int numCols;
    int margin;

    void updateLayout(const QRect& rect);
};

} // namespace Ui
} // namespace Lamagotchi

#endif // FLEX_GRID_LAYOUT_H
