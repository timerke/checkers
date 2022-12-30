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

public slots:
    void handle_authorization();
    void handle_checker_click(bool clicked);
    void handle_play_click();
    void handle_score_change();
    void show_rules_for_english();
    void show_rules_for_russian();
    void show_winner(Player *winner);

private:
    static const int PLAYER_NAME_LENGTH = 10;
    Field *field;
    Game *game;
    Ui::MainWindow *ui;  
};

#endif // MAINWINDOW_H
