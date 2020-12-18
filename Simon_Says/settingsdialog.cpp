#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SettingsDialog::buttonClicked);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::panelSize()
{
    switch(ui->comboBoxPanel->currentIndex()) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 4;
        case 3:
            return 5;
        default:
            return 3;
    }
}

int SettingsDialog::lightTime()
{
    return ui->comboBoxTime->currentText().toInt();
}

int SettingsDialog::possibleAttempts()
{
    return ui->comboBoxAttempts->currentText().toInt();
}

void SettingsDialog::buttonClicked(QAbstractButton *button) {
    if(button->text() == "OK") {
        QVector<int> settings;
        settings.append(panelSize());
        settings.append(lightTime());
        settings.append(possibleAttempts());

        emit settingsChanged(settings);
    }
}
