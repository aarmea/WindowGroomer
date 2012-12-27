CONFIG += \
  qxt

QXT += \
  core \
  gui

HEADERS = \
  gridwindow.h \
  gridwidget.h

SOURCES = \
  main.cpp \
  gridwindow.cpp \
  gridwidget.cpp

RESOURCES = windowgroomer.qrc

win32:RC_FILE = windowgroomer.rc
