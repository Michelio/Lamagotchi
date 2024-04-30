#include "ui/layouts/flex_grid_layout.h"

#include <cmath>

namespace Lamagotchi
{

namespace Ui
{

FlexGridLayout::FlexGridLayout(QWidget* parent, int margin, int spacing) : QLayout(parent), spacing(6), margin(margin)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlexGridLayout::~FlexGridLayout()
{
    QLayoutItem* item;
    while ((item = takeAt(0)))
        delete item;
}

void FlexGridLayout::addItem(QLayoutItem* item)
{
    minColWidth = std::max(minColWidth, item->minimumSize().width());
    itemList.append(item);
}

QSize FlexGridLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlexGridLayout::minimumSize() const
{
    int width = 0;
    int height = 0;

    for (const QLayoutItem* item : itemList)
    {
        QSize itemSize = item->minimumSize();
        width = qMax(width, itemSize.width());
        height = qMax(height, itemSize.height());
    }

    return QSize(width * numCols + spacing * (numCols - 1), height + margin * 2);
}

void FlexGridLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    updateLayout(rect);
}

QLayoutItem* FlexGridLayout::itemAt(int index) const
{
    if (index >= 0 && index < itemList.size())
    {
        return itemList[index];
    }
    return nullptr;
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
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    auto effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int y = effectiveRect.y();

    int availableWidth = rect.width();
    int maxCols = availableWidth / minColWidth;

    maxCols = std::max(1, maxCols);

    int itemCount = itemList.size();
    numRows = std::ceil(static_cast<double>(itemCount) / maxCols);
    numCols = std::ceil(static_cast<double>(itemCount) / numRows);

    int itemWidth = (availableWidth - spacing * (numCols - 1) - left - right) / numCols;

    int i = 0;
    int lineHeight = 0;
    for (const auto& item : std::as_const(itemList))
    {
        int col = i % numCols;
        int x = 0;

        if (itemWidth > item->maximumSize().width())
        {
            x = effectiveRect.x() + col * (itemWidth + spacing) + itemWidth / 2 - item->maximumSize().width() / 2;
        }

        else
        {
            x = effectiveRect.x() + col * (itemWidth + spacing);
        }

        if (i % numCols == 0)
        {
            y = y + lineHeight + spacing;
            lineHeight = 0;
        }

        item->setGeometry(QRect{x, y, itemWidth, item->sizeHint().height()});

        lineHeight = std::max(lineHeight, item->sizeHint().height());
        ++i;
    }
}

} // namespace Ui
} // namespace Lamagotchi
