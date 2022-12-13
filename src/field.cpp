#include "field.h"

#define MIN_SIZE 100

/**
 * @brief Field::Field
 * Конструктор класса с игровым полем.
 */
Field::Field() : QGraphicsView() {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(MIN_SIZE);
    this->setMinimumWidth(MIN_SIZE);

    scene = new QGraphicsScene();
    this->setScene(scene);
    this->create_cells();

    this->create_checkers(CheckerType::BLACK_CHECKER, black_checkers);
    this->create_checkers(CheckerType::WHITE_CHECKER, white_checkers);
}

/**
 * @brief Field::~Field
 * Деструктор класса.
 */
Field::~Field() {
    delete scene;
}

/**
 * @brief Field::check_empty_cell
 * Метод проверяет, находится ли в указанной ячейке какая-нибудь шашка.
 * @param cell - ячейка, которую нужно проверить.
 * @return true, если в ячейке нет шашки.
 */
bool Field::check_empty_cell(Cell *cell) {
    for (int i = 0; i < this->CHECKERS_NUMBER; i++) {
        if (this->black_checkers[i]->isVisible() && this->black_checkers[i]->cell == cell) {
            return false;
        }
        if (this->white_checkers[i]->isVisible() && this->white_checkers[i]->cell == cell) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Field::create_cells
 * Метод создает ячейки и помещает их на сцену.
 */
void Field::create_cells() {
    this->scene->setBackgroundBrush(QBrush(QColor(208, 208, 208)));
    for (int row = 0; row < this->CELLS_NUMBER; row++) {
        for (int column = 0; column < this->CELLS_NUMBER; column++) {
            this->cells[row][column] = new Cell(row, column);
            this->scene->addItem(this->cells[row][column]);
        }
    }
    this->draw_cells();
}

/**
 * @brief Field::create_checkers
 * Метод создает шашки заданного типа (черные или белые) и помещает их на сцену.
 * @param checker_type - тип шашек (черные или белые), которые нужно создать;
 * @param checkers - массив, куда сохраняются шашки.
 */
void Field::create_checkers(CheckerType checker_type, Checker **checkers) {
    for (int i = 0; i < this->CHECKERS_NUMBER; i++) {
        checkers[i] = new Checker(checker_type);
        this->scene->addItem(checkers[i]);
    }
}

/**
 * @brief Field::draw_cells
 * Метод рисует ячейки на шашечной доске.
 */
void Field::draw_cells() {
    int min_size = qMin(this->size().height(), this->size().width());
    this->scene->setSceneRect(0, 0, min_size, min_size);
    this->cell_size = min_size / this->CELLS_NUMBER;
    for (int row = 0; row < this->CELLS_NUMBER; row++) {
        for (int column = 0; column < this->CELLS_NUMBER; column++) {
            int x = column * this->cell_size;
            int y = row * this->cell_size;
            this->cells[row][column]->setRect(x, y, this->cell_size, this->cell_size);
        }
    }
}

/**
 * @brief Field::draw_checkers
 * Метод рисует шашки на шашечной доске.
 */
void Field::draw_checkers() {
    for (int i = 0; i < this->CHECKERS_NUMBER; i++) {
        this->black_checkers[i]->redraw();
        this->white_checkers[i]->redraw();
    }
}

/**
 * @brief Field::find_cell_at_pos
 * Метод находит ячейку, которой принадлежит указанная точка.
 * @param pos - точка.
 * @return найденная ячейка.
 */
Cell * Field::find_cell_at_pos(QPointF &pos) {
    for (int row = 0; row < this->CELLS_NUMBER; row++) {
        for (int column = 0; column < this->CELLS_NUMBER; column++) {
            if (this->cells[row][column]->check_pos_in_cell(pos)) {
                return this->cells[row][column];
            }
        }
    }
    return nullptr;
}

/**
 * @brief Field::get_black_checkers
 * Метод возвращает указатель на массив черных (красных) шашек.
 * @return указатель на массив черных шашек.
 */
Checker ** Field::get_black_checkers() {
    return this->black_checkers;
}

/**
 * @brief Field::get_cell
 * Метод возвращает ячейку на указанных строке и столбце.
 * @param row - номер строки;
 * @param column - номер столбца.
 * @return ячейка.
 */
Cell * Field::get_cell(int row, int column) {
    return this->cells[row][column];
}

/**
 * @brief Field::get_white_checkers
 * Метод возвращает указатель на массив белых (синих) шашек.
 * @return указатель на массив белых шашек.
 */
Checker ** Field::get_white_checkers() {
    return this->white_checkers;
}

/**
 * @brief Field::resizeEvent
 * Переопределение метода, обрабатывающего событие изменения размера виджета.
 * @param event - событие изменения размера виджета.
 */
void Field::resizeEvent(QResizeEvent *event) {
    this->draw_cells();
    this->draw_checkers();
    QGraphicsView::resizeEvent(event);
}

/**
 * @brief Field::set_checkers_to_init_pos
 * Метод восстанавливает исходное состояние шашек перед игрой.
 */
void Field::set_checkers_to_init_pos() {
    int black_index = 0;
    int white_index = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < this->CELLS_NUMBER; column++) {
            if ((row + column) % 2) {
                this->black_checkers[black_index]->set_position(this->cells[row][column]);
                this->black_checkers[black_index]->show();
                black_index++;
            }
            if ((7 - row + column) % 2) {
                this->white_checkers[white_index]->set_position(this->cells[7 - row][column]);
                this->white_checkers[white_index]->show();
                white_index++;
            }
        }
    }
}
