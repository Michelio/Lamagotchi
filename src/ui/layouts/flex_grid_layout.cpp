#include "ui/layouts/flex_grid_layout.h"

#include <QWidget>
#include <cmath>

namespace Lamagotchi
{

namespace Ui
{

FlexGridLayout::FlexGridLayout(QWidget* parent, int spacing, int margin)
    : QLayout(parent), m_parent(parent), spacing(spacing), margin(margin)
{
    setContentsMargins(margin, margin, margin, margin);
    numCols = 1;
    numRows = itemList.count();
}

FlexGridLayout::~FlexGridLayout()
{
    QLayoutItem* item;
    while ((item = takeAt(0)))
        delete item;
}

void FlexGridLayout::addItem(QLayoutItem* item)
{
    minCellWidth = std::max(minCellWidth, item->minimumSize().width());
    itemList.append(item);
}

QSize FlexGridLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlexGridLayout::minimumSize() const
{
    int width = numCols * (minCellWidth + spacing) + margin * 2;
    width -= spacing;
    int height = margin * 2;
    int itemHeight = 0;

    int count = itemList.count();
    for (int i = 0, col = 1; i < count; ++i, ++col)
    {
        itemHeight = std::max(itemHeight, itemList.value(i)->minimumSize().height());

        if (col == numCols || i == (count - 1))
        {
            height += itemHeight;
            height += spacing;
            itemHeight = 0;
            col = 0;
        }
    }

    height -= spacing;

    return QSize(width, height);
}

void FlexGridLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    updateLayout(rect);

    if (m_parent)
    {
        m_parent->updateGeometry();
    }
}

QLayoutItem* FlexGridLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem* FlexGridLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
    {
        return itemList.takeAt(index);
    }
    return nullptr;
}

int FlexGridLayout::count() const
{
    return itemList.size();
}

void FlexGridLayout::updateLayout(const QRect& rect)
{
    int availableWidth = rect.width() - margin * 2;
    numCols = (availableWidth + spacing) / (minCellWidth + spacing);
    int itemCount = itemList.size();

    numCols = std::max(1, numCols);
    numRows = std::ceil(static_cast<double>(itemCount) / numCols);

    int x = 0;
    int y = rect.y() + margin;
    int lineHeight = 0;

    for (int i = 0; i < itemCount; ++i)
    {
        QLayoutItem* item = itemList[i];
        int col = i % numCols;

        x = rect.x() + margin + col * (minCellWidth + spacing);

        if (i % numCols == 0 && i)
        {
            y = y + lineHeight + spacing;
            lineHeight = 0;
        }

        item->setGeometry(QRect{x, y, minCellWidth, item->sizeHint().height()});

        lineHeight = std::max(lineHeight, item->sizeHint().height());
    }
}

} // namespace Ui
} // namespace Lamagotchi
