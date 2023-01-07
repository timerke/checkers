#include <QPen>
#include "cell.h"

/**
 * @brief Cell::Cell
 * Конструктор класса для клетки на шашечной доске.
 * @param row - номер строки на шашечной доске для клетки;
 * @param column - номер столбца на шашечной доске для клетки;
 * @param cell_type - тип клетки (черная или белая);
 * @param cell_color - цвет клетки.
 */
Cell::Cell(int row, int column, CellType cell_type, QColor cell_color) : QGraphicsRectItem() {
    this->cell_color = cell_color;
    this->cell_type = cell_type;
    this->column = column;
    this->row = row;
    QPen pen(Qt::black);
    this->setPen(pen);
    this->setBrush(QBrush(cell_color));
}

/**
 * @brief Cell::~Cell
 * Деструктор класса.
 */
Cell::~Cell() {

}

/**
 * @brief Cell::check_black
 * Метод проверяет, является ли клетка черной.
 * @return true, если клетка черная.
 */
bool Cell::check_black() {
    return this->cell_type == CellType::BLACK_CELL;
}

/**
 * @brief Cell::check_pos_in_cell
 * Метод проверяет, что указанная точка находится внутри клетки.
 * @param pos - точка.
 * @return true, если точка внутри клетки.
 */
bool Cell::check_pos_in_cell(QPointF pos) {
    QRectF rect = this->rect();
    if (rect.x() < pos.x() && pos.x() < rect.x() + rect.width() &&
        rect.y() < pos.y() && pos.y() < rect.y() + rect.height()) {
        return true;
    }
    return false;
}

/**
 * @brief Cell::deselect_cell_for_move
 * Метод изменяет отрисовку границы клетки и делает границу обычной.
 */
void Cell::deselect_cell_for_move() {
    QPen pen(Qt::black);
    this->setPen(pen);
}

/**
 * @brief Cell::select_cell_for_move
 * Метод изменяет отрисовку границы клетки, делает ее выделенной.
 */
void Cell::select_cell_for_move() {
    QPen pen(Qt::yellow);
    pen.setWidth(2);
    this->setPen(pen);
}

/**
 * @brief Cell::set_cell_color
 * Метод задает новый цвет для клетки.
 * @param cell_color - новый цвет клетки.
 */
void Cell::set_cell_color(QColor cell_color) {
    this->cell_color = cell_color;
}
