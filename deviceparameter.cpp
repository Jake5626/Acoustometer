#include "deviceparameter.h"
#include "ui_deviceparameter.h"
#include <QDateTime>
DeviceParameter::DeviceParameter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceParameter)
{
    ui->setupUi(this);

    this->setMaximumSize(635,335);
    this->setMinimumSize(635,335);
    ui->spinBox_K->setRange(1,1000);
    ui->doubleSpinBox_H->setRange(0,99.99);
    ui->spinBox_T->setRange(1,300);
    ui->spinBox_OFF->setRange(10,60);
    ui->spinBox_instance->setRange(1,600);
    ui->label_ID->setText(QString::number(device_ID));
    setWindowModality(Qt::ApplicationModal);
    connect(ui->buttonApplay,SIGNAL(clicked()),this,SLOT(buttonApply_clicked()));
    connect(ui->buttonCancel,SIGNAL(clicked()),this,SLOT(buttonCancle_clicked()));
}

DeviceParameter::~DeviceParameter()
{
    delete ui;
}

void DeviceParameter::setLanguage(LANG *language)
{
    this->language = language;
    this->setWindowTitle(this->language->deviceSetting);
}

void DeviceParameter::buttonApply_clicked()
{
    QString s = "";
    s += QString::number(ui->spinBox_K->value()) + ",";
    s += QString::number(ui->doubleSpinBox_H->value()) + ",";
    s += QString::number(ui->comboBox_G->currentIndex()+1) + ",";

    if(ui->checkBox_F->isChecked())
        s += "1,";
    else
        s += "0,";
    if(ui->checkBox_T->isChecked())
        s += "1#" + QString::number(ui->spinBox_T->value()) + ",";
    else
        s += "0,";
    if(ui->checkBox_OFF->isChecked())
        s += "1#" + QString::number(ui->spinBox_OFF->value()) + ",";
    else
        s += "0,";
    s += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    emit DeviceParameterChanged(s);
    emit instance_t(ui->spinBox_instance->value()*1000);
    this->close();
}

void DeviceParameter::buttonCancle_clicked()
{
    this->close();
}

void DeviceParameter::setDeviceID(int id)
{
    this->device_ID = id;
    ui->label_ID->setText(QString::number(device_ID));
}

void DeviceParameter::sentAgent(PortAgent *agent)
{
    this->Agent = agent;
    connect(Agent,SIGNAL(deviceParameter(QStringList)),this,SLOT(initView(QStringList)));
}

void DeviceParameter::initView(QStringList Settings)
{
    ui->spinBox_K->setValue(Settings.at(0).toInt());
    ui->doubleSpinBox_H->setValue(Settings.at(1).toDouble());
    ui->comboBox_G->setCurrentIndex(Settings.at(2).toInt()-1);
    if(Settings.at(3)=="0")
        ui->checkBox_F->setChecked(false);
    else
        ui->checkBox_F->setChecked(true);

    if(Settings.at(4)=="0")
        ui->checkBox_T->setChecked(false);
    else
    {
        ui->checkBox_T->setChecked(true);
        ui->spinBox_T->setValue(Settings.at(4).toInt());
    }

    if(Settings.at(5)=="0")
        ui->checkBox_OFF->setChecked(false);
    else
    {
        ui->spinBox_OFF->setValue(Settings.at(5).toInt());
        ui->checkBox_OFF->setChecked(true);
    }
    ui->spinBox_instance->setValue(Agent->getT()/1000);

    ui->label_time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->label_time_device->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

}

