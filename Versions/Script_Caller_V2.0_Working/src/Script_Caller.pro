TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    log_write.c \
    time_manager.c \
    scripts_file_reader.c \
    scripts_list_management.c \
    script_executioner.c \
    monitor.c

LIBS += -pthread

HEADERS += \
    log_write.h \
    time_manager.h \
    scripts_file_reader.h \
    scripts_list_management.h \
    script_executioner.h \
    monitor.h
