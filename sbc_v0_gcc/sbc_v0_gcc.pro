#-------------------------------------------------
#
# Project created by QtCreator 2020-02-25T09:27:51
#
#-------------------------------------------------

QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sbc_v0_gcc
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    link/linkbase.cpp \
    link/link_tr_module.cpp \
    control/system_ctrl.cpp \
    task_boot.cpp \
    control/tr_module_ctrl.cpp \
    msghandler/tr_msg_handler.cpp \
    database/db_manager.cpp \
    item/channel_item.cpp \
    keyhandle/key_handle.cpp

HEADERS  += widget.h \
    link/linkbase.h \
    link/link_tr_module.h \
    config/system_config.h \
    control/system_ctrl.h \
    task_boot.h \
    config/system_message_list.h \
    control/tr_module_ctrl.h \
    msghandler/tr_msg_handler.h \
    database/db_manager.h \
    item/channel_item.h \
    keyhandle/key_handle.h

FORMS    += widget.ui
