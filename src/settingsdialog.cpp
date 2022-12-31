#include <QIcon>
#include "settingsdialog.h"
#include "./ui_settingsdialog.h"

/**
 * @brief SettingsDialog::SettingsDialog
 * Конструктор класс для окна с настройками.
 */
SettingsDialog::SettingsDialog() : QDialog(), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/icon.png"));

    ui->button_field_left->setIcon(QIcon(":/image/left.png"));
    connect(ui->button_field_left, &QPushButton::clicked, this, &SettingsDialog::scroll_fields);
    ui->button_field_right->setIcon(QIcon(":/image/right.png"));
    connect(ui->button_field_right, &QPushButton::clicked, this, &SettingsDialog::scroll_fields);

    ui->button_checker_left->setIcon(QIcon(":/image/left.png"));
    connect(ui->button_checker_left, &QPushButton::clicked, this, &SettingsDialog::scroll_checkers);
    ui->button_checker_right->setIcon(QIcon(":/image/right.png"));
    connect(ui->button_checker_right, &QPushButton::clicked, this, &SettingsDialog::scroll_checkers);

    ui->button_ok->setFocus();
    connect(ui->button_cancel, &QPushButton::clicked, this, &SettingsDialog::reject);
}

/**
 * @brief SettingsDialog::~SettingsDialog
 * Деструктор класса.
 */
SettingsDialog::~SettingsDialog() {
    delete ui;
}

/**
 * @brief SettingsDialog::scroll_checkers
 */
void SettingsDialog::scroll_checkers() {

}

/**
 * @brief SettingsDialog::scroll_fields
 */
void SettingsDialog::scroll_fields() {

}
