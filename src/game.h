#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QVector>
#include "checker.h"
#include "field.h"

struct {
    CheckerType checker_type;
    Checker **checkers;
    int current_account;
    QString name;
    int number_of_wins;
} typedef Player;

/**
 * @brief The Game class
 * Класс для управления правилами игры.
 */
class Game : public QObject
{
    Q_OBJECT

public:
    Game(Field *field);
    ~Game();
    bool need_authorization();
    void set_name_for_black_player(QString name);
    void set_name_for_white_player(QString name);
    void start_game();

private:
    int calculate_step(Cell *cell_1, Cell *cell_2);
    Checker * check_enemy_checker_at_cell(Cell *cell);
    bool check_possibility_of_move(Cell *cell);
    void find_winner();
    int get_step();
    void init_player(CheckerType checker_type, Player *player, Checker **checkers);
    void make_move(Checker *checker);
    void make_move_transition();
    void remove_enemy_checkers();
    void set_condition_for_players_run();

public slots:
    void handle_checker_click(bool ckicked, Checker *checker);
    void handle_checker_move(QPointF pos);

signals:
    void account_changed();
    void checker_pressed_or_released(bool pressed);
    void winner_found(Player *winner);

public:
    Player black_player;
    Player white_player;

private:
    QVector<Cell *> checker_path;
    Field *field;
    Player *player_to_run;
    Player *player_to_wait;
};

#endif // GAME_H
