#ifndef CELL_H
#define CELL_H

#include <QBrush>
#include <QGraphicsRectItem>

enum CellType {
    BLACK_CELL,
    WHITE_CELL
};

/**
 * @brief The Cell class
 * Класс для клетки на шашечной доске.
 */
class Cell : public QGraphicsRectItem {

public:
    Cell(int row, int column, CellType cell_type, QColor cell_color);
    ~Cell();
    bool check_black();
    bool check_pos_in_cell(QPointF pos);
    void deselect_cell_for_move();
    void select_cell_for_move();
    void set_cell_color(QColor cell_color);

public:
    int column;
    int row;

private:
    QColor cell_color;
    CellType cell_type;
};

#endif // CELL_H
