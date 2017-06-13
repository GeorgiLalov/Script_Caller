TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    log_write.c \
    time_manager.c

LIBS += -pthread

HEADERS += \
    log_write.h \
    time_manager.h
