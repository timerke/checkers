#include <QDebug>
#include "game.h"

/**
 * @brief Game::Game
 * Конструктор класса, который управляет игрой.
 * @param field - шашечное поле.
 */
Game::Game(Field *field) {
    this->field = field;
    this->black_player = Player();
    this->init_player(CheckerType::BLACK_CHECKER, &this->black_player,
                      this->field->get_black_checkers());
    this->white_player = Player();
    this->init_player(CheckerType::WHITE_CHECKER, &this->white_player,
                      this->field->get_white_checkers());
    this->player_to_run = nullptr;
    this->player_to_wait = nullptr;
}

/**
 * @brief Game::~Game
 * Деструктор класса.
 */
Game::~Game() {

}

/**
 * @brief Game::calculate_step
 * Метод вычисляет шаг между указанными ячейками.
 * @param cell_1 - первая ячейка;
 * @param cell_2 - вторая ячейка.
 * @return шаг между ячейками.
 */
int Game::calculate_step(Cell *cell_1, Cell *cell_2) {
    int column_step = abs(cell_1->column - cell_2->column);
    int row_step = cell_2->row - cell_1->row;
    if (column_step != abs(row_step)) {
        return 3;
    }
    if (column_step > 2) {
        return 3;
    }
    return row_step;
}

/**
 * @brief Game::check_enemy_checker_at_cell
 * Метод проверяет, что на указанной ячейке есть вражеская шашка. Если на ячейке
 * есть вражеская шашка, то функция возвращает ее.
 * @param cell - ячейка.
 * @return вражеская шашка.
 */
Checker * Game::check_enemy_checker_at_cell(Cell *cell) {
    for (int i = 0; i < Field::CHECKERS_NUMBER; i++) {
        if (this->player_to_wait->checkers[i]->isVisible() &&
            this->player_to_wait->checkers[i]->cell == cell) {
            return this->player_to_wait->checkers[i];
        }
    }
    return nullptr;
}

/**
 * @brief Game::check_possibility_of_move
 * Метод проверяет возможность хода в указанную ячейку для английских шашек.
 * @param cell - ячейка.
 * @return true, если ход можно сделать.
 */
bool Game::check_possibility_of_move_english(Cell *cell) {
    if (cell && cell->check_black() && this->field->check_empty_cell(cell) &&
            this->checker_path.indexOf(cell) < 0) {
        int step = this->get_step();
        if (step == 1) {
            qDebug() << "До этого уже сделан ход на одну клетку";
            return false;
        }
        Cell *previous_cell = this->checker_path.last();
        int current_step = this->calculate_step(previous_cell, cell);
        if ((current_step == -1 && this->player_to_run->checker_type != CheckerType::WHITE_CHECKER) ||
            (current_step == 1 && this->player_to_run->checker_type != CheckerType::BLACK_CHECKER)) {
            qDebug() << "Назад на одну клетку ходить нельзя";
            return false;
        }
        if ((step == 0 || step == 2) &&
                ((current_step == 2 && this->player_to_run->checker_type == CheckerType::BLACK_CHECKER) ||
                 (current_step == -2 && this->player_to_run->checker_type == CheckerType::WHITE_CHECKER))) {
            int column_between = (cell->column + previous_cell->column) / 2;
            int row_between = (cell->row + previous_cell->row) / 2;
            Cell *cell_between = this->field->get_cell(row_between, column_between);
            if (this->check_enemy_checker_at_cell(cell_between)) {
                qDebug() << "Можно ходить на две клетки вперед, так как между клетками вражеская шашка";
                return true;
            }
            qDebug() << "Нельзя ходить на две клетки вперед, так как между клетками нет вражеской шашки";
            return false;
        }
        if (step == 0 && abs(current_step) == 1) {
            qDebug() << "Можно ходить на одну клетку вперед";
            return true;
        }
    }
    return false;
}

/**
 * @brief Game::check_possibility_of_move
 * Метод проверяет возможность хода в указанную ячейку для русских шашек.
 * @param cell - ячейка.
 * @return true, если ход можно сделать.
 */
bool Game::check_possibility_of_move_russian(Cell *cell) {
    return true;
}

/**
 * @brief Game::find_winner
 * Метод определяет, есть ли на данный момент победитель.
 */
void Game::find_winner() {
    int black_checkers_removed = 0;
    int white_checkers_removed = 0;
    for (int i = 0; i < Field::CHECKERS_NUMBER; i++) {
        if (!this->black_player.checkers[i]->isVisible()) {
            black_checkers_removed++;
        }
        if (!this->white_player.checkers[i]->isVisible()) {
            white_checkers_removed++;
        }
    }
    if (black_checkers_removed == Field::CHECKERS_NUMBER) {
        emit this->winner_found(&this->white_player);
    } else if (white_checkers_removed == Field::CHECKERS_NUMBER) {
        emit this->winner_found(&this->black_player);
    }
}

/**
 * @brief Game::get_step
 * Метод возвращает шаг, с которым шашка ходила в процессе хода игрока.
 * @return шаг в процессе хода.
 */
int Game::get_step() {
    if (this->checker_path.length() == 1) {
        return 0;
    }
    return this->calculate_step(this->checker_path.at(0), this->checker_path.at(1));
}

/**
 * @brief Game::handle_checker_click
 * Слот обрабатывает клик игрока по указанной шашке.
 * @param clicked - true, если шашка выбрана, иначе - освобождена;
 * @param checker - шашка.
 */
void Game::handle_checker_click(bool clicked, Checker *checker) {
    if (checker->checker_type == this->player_to_run->checker_type) {
        checker->handle_click(clicked);
        emit this->checker_pressed_or_released(clicked);
        if (!clicked) {
            this->make_move(checker);
            this->find_winner();
        } else {
            this->checker_path.clear();
            this->checker_path.append(checker->cell);
        }
    }
}

/**
 * @brief Game::handle_checker_move
 * Слот обрабатывает передвижение шашки мышкой.
 * @param pos - положение шашки.
 */
void Game::handle_checker_move(QPointF pos) {
    Cell *cell = this->field->find_cell_at_pos(pos);
    if ((this->*check_possibility_of_move)(cell)) {
        this->checker_path.append(cell);
        cell->select_cell_for_move();
    }
}

/**
 * @brief Game::init_player
 * Метод инициализирует объект игрока.
 * @param checker_type - тип игрока (черный или белый);
 * @param player - объект, который будет инициализирован;
 * @param checkers - шашки для игрока.
 */
void Game::init_player(CheckerType checker_type, Player *player, Checker **checkers) {
    player->checker_type = checker_type;
    player->checkers = checkers;
    player->name = "";
    player->score = 0;
    for (int i = 0; i < Field::CHECKERS_NUMBER; i++) {
        connect(checkers[i], &Checker::checker_moved, this, &Game::handle_checker_move);
        connect(checkers[i], &Checker::checker_pressed_or_released, this, &Game::handle_checker_click);
    }
}

/**
 * @brief Game::make_move
 * Метод делает ход шашкой при освобождении ее игроком.
 * @param checker - шашка.
 */
void Game::make_move(Checker *checker) {
    Cell *cell = this->checker_path.last();
    bool need_to_make_move_transition = cell != checker->cell;
    checker->set_position(cell);
    for (auto cell_in_path : this->checker_path) {
        cell_in_path->deselect_cell_for_move();
    }
    this->remove_enemy_checkers();
    this->checker_path.clear();
    if (need_to_make_move_transition) {
        this->make_move_transition();
    }
}

/**
 * @brief Game::make_move_transition
 * Метод осуществляет переход хода.
 */
void Game::make_move_transition() {
    if (this->player_to_run == &this->black_player) {
        this->player_to_run = &this->white_player;
        this->player_to_wait = &this->black_player;
    } else {
        this->player_to_run = &this->black_player;
        this->player_to_wait = &this->white_player;
    }
    this->set_condition_for_players_run();
}

/**
 * @brief Game::remove_enemy_checkers
 * Метод удаляет (съедает) вражесткую шашку при выполнении хода игроком.
 */
void Game::remove_enemy_checkers() {
    int number_of_removed_checkers = 0;
    for (int i = 0; i < this->checker_path.length() - 1; i++) {
        int column = (this->checker_path.at(i)->column + this->checker_path.at(i + 1)->column) / 2;
        int row = (this->checker_path.at(i)->row + this->checker_path.at(i + 1)->row) / 2;
        Cell *cell = this->field->get_cell(row, column);
        Checker *checker = this->check_enemy_checker_at_cell(cell);
        if (checker) {
            number_of_removed_checkers++;
            checker->hide();
        }
    }
    this->player_to_run->score += number_of_removed_checkers;
    if (number_of_removed_checkers) {
        emit this->score_changed();
    }
}

/**
 * @brief Game::set_condition_for_players_run
 * Метод делает неподвижными шашки игрока, который не ходит сейчас.
 */
void Game::set_condition_for_players_run() {
    for (int i = 0; i < Field::CHECKERS_NUMBER; i++) {
        this->player_to_run->checkers[i]->setFlag(QGraphicsItem::ItemIsMovable);
        this->player_to_wait->checkers[i]->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}

/**
 * @brief Game::set_name_for_black_player
 * Метод задает имя игрока с черными (красными) шашками.
 * @param name - имя игрока.
 */
void Game::set_name_for_black_player(QString name) {
    this->black_player.name = name;
}

/**
 * @brief Game::set_name_for_white_player
 * Метод задает имя игрока с белыми (синими) шашками.
 * @param name - имя игрока.
 */
void Game::set_name_for_white_player(QString name) {
    this->white_player.name = name;
}

/**
 * @brief Game::start_game
 * Метод начинает игру.
 * @param english - если true, то начинается игра в английские шашки, иначе в русские.
 */
void Game::start_game(bool english) {
    this->field->set_checkers_to_init_pos(1);
    this->black_player.score = 0;
    this->white_player.score = 0;
    this->player_to_run = &this->black_player;
    this->player_to_wait = &this->white_player;
    this->set_condition_for_players_run();
    if (english) {
        this->check_possibility_of_move = &Game::check_possibility_of_move_english;
    } else {
        this->check_possibility_of_move = &Game::check_possibility_of_move_russian;
    }
    emit this->score_changed();
}
