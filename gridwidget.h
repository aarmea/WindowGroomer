#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <QMouseEvent>
#include <QPoint>

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

  QPoint findCellFromPos(QPoint pos);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  int cols;
  int rows;
  int border;
  QColor backColor;
  QColor inactiveCellColor;
  QColor activeCellColor;

  QRect activeCells;

  bool mouseDown;
  QPoint mouseDownCell;
};

QRect normalize(QRect rect);

#endif
