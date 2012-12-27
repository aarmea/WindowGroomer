#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QxtGlobalShortcut>

#include <QKeySequence>
#include <QDialog>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QVBoxLayout>

// Put this back when everything else is tested
// #include "gridwidget.h"
#include <QLabel>

class GridWindow : public QDialog
{
  Q_OBJECT
public:
  GridWindow();

protected:
  void closeEvent(QCloseEvent *event);

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
  // GridWidget *gridSelect;
  QLabel *gridSelect;

  // Tray icon and context menus
  QSystemTrayIcon *trayIcon;
  QMenu *trayMenu;
  QAction *prefsAction;
  QAction *aboutAction;
  QAction *quitAction;
};

#endif
