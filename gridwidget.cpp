#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent) :
  QWidget(parent),
  cols(4), rows(3),
  backColor(Qt::black),
  inactiveCellColor(Qt::darkGray),
  activeCellColor(Qt::lightGray)
{}

void GridWidget::resizeGrid(int newCols, int newRows)
{
  cols = newCols;
  rows = newRows;
}

void GridWidget::setColors(QColor back, QColor inactive, QColor active)
{
  backColor = back;
  inactiveCellColor = inactive;
  activeCellColor = active;
}

void GridWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  // Fill with background
  painter.fillRect(rect(), backColor);

  // Draw inactive cells
  paintCells(painter, QRect(0, 0, cols, rows), Inactive);

  // Draw active cells
  paintCells(painter, activeCells, Active);
}

void GridWidget::paintCells(QPainter &painter, QRect cells, CellStatus status)
{
  int border = 2;
  QColor color = (status == Active) ? activeCellColor : inactiveCellColor;
  int cellWidth = width() / cols;
  int cellHeight = height() / rows;
  for (int x = cells.left(); x <= cells.right(); ++x) {
    for (int y = cells.top(); y <= cells.bottom(); ++y) {
      QRect cell(x*cellWidth + border, y*cellHeight + border,
        cellWidth - 2*border, cellHeight - 2*border);
      painter.fillRect(cell, color);
    }
  }
}
