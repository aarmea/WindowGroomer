#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QColor>

class GridWidget : public QWidget
{
  Q_OBJECT
public:
  explicit GridWidget(QWidget *parent = 0);

  void resizeGrid(int newCols, int newRows);
  void setColors(QColor back, QColor inactive, QColor active);

protected:
  enum CellStatus {Inactive, Active};

  void paintEvent(QPaintEvent *event);
  void paintCells(QPainter &painter, QRect cells,
    CellStatus status = Inactive);

private:
  int cols;
  int rows;
  int border;
  QColor backColor;
  QColor inactiveCellColor;
  QColor activeCellColor;

  QRect activeCells;
};

#endif
