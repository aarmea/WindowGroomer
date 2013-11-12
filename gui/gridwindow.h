#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QxtGlobalShortcut>
#include <QWidget>
#include <QDesktopWidget>
#include <QSettings>

#include <QSize>
#include <QKeySequence>
#include <QDialog>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>

#include <QMessageBox>
#include <QString>

#include <QtCore/qmath.h>

#include "gui/gridwidget.h"
#include "gui/settingswindow.h"
#include "wm/nativewindow.h"

class GridWindow : public QDialog
{
  Q_OBJECT
public:
  explicit GridWindow(QWidget *parent = 0);

  QSize sizeHint();

public slots:
  void receiveGrid(const QRect &grid);
  void loadSettings();

private slots:
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void shortcutPressed();

  void showAbout();
  void showPrefs();

private:
  void initWindow();
  void initActions();
  void initTray();
  void initSettings();

  void showWindow();

  QxtGlobalShortcut *shortcut;

  // Grid positioning window
  GridWidget *gridSelect;
  int sqArea;

  // TODO(aarmea): Keep track of windows positioned with WindowGroomer and
  // what windows they're next to.
  NativeWindow window;

  // Settings window
  QSettings *settings;
  SettingsWindow *settingsWindow;

  // Tray icon and context menus
  QSystemTrayIcon *trayIcon;
  QMenu *trayMenu;
  QAction *prefsAction;
  QAction *aboutAction;
  QAction *quitAction;
};

QRect getAreaFromCells(QRect cells, QSize gridSize, QRect availArea);

#endif
