#include "widget.h"
#include <QApplication>
#include "config/system_config.h"

bool global_b_serial_is_open = false;
bool global_b_tr_data_ctrl_interface_enabled = false;
int global_i_page_index = 0;
int global_i_current_channel_index = 0;
bool global_b_channel_has_been_tune = false;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
