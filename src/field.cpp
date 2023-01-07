#include <QDebug>
#include "field.h"

#define MIN_SIZE 100

/**
 * @brief Field::Field
 * Конструктор класса с игровым полем.
 * @param row_number - количество строк;
 * @param column_number - количество столбцов;
 * @param checker_number - количество шашек каждого типа (черных и белых).
 */
Field::Field(int row_number, int column_number, int checker_number) : QGraphicsView() {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(MIN_SIZE);
    this->setMinimumWidth(MIN_SIZE);

    this->checker_number = checker_number;
    this->column_number = column_number;
    this->row_number = row_number;
    this->scene = new QGraphicsScene();
    this->setScene(this->scene);
    this->create_cells();

    this->create_checkers(CheckerType::BLACK_CHECKER, &this->black_checkers);
    this->create_checkers(CheckerType::WHITE_CHECKER, &this->white_checkers);
}

/**
 * @brief Field::~Field
 * Деструктор класса.
 */
Field::~Field() {
    delete []this->black_checkers;
    delete []this->white_checkers;
    for (int row = 0; row < this->row_number; row++) {
        delete []this->cells[row];
    }
    delete []this->cells;
    delete this->scene;
}

/**
 * @brief Field::check_empty_cell
 * Метод проверяет, находится ли в указанной клетке какая-нибудь шашка.
 * @param cell - клетка, которую нужно проверить.
 * @return true, если в клетке нет шашки.
 */
bool Field::check_empty_cell(Cell *cell) {
    for (int i = 0; i < this->checker_number; i++) {
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
 * Метод создает клетки и помещает их на сцену.
 */
void Field::create_cells() {
    this->scene->setBackgroundBrush(QBrush(QColor(208, 208, 208)));
    this->cells = new Cell **[this->row_number];
    for (int row = 0; row < this->row_number; row++) {
        this->cells[row] = new Cell *[this->column_number];
        for (int column = 0; column < this->column_number; column++) {
            CellType cell_type = this->get_cell_type(row, column);
            QColor color = this->get_cell_color(cell_type);
            this->cells[row][column] = new Cell(row, column, cell_type, color);
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
void Field::create_checkers(CheckerType checker_type, Checker ***checkers) {
    *checkers = new Checker *[this->checker_number];
    for (int i = 0; i < this->checker_number; i++) {
        (*checkers)[i] = new Checker(i, checker_type);
        this->scene->addItem((*checkers)[i]);
    }
}

/**
 * @brief Field::draw_cells
 * Метод рисует клетки на шашечной доске.
 */
void Field::draw_cells() {
    qreal height = this->size().height() / this->row_number;
    qreal width = this->size().width() / this->column_number;
    qreal cell_size = qMin(height, width);
    this->scene->setSceneRect(0, 0, this->column_number * cell_size, this->row_number * cell_size);
    for (int row = 0; row < this->row_number; row++) {
        for (int column = 0; column < this->column_number; column++) {
            int x = column * cell_size;
            int y = row * cell_size;
            this->cells[row][column]->setRect(x, y, cell_size, cell_size);
        }
    }
}

/**
 * @brief Field::draw_checkers
 * Метод рисует шашки на шашечной доске.
 */
void Field::draw_checkers() {
    for (int i = 0; i < this->checker_number; i++) {
        this->black_checkers[i]->redraw();
        this->white_checkers[i]->redraw();
    }
}

/**
 * @brief Field::find_cell_at_pos
 * Метод находит клетку, которой принадлежит указанная точка.
 * @param pos - точка.
 * @return найденная клетка.
 */
Cell * Field::find_cell_at_pos(QPointF &pos) {
    for (int row = 0; row < this->row_number; row++) {
        for (int column = 0; column < this->column_number; column++) {
            if (this->cells[row][column]->check_pos_in_cell(pos)) {
                return this->cells[row][column];
            }
        }
    }
    return nullptr;
}

/**
 * @brief Field::get_black_checkers
 * Метод возвращает указатель на массив черных шашек.
 * @return указатель на массив черных шашек.
 */
Checker ** Field::get_black_checkers() {
    return this->black_checkers;
}

/**
 * @brief Field::get_cell
 * Метод возвращает клетку на указанных строке и столбце.
 * @param row - номер строки;
 * @param column - номер столбца.
 * @return клетка.
 */
Cell * Field::get_cell(int row, int column) {
    return this->cells[row][column];
}

/**
 * @brief Field::get_cell_color
 * Метод возвращает цвет клетки.
 * @param cell_type - тип клетки (черная или белая).
 * @return цвет клетки.
 */
QColor Field::get_cell_color(CellType cell_type) {
    return cell_type == CellType::BLACK_CELL ? this->color_for_black_cells : this->color_for_white_cells;
}

/**
 * @brief Field::get_cell_type
 * Метод возвращает тип клетки (черная или белая).
 * @param row - номер строки на шашечном поле;
 * @param column - номер столбца на шашечном поле.
 * @return тип клетки.
 */
CellType Field::get_cell_type(int row, int column) {
    if ((row + column) % 2) {
        return CellType::BLACK_CELL;
    }
    return CellType::WHITE_CELL;
}

/**
 * @brief Field::get_white_checkers
 * Метод возвращает указатель на массив белых шашек.
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
 * @brief Field::set_cell_colors
 * Метод задает новые цвета для черных и белых клеток.
 * @param black - новый цвет для черных клеток;
 * @param white - новый цвет для белых клеток.
 */
void Field::set_cell_colors(QColor black, QColor white) {
    this->color_for_black_cells = black;
    this->color_for_white_cells = white;
    for (int row = 0; row < this->row_number; row++) {
        for (int column = 0; column < this->column_number; column++) {
            CellType cell_type = this->get_cell_type(row, column);
            this->cells[row][column]->set_cell_color(this->get_cell_color(cell_type));
        }
    }
}

/**
 * @brief Field::set_checkers_to_init_pos
 * Метод восстанавливает исходное состояние шашек перед игрой.
 * @param checker_variant - вариант набора шашек.
 */
void Field::set_checkers_to_init_pos(int checker_variant) {
    int index = 0;
    int checker_index = 0;
    while (checker_index < this->checker_number) {
        int row = index / this->column_number;
        int column = index % this->column_number;
        if (this->cells[row][column]->check_black()) {
            this->black_checkers[checker_index]->change_checker_status(false, checker_variant);
            this->black_checkers[checker_index]->set_position(this->cells[row][column]);
            this->black_checkers[checker_index]->show();
            checker_index++;
        }
        index++;
    }
    index = 0;
    checker_index = 0;
    while (checker_index < this->checker_number) {
        int row = this->row_number - index / this->column_number - 1;
        int column = index % this->column_number;
        if (this->cells[row][column]->check_black()) {
            this->white_checkers[checker_index]->change_checker_status(false, checker_variant);
            this->white_checkers[checker_index]->set_position(this->cells[row][column]);
            this->white_checkers[checker_index]->show();
            checker_index++;
        }
        index++;
    }
}
