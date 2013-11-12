#include "gui/settingswindow.h"

SettingsWindow::SettingsWindow(QSettings *newSettings, QWidget *parent) :
  settings(newSettings), QDialog(parent)
{
  initWindow();

  QWidget::setFixedSize(sizeHint());
}

QSize SettingsWindow::sizeHint()
{
  return QSize(240, 320);
}

void SettingsWindow::initWindow()
{
  setWindowTitle(APP_PRODUCT " Preferences");

  // Set up OK/Apply/Cancel buttons
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
      QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
  buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
  connect(buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this,
      SLOT(apply()));
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  // General tab
  QWidget *generalTab = new QWidget(this);
  QFormLayout *generalPage = new QFormLayout(generalTab);
  hotkey = new QLineEdit(this);
  generalPage->addRow(tr("Global hotkey"), hotkey);
  grid_xcells = new QSpinBox(generalTab);
  grid_xcells->setRange(1, 32);
  generalPage->addRow(tr("Vertical divisions"), grid_xcells);
  grid_ycells = new QSpinBox(generalTab);
  grid_ycells->setRange(1, 32);
  generalPage->addRow(tr("Horizontal divisions"), grid_ycells);

  // TODO(aarmea): More tabs for other functionality

  tabs = new QTabWidget(this);
  tabs->addTab(generalTab, tr("&General"));

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(tabs);
  layout->addWidget(buttonBox);
  setLayout(layout);
}

void SettingsWindow::accept()
{
  QDialog::accept();

  // Save the settings from the GUI to the QSettings object
  settings->setValue("hotkey", hotkey->text());
  settings->setValue("grid/xcells", grid_xcells->value());
  settings->setValue("grid/ycells", grid_ycells->value());

  // Emit a signal that the app can receive when settings have been changed
  emit settingsChanged();
}

void SettingsWindow::showEvent(QShowEvent *event)
{
  QDialog::showEvent(event);

  // Load the settings from the QSettings object to the GUI
  hotkey->setText(settings->value("hotkey").toString());
  grid_xcells->setValue(settings->value("grid/xcells").toInt());
  grid_ycells->setValue(settings->value("grid/ycells").toInt());
}
