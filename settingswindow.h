#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QWidget>

#include <QSize>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>

class SettingsWindow : public QDialog
{
  Q_OBJECT
public:
  explicit SettingsWindow(QWidget *parent = 0);

  QSize sizeHint();

public slots:
  // TODO

private slots:
  // TODO

private:
  void initWindow();

  QTabWidget *tabs;

  // General tab fields
  QSpinBox *verticalDivisions;
  QSpinBox *horizontalDivisions;
};

#endif
