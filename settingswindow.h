#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QSettings>

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
  explicit SettingsWindow(QSettings *newSettings, QWidget *parent = 0);

  QSize sizeHint();

public slots:
  void accept();

protected slots:
  void showEvent(QShowEvent *event);

signals:
  void settingsChanged();

private:
  void initWindow();

  QSettings *settings;

  QTabWidget *tabs;

  // General tab fields
  QSpinBox *verticalDivisions;
  QSpinBox *horizontalDivisions;

  // TODO(aarmea): Make the keyboard shortcut configurable
};

#endif
