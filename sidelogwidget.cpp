#include "sidelogwidget.h"
#include "./ui_sidelogwidget.h"

SideLogWidget::SideLogWidget(QWidget *parent): QWidget(parent), ui(new Ui::SideLogWidget){
    ui->setupUi(this);
}

SideLogWidget::~SideLogWidget(){
    delete ui;
}
