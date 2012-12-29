#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent) :
  QWidget(parent), mouseDown(false),
  cols(4), rows(3),
  backColor(Qt::black),
  inactiveCellColor(Qt::darkGray),
  activeCellColor(Qt::lightGray)
{}

QSize GridWidget::gridSize()
{
  return QSize(cols, rows); 
}

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

QPoint GridWidget::findCellFromPos(QPoint pos)
{
  int cellWidth = width() / cols;
  int cellHeight = height() / rows;
  return QPoint(pos.x()/cellWidth, pos.y()/cellHeight);
}

void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (mouseDown) {
    QPoint currentCell = findCellFromPos(event->pos());
    activeCells = normalize(QRect(mouseDownCell, currentCell));
    update();
  }
}

void GridWidget::mousePressEvent(QMouseEvent *event)
{
  mouseDown = true;
  mouseDownCell = findCellFromPos(event->pos());
}

void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
  emit sendGrid(activeCells);
  mouseDown = false;
  mouseDownCell = QPoint();
  activeCells = QRect();
  update();
}

// QRect::normalized() does not correctly normalize QRects that have height or
// width of -1
QRect normalize(QRect rect)
{
  int x1 = rect.left();
  int y1 = rect.top();
  int x2 = rect.left() + rect.width();
  int y2 = rect.top() + rect.height();

  int temp = 0;
  if (x2 <= x1) {
    temp = x1;
    x1 = x2 - 1;
    x2 = temp + 1;
  }
  if (y2 <= y1) {
    temp = y1;
    y1 = y2 - 1;
    y2 = temp + 1;
  }

  return QRect(x1, y1, x2-x1, y2-y1);
}
