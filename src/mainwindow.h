#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QLabel>
#include <QMainWindow>
#include "field.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Класс для основного окна приложения.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void show_player_data(Player *player, QLabel *label);

public slots:
    void handle_account_change();
    void handle_authorization();
    void handle_checker_click(bool clicked);
    void handle_play_click();
    void show_rules_for_english();
    void show_rules_for_russian();
    void show_winner(Player *winner);

private:
    static const int PLAYER_NAME_LENGTH = 10;
    Field *field;
    QFont font;
    Game *game;
    Ui::MainWindow *ui;  
};

#endif // MAINWINDOW_H
