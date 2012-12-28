#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QxtGlobalShortcut>
#include <QWidget>
#include <QDesktopWidget>

#include <QSize>
#include <QKeySequence>
#include <QDialog>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>

#include "gridwidget.h"

class GridWindow : public QDialog
{
  Q_OBJECT
public:
  explicit GridWindow(QWidget *parent = 0);

  QSize sizeHint();

private slots:
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void shortcutPressed();

private:
  void initWindow();
  void initActions();
  void initTray();

  void showWindow();

  QxtGlobalShortcut *shortcut;

  // Grid positioning window
  GridWidget *gridSelect;
  int sqArea;

  // Tray icon and context menus
  QSystemTrayIcon *trayIcon;
  QMenu *trayMenu;
  QAction *prefsAction;
  QAction *aboutAction;
  QAction *quitAction;
};

#endif
