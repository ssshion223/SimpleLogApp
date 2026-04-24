#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "configuration.h"
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    configdata getresult();
    void loadconfigUI(const configdata &cfg);
private:
    Ui::Settings *ui;
    configdata cfg_;
private slots:
    void ok_button_cb();
};

#endif // SETTINGS_H
