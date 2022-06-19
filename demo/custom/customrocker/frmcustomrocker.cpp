/**
 * @file frmcustomrocker.cpp
 * @author creekwater
 * @brief
 *
 * 使用摇杆控件的demo
 *
 * @version 0.1
 * @date 2022-06-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma execution_character_set("utf-8")

#include "frmcustomrocker.h"
#include "ui_frmcustomrocker.h"

frmCustomRocker::frmCustomRocker(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomRocker)
{
    ui->setupUi(this);
    connect(ui->customRocker, SIGNAL(moveAngle(double, double)), this, SLOT(moveAngle(double, double)));
}

frmCustomRocker::~frmCustomRocker()
{
    delete ui;
}

/**
 * @brief 接收摇杆控件传来的信号
 *
 * @param angle     角度
 * @param distance  距离
 */
void frmCustomRocker::moveAngle(double angle, double distance)
{
    ui->labAngle->setText(QString("角度: %1  距离: %2").arg(angle).arg(distance));
}

/**
 * @brief 设置摇杆只能在边缘移动
 *
 * @param arg1
 */
void frmCustomRocker::on_ckOnline_stateChanged(int arg1)
{
    ui->customRocker->setOnline(arg1 != 0);
}
