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
  qreal sqrAspect = sqrt(aspect);
  return QSize(sqArea*sqrAspect, sqArea/sqrAspect);
}

void GridWindow::receiveGrid(const QRect &grid)
{
  QSize gridSize = gridSelect->gridSize();
  QDesktopWidget *screens = qApp->desktop();
  QRect availArea = screens->availableGeometry(this);
  QRect newSize = getAreaFromCells(grid, gridSize, availArea);

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

void GridWindow::initWindow()
{
  gridSelect = new GridWidget(this);
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(gridSelect);
  setLayout(layout);

  connect(gridSelect, SIGNAL(sendGrid(QRect)), this, SLOT(receiveGrid(QRect)));
}

void GridWindow::initActions()
{
  prefsAction = new QAction(tr("&Preferences"), this);
  // TODO: make a preferences popup and connect the action to the popup

  aboutAction = new QAction(tr("&About"), this);
  // TODO: make an about popup and connect the action to the popup

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
  return QRect(availArea.x() + qRound(grid.x()*cellWidth),
    availArea.y() + qRound(grid.y()*cellWidth),
    qRound(grid.width()*cellWidth), qRound(grid.height()*cellHeight));
}
