#include "gridwindow.h"

GridWindow::GridWindow()
{
  initWindow();
  initActions();
  initTray();

  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void GridWindow::closeEvent(QCloseEvent *event)
{
  if (trayIcon->isVisible()) {
    hide();
    event->ignore();
  }
}

void GridWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  if (reason == QSystemTrayIcon::DoubleClick) {
    show();
  }
}

void GridWindow::initWindow()
{
  // gridSelect = new GridWidget();
  gridSelect = new QLabel("Hello World!");
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(gridSelect);
  setLayout(layout);
}

void GridWindow::initActions()
{
  prefsAction = new QAction(tr("&Preferences"), this);
  // TODO: make a preferences popup and connect the action to the popup

  aboutAction = new QAction(tr("&About"), this);
  // TODO: make an about popup and connect the action to the popup

  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
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
