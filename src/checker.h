#ifndef CHECKER_H
#define CHECKER_H
#pragma once

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include "cell.h"

class Game;

enum CheckerType {
    BLACK_CHECKER,
    WHITE_CHECKER
};

enum CheckerStatus {
    HOVER_STARTED,
    HOVER_STOPPED,
    PRESSED,
    QUIET,
    RELEASED
};

/**
 * @brief The Checker class
 * Класс для шашки.
 */
class Checker : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

    friend class Game;

public:
    explicit Checker(int index, CheckerType checker_type);
    ~Checker();
    void change_checker_status(bool king, int checker_variant = 0);
    void handle_mouse_action(CheckerStatus checker_status);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void redraw();
    void set_position(Cell *cell);

private:
    QString get_file_for_checker(int checker_variant);
    QPen get_pen(int width);

signals:
    void checker_moved(QPointF pos);
    void mouse_action_happened(Checker *checker, CheckerStatus checker_status);

public:
    Cell *cell;
    CheckerType checker_type;
    int index;

private:
    QGraphicsEllipseItem *circle;
    bool king;
    QGraphicsPixmapItem *pixmap_item;
    const int SELECTED_LINE_WIDTH = 2;
};

#endif // CHECKER_H
