CONFIG += \
  qxt

QXT += \
  core \
  gui

HEADERS = \
  gridwindow.h

SOURCES = \
  main.cpp \
  gridwindow.cpp

RESOURCES = windowgroomer.qrc

win32:RC_FILE = windowgroomer.rc
