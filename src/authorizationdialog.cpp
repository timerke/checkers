#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "authorizationdialog.h"

/**
 * @brief AuthorizationDialog::AuthorizationDialog
 * Конструктор класса диалогового окна для авторизации.
 * @param name_of_black_player - имя игрока с черными (красными) шашками;
 * @param name_of_white_player - имя игрока с белыми (синими) шашками.
 */
AuthorizationDialog::AuthorizationDialog(QString name_of_black_player, QString name_of_white_player) : QDialog() {
    this->setWindowTitle("Авторизация");

    QGridLayout *g_layout = new QGridLayout();
    QLabel *label_white = new QLabel("Белый игрок");
    g_layout->addWidget(label_white, 0, 0);
    this->line_edit_white = new QLineEdit(name_of_white_player);
    g_layout->addWidget(this->line_edit_white, 0, 1);
    QLabel *label_black = new QLabel("Черный игрок");
    g_layout->addWidget(label_black, 1, 0);
    this->line_edit_black = new QLineEdit(name_of_black_player);
    g_layout->addWidget(this->line_edit_black, 1, 1);

    this->button_ok = new QPushButton("OK");
    connect(button_ok, &QPushButton::clicked, this, &AuthorizationDialog::handle_ok);
    this->button_cancel = new QPushButton("Отмена");
    connect(button_cancel, &QPushButton::clicked, this, &AuthorizationDialog::reject);
    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addStretch(1);
    h_layout->addWidget(this->button_ok);
    h_layout->addWidget(this->button_cancel);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(g_layout, 1);
    v_layout->addLayout(h_layout);
    this->setLayout(v_layout);
}

/**
 * @brief AuthorizationDialog::~AuthorizationDialog
 * Деструктор класса.
 */
AuthorizationDialog::~AuthorizationDialog() {

}

/**
 * @brief AuthorizationDialog::get_black_player_name
 * Метод возвращает имя игрока с черными шашками.
 * @return имя игрока с черными шашками.
 */
QString AuthorizationDialog::get_black_player_name() {
    return this->line_edit_black->text();
}

/**
 * @brief AuthorizationDialog::get_white_player_name
 * Метод возвращает имя игрока с белыми шашками.
 * @return имя игрока с белыми шашками.
 */
QString AuthorizationDialog::get_white_player_name() {
    return this->line_edit_white->text();
}

/**
 * @brief AuthorizationDialog::handle_ok
 * Слот обрабатывает клик по кнопке OK, когда игроки авторизовались.
 */
void AuthorizationDialog::handle_ok() {
    if (this->line_edit_black->text() != "" && this->line_edit_white->text() != "") {
        this->accept();
    }
}
