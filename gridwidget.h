#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

#include <QApplication>

class GridWidget : public QWidget
{
  Q_OBJECT
public:
  explicit GridWidget(QWidget *parent = 0);

  void resizeGrid(int newCols, int newRows);

private:
  int cols;
  int rows;
};

#endif
