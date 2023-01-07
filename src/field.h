#ifndef FIELD_H
#define FIELD_H

#include <QBrush>
#include <QGraphicsView>
#include <QPen>
#include <QVector>
#include "cell.h"
#include "checker.h"

/**
 * @brief The Field class
 * Класс для шашечного поля.
 */
class Field : public QGraphicsView {
    Q_OBJECT

public:
    Field(int row_number, int column_number, int checker_number);
    ~Field();
    bool check_empty_cell(Cell *cell);
    Cell * find_cell_at_pos(QPointF &pos);
    Checker ** get_black_checkers();
    Cell * get_cell(int row, int column);
    Checker ** get_white_checkers();
    void set_cell_colors(QColor black, QColor white);
    void set_checkers_to_init_pos(int checker_variant);

private:
    void create_cells();
    void create_checkers(CheckerType checker_type, Checker ***checkers);
    void draw_cells();
    void draw_checkers();
    CellType get_cell_type(int row, int column);
    QColor get_cell_color(CellType cell_type);
    void resizeEvent(QResizeEvent *event);

public:
    int checker_number;

private:
    Checker **black_checkers;
    Cell ***cells;
    QColor color_for_black_cells = QColor(78, 78, 78);
    QColor color_for_white_cells = QColor("white");
    int column_number;
    int row_number;
    QGraphicsScene *scene;
    Checker **white_checkers;
};

#endif // FIELD_H
