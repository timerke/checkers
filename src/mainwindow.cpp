#include <QDebug>
#include <QIcon>
#include <QMessageBox>
#include "authorizationdialog.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include "./ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * Конструктор основного окна.
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/image/icon.png"));
    ui->action_authorise->setIcon(QIcon(":/image/auth.png"));
    connect(ui->action_authorise, &QAction::triggered, this, &MainWindow::handle_authorization);
    ui->action_exit->setIcon(QIcon(":/image/exit.png"));
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::close);
    ui->action_play_english->setIcon(QIcon(":/image/eng.png"));
    connect(ui->action_play_english, &QAction::triggered, this, &MainWindow::handle_play_click);
    ui->action_play_russian->setIcon(QIcon(":/image/rus.png"));
    connect(ui->action_play_russian, &QAction::triggered, this, &MainWindow::handle_play_click);
    ui->action_settings->setIcon(QIcon(":/image/settings.png"));
    connect(ui->action_settings, &QAction::triggered, this, &MainWindow::handle_settings_click);
    ui->action_rules_for_english->setIcon(QIcon(":/image/eng.png"));
    connect(ui->action_rules_for_english, &QAction::triggered, this, &MainWindow::show_rules_for_english);
    ui->action_rules_for_russian->setIcon(QIcon(":/image/rus.png"));
    connect(ui->action_rules_for_russian, &QAction::triggered, this, &MainWindow::show_rules_for_russian);

    this->game = new Game();
    this->ui->widget->layout()->addWidget(this->game->field);
    connect(this->game, &Game::score_changed, this, &MainWindow::handle_score_change);
    connect(this->game, &Game::checker_pressed_or_released, this, &MainWindow::handle_checker_click);
    connect(this->game, &Game::winner_found, this, &MainWindow::show_winner);
}

/**
 * @brief MainWindow::~MainWindow
 * Деструктор основного окна.
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::handle_authorization
 * Слот показывает диалоговое окно авторизации игроков.
 */
void MainWindow::handle_authorization() {
    AuthorizationDialog *dialog = new AuthorizationDialog();
    if (dialog->exec()) {
        QString player_name = dialog->get_player_name();
    }
    delete dialog;
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
    if (this->sender() == this->ui->action_play_english) {
        qDebug() << "Старт игры в английские шашки";
        this->game->start_game(true);
    } else if (this->sender() == this->ui->action_play_russian) {
        qDebug() << "Старт игры в русские шашки";
        this->game->start_game(false);
    }
}

/**
 * @brief MainWindow::handle_score_change
 * Слот обрабатывает сигнал с изменением счета.
 */
void MainWindow::handle_score_change() {

}

/**
 * @brief MainWindow::handle_settings_click
 * Слот обрабатывает сигнал показать окно с настройками игры.
 */
void MainWindow::handle_settings_click() {
    SettingsDialog *dialog = new SettingsDialog();
    if (dialog->exec()) {

    }
    delete dialog;
}

/**
 * @brief MainWindow::show_rules_for_english
 * Метод выводит сообщение с правилами игры в английские шашки.
 */
void MainWindow::show_rules_for_english() {
    QMessageBox::information(this, "Правила игры в английские шашки",
                             "Первый ход делают чёрные шашки. «Простые» шашки могут ходить по диагонали "
                             "на одно поле вперед и бить только вперед. Дамка может ходить на одно поле "
                             "по диагонали вперед или назад, при взятии ходит только через одно поле в "
                             "любую сторону. Взятие шашки соперника является обязательным.<br>При "
                             "достижении последнего (восьмого от себя) горизонтального ряда простая шашка "
                             "превращается в дамку. Если простая достигла последнего ряда во время взятия,"
                             " то она превращается в дамку и останавливается, даже при возможности продолжить взятие.");
}

/**
 * @brief MainWindow::show_rules_for_english
 * Метод выводит сообщение с правилами игры в русские шашки.
 */
void MainWindow::show_rules_for_russian() {
    QMessageBox::information(this, "Правила игры в русские шашки",
                             "Первый ход делают чёрные шашки. «Простые» шашки могут ходить по диагонали "
                             "на одно поле вперед, а бить только вперед и назад. Дамка ходит вперед и "
                             "назад на любое поле той диагонали, на которой она стоит. Дамка бьет вперед "
                             "и назад, и становится на диагональ на любое свободное поле за побитой "
                             "шашкой.<br>При достижении последнего (восьмого от себя) горизонтального "
                             "ряда простая шашка превращается в дамку. Во время боя простая шашка может"
                             " превратиться в дамку и сразу продолжить бой по правилам дамки.");
}

/**
 * @brief MainWindow::show_winner
 * Слот показывает сообщение о победителе.
 * @param winner - победитель.
 */
void MainWindow::show_winner(Player *winner) {
    QMessageBox::information(this, "Информация", "Победил " + winner->name);
}
