#include <QMessageBox>
#include "authorizationdialog.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * Конструктор основного окна.
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->action_authorise, &QAction::triggered, this, &MainWindow::handle_authorization);
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->action_play, &QAction::triggered, this, &MainWindow::handle_play_click);
    connect(ui->button_play, &QPushButton::clicked, this, &MainWindow::handle_play_click);

    this->field = new Field();
    this->ui->widget->layout()->addWidget(this->field);
    this->game = new Game(this->field);
    connect(this->game, &Game::account_changed, this, &MainWindow::handle_account_change);
    connect(this->game, &Game::checker_pressed_or_released, this, &MainWindow::handle_checker_click);
    connect(this->game, &Game::winner_found, this, &MainWindow::show_winner);

    this->font = ui->label_player_black->font();
    this->font.setBold(true);
    ui->label_player_black->setFont(font);
    ui->label_player_white->setFont(font);
}

/**
 * @brief MainWindow::~MainWindow
 * Деструктор основного окна.
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::handle_account_change
 * Слот обрабатывает сигнал с изменением счета.
 */
void MainWindow::handle_account_change() {
    this->show_player_data(&this->game->black_player, this->ui->label_player_black);
    this->show_player_data(&this->game->white_player, this->ui->label_player_white);
}

/**
 * @brief MainWindow::handle_authorization
 * Слот показывает диалоговое окно авторизации игроков.
 */
void MainWindow::handle_authorization() {
    AuthorizationDialog *dialog = new AuthorizationDialog(this->game->black_player.name, this->game->white_player.name);
    if (dialog->exec()) {
        this->game->black_player.name = dialog->get_black_player_name();
        this->show_player_data(&this->game->black_player, this->ui->label_player_black);
        this->game->white_player.name = dialog->get_white_player_name();
        this->show_player_data(&this->game->white_player, this->ui->label_player_white);
    }
}

/**
 * @brief MainWindow::handle_checker_click
 * Слот меняет курсор при клике на шашку.
 * @param clicked - если true, то пользователь кликает на шашку.
 */
void MainWindow::handle_checker_click(bool clicked) {
    if (clicked) {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    } else {
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

/**
 * @brief MainWindow::handle_play_click
 * Слот обрабатывает старт игры. Если игроки не авторизованы, то выводится окно авторизации.
 */
void MainWindow::handle_play_click() {
    if (this->game->need_authorization()) {
        this->handle_authorization();
    }
    this->game->start_game();
}

/**
 * @brief MainWindow::show_player_data
 * Метод показывает имя и счет игрока в окне приложения.
 * @param player - игрок;
 * @param label - виджет, в котором нужно показать информацию.
 */
void MainWindow::show_player_data(Player *player, QLabel *label) {
    QString name;
    QString color;
    QString info;
    if (player->checker_type == CheckerType::BLACK_CHECKER) {
        color = "color: \"#F08080\";";
        name = player->name.leftJustified(this->PLAYER_NAME_LENGTH, ' ');
        name = name.left(this->PLAYER_NAME_LENGTH);
        info = name + "   " + QString::number(player->current_account).rightJustified(2, '0');
    } else {
        color = "color: \"#6495ED\";";
        name = player->name.rightJustified(this->PLAYER_NAME_LENGTH, ' ');
        name = name.left(this->PLAYER_NAME_LENGTH);
        info = QString::number(player->current_account).rightJustified(2, '0') + "   " + name;
    }
    label->setStyleSheet(color);
    label->setText(info);
    label->setToolTip(player->name);
}

/**
 * @brief MainWindow::show_winner
 * Слот показывает сообщение о победителе.
 * @param winner - победитель.
 */
void MainWindow::show_winner(Player *winner) {
    QMessageBox::information(this, "Информация", "Победил " + winner->name);
}
