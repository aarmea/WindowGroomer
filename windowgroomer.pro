CONFIG += \
  qxt

QXT += \
  core \
  gui

HEADERS = \
  gridwindow.h \
  gridwidget.h \
  nativewindow.h

SOURCES = \
  main.cpp \
  gridwindow.cpp \
  gridwidget.cpp \
  nativewindow.cpp

RESOURCES = windowgroomer.qrc

win32:RC_FILE = windowgroomer.rc
