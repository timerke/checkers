#include <QPen>
#include "cell.h"

/**
 * @brief Cell::Cell
 * Конструктор класса для ячейки шашечной доски.
 * @param row - номер строки на шашечной доске для ячейки;
 * @param column - номер столбца на шашечной доске для ячейки.
 */
Cell::Cell(int row, int column) : QGraphicsRectItem() {
    this->column = column;
    this->row = row;
    this->cell_type = this->get_cell_type(row, column);
    QPen pen(Qt::black);
    this->setPen(pen);
    this->setBrush(this->get_brush_for_cell());
}

/**
 * @brief Cell::~Cell
 * Деструктор класса.
 */
Cell::~Cell() {

}

/**
 * @brief Cell::check_black
 * Метод проверяет, является ли ячейка черной.
 * @return true, если ячейка черная.
 */
bool Cell::check_black() {
    return this->cell_type == CellType::BLACK_CELL;
}

/**
 * @brief Cell::check_pos_in_cell
 * Метод проверяет, что указанная точка находится внутри ячейки.
 * @param pos - точка.
 * @return true, если точка внутри ячейки.
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
 * Метод изменяет отрисовку границы ячейки, делает границу обычной.
 */
void Cell::deselect_cell_for_move() {
    QPen pen(Qt::black);
    this->setPen(pen);
}

/**
 * @brief Cell::get_brush
 * Метод возвращает кисть для ячейки шашечной доски в заданном ряду и столбце.
 * @return кисть для ячейки.
 */
QBrush Cell::get_brush_for_cell() {
    QBrush brush;
    if (this->cell_type == CellType::WHITE_CELL) {
        // Кисть для белых клеток
        brush = QBrush(QColor("white"));
    } else {
        // Кисть для черных клеток
        brush = QBrush(QColor(78, 78, 78));
    }
    return brush;
}

/**
 * @brief Cell::get_cell_type
 * Метод возвращает тип ячейки (черная или белая).
 * @param row - номер строки на шашечном поле;
 * @param column - номер столбца на шашечном поле.
 * @return тип ячейки.
 */
CellType Cell::get_cell_type(int row, int column) {
    if ((row + column) % 2) {
        return CellType::BLACK_CELL;
    }
    return CellType::WHITE_CELL;
}

/**
 * @brief Cell::select_cell_for_move
 * Метод изменяет отрисовку границы ячейки, делает ее выделенной.
 */
void Cell::select_cell_for_move() {
    QPen pen(Qt::yellow);
    pen.setWidth(2);
    this->setPen(pen);
}
