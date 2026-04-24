#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent): QDialog(parent), ui(new Ui::Settings) {
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Settings::ok_button_cb);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::ok_button_cb(){

    cfg_.autofold = ui->autofold->isChecked();
    cfg_.autostart = ui->autostart->isChecked();
    accept();
}
configdata Settings::getresult(){
    return cfg_;
}

void Settings::loadconfigUI(const configdata &cfg){
    cfg_.autofold = cfg.autofold;
    cfg_.autostart = cfg.autostart;
    ui->autofold->setChecked(cfg_.autofold);
    ui->autostart->setChecked(cfg_.autostart);
}