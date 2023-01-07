#ifndef FIELD_H
#define FIELD_H

#include <QColor>
#include <QGraphicsScene>
#include <QObject>
#include "cell.h"
#include "checker.h"

/**
 * @brief The Field class
 * Класс для шашечного поля.
 */
class Field : public QObject {
    Q_OBJECT

public:
    Field(int row_number, int column_number, int checker_number);
    ~Field();
    qreal calculate_cell_size(qreal widget_height, qreal widget_width);
    bool check_empty_cell(Cell *cell);
    void draw_cells(qreal cell_size);
    void draw_checkers();
    Cell * find_cell_at_pos(QPointF &pos);
    Checker ** get_black_checkers();
    Cell * get_cell(int row, int column);
    Checker ** get_white_checkers();
    void set_cell_colors(QColor black, QColor white);
    void set_checker_variant(int checker_variant);
    void set_checkers_to_init_pos();
    void set_to_scence(QGraphicsScene *scene);

private:
    void create_cells();
    void create_checkers(CheckerType checker_type, Checker ***checkers);
    CellType get_cell_type(int row, int column);
    QColor get_cell_color(CellType cell_type);

public:
    int column_number;
    int row_number;

private:
    Checker **black_checkers;
    Cell ***cells;
    int checker_number;
    int checker_variant = 1;
    QColor color_for_black_cells = QColor(78, 78, 78);
    QColor color_for_white_cells = QColor("white");
    Checker **white_checkers;
};

#endif // FIELD_H
