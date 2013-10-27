#include "gridwindow.h"

GridWindow::GridWindow(QWidget *parent) :
  QDialog(parent), sqArea(256)
{
  initWindow();
  initActions();
  initTray();

  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

QSize GridWindow::sizeHint()
{
  // Calculate size from resolution of current screen
  QDesktopWidget *screens = qApp->desktop();
  QRect curScreenRes = screens->screenGeometry(this);
  qreal aspect = qreal(curScreenRes.width()) / curScreenRes.height();
  qreal sqrAspect = qSqrt(aspect);
  return QSize(sqArea*sqrAspect, sqArea/sqrAspect);
}

void GridWindow::receiveGrid(const QRect &grid)
{
  QSize gridSize = gridSelect->gridSize();
  QDesktopWidget *screens = qApp->desktop();
  QRect availArea = screens->availableGeometry(this);
  QRect newSize = getAreaFromCells(grid, gridSize, availArea);

  // Resizing twice fixes positioning on a different monitor
  window.resize(newSize);
  if (window.resize(newSize)) {
    accept();
  } else {
    reject();
  }
}

void GridWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  if (reason == QSystemTrayIcon::DoubleClick) {
    showWindow();
  }
}

void GridWindow::shortcutPressed()
{
  showWindow();
}

void GridWindow::showAbout()
{
  QMessageBox about;
  QString aboutString;
  aboutString.sprintf(
    "%s %s\n"
    "%s\n"
    "Copyright (C) %s %s\n"
    "\n"
    "This program is free software: you can redistribute it and/or modify "
    "it under the terms of the GNU General Public License as published by "
    "the Free Software Foundation, either version 3 of the License, or "
    "(at your option) any later version.\n"
    "\n"
    "This program is distributed in the hope that it will be useful, "
    "but WITHOUT ANY WARRANTY; without even the implied warranty of "
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
    "GNU General Public License for more details.\n"
    "\n"
    "You should have received a copy of the GNU General Public License "
    "along with this program.  If not, see <http://www.gnu.org/licenses/>.",
    APP_PRODUCT, APP_VERSION, APP_DESCRIPTION, APP_COPYRIGHT, APP_COMPANY);
  about.setText(aboutString);
  about.exec();
}

void GridWindow::showPrefs()
{
  // TODO
}

void GridWindow::initWindow()
{
  gridSelect = new GridWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(gridSelect);
  setLayout(layout);

  connect(gridSelect, SIGNAL(sendGrid(QRect)), this, SLOT(receiveGrid(QRect)));
}

void GridWindow::initActions()
{
  prefsAction = new QAction(tr("&Preferences"), this);
  connect(prefsAction, SIGNAL(triggered()), this, SLOT(showPrefs()));

  aboutAction = new QAction(tr("&About"), this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

  shortcut = new QxtGlobalShortcut(this);
  connect(shortcut, SIGNAL(activated()), this, SLOT(shortcutPressed()));
  // TODO: make shortcut configurable, warn if shortcut is not available
  shortcut->setShortcut(QKeySequence("Ctrl+Shift+F12"));
}

void GridWindow::initTray()
{
  trayMenu = new QMenu(this);
  trayMenu->addAction(prefsAction);
  trayMenu->addAction(aboutAction);
  trayMenu->addSeparator();
  trayMenu->addAction(quitAction);

  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setContextMenu(trayMenu);
  trayIcon->setIcon(QIcon(":/images/icon.png"));
  trayIcon->show();
}

void GridWindow::showWindow()
{
  window.getFront();
  setWindowTitle(window.title());

  QWidget::setFixedSize(sizeHint());
  show();
  raise();
  activateWindow();
}

QRect getAreaFromCells(QRect grid, QSize gridSize, QRect availArea)
{
  qreal cellWidth = qreal(availArea.width()) / gridSize.width();
  qreal cellHeight = qreal(availArea.height()) / gridSize.height();
  int x = availArea.x() + qRound(grid.x()*cellWidth);
  int y = availArea.y() + qRound(grid.y()*cellHeight);
  int width = qRound(grid.width()*cellWidth);
  int height = qRound(grid.height()*cellHeight);
  return QRect(x, y, width, height);
}
