#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QKeyEvent>
#include "task_boot.h"
#include "control/system_ctrl.h"
#include "control/tr_module_ctrl.h"
#include "database/db_manager.h"
#include "keyhandle/key_handle.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QString getModulationType(int);
    QString getPowerLevel(int);
    void updateChannelInfo(int);

protected:

    void keyPressEvent(QKeyEvent *);



public slots:

    void slot_update_text_browser(int,QString);

    void slot_update_stacked_widget(int);

    void slot_update_system_log(int,QString);

    void slot_update_channel_info(int);


private slots:
    void on_stackedWidget_currentChanged(int arg1);
};

#endif // WIDGET_H
