#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent) :
  QWidget(parent), cols(4), rows(3)
{}

void GridWidget::resizeGrid(int newCols, int newRows)
{
  cols = newCols;
  rows = newRows;
}
