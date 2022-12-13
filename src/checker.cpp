#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPen>
#include "checker.h"

/**
 * @brief Checker::Checker
 * Конструктор класс для шашки.
 * @param checker_type - тип шашки (черная или белая).
 */
Checker::Checker(CheckerType checker_type) : QObject(), QGraphicsItemGroup() {
    this->checker_type = checker_type;
    this->king = false;
    QPen pen = this->get_pen(false);
    for (int i = 0; i < this->CIRCLES_NUMBER; i++) {
        QBrush brush = this->get_brush(i);
        this->circles[i] = new QGraphicsEllipseItem();
        this->circles[i]->setPen(pen);
        this->circles[i]->setBrush(brush);
        this->addToGroup(this->circles[i]);
    }
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->cell = nullptr;
}

/**
 * @brief Checker::~Checker
 * Деструктор класса.
 */
Checker::~Checker() {

}

/**
 * @brief Checker::get_brush
 * Метод возвращает кисть для шашки.
 * @param circle_index - номер кружка, который нужно закрасить.
 * @return кисть.
 */
QBrush Checker::get_brush(int circle_index) {
    QBrush brush;
    if (this->checker_type == CheckerType::BLACK_CHECKER) {
        switch (circle_index) {
        case 0:
            brush.setColor(QColor(240, 128, 128));
            break;
        case 1:
            brush.setColor(QColor(250, 138, 138));
            break;
        default:
            brush.setColor(QColor(255, 148, 148));
        }
    } else {
        switch (circle_index) {
        case 0:
            brush.setColor(QColor(100, 149, 237));
            break;
        case 1:
            brush.setColor(QColor(110, 159, 247));
            break;
        default:
            brush.setColor(QColor(120, 169, 255));
        }
    }
    brush.setStyle(Qt::SolidPattern);
    return brush;
}

/**
 * @brief Checker::get_pen
 * Метод возвращает перо для шашки в указанном состоянии.
 * @param selected - если true, то шашка выбрана игроком.
 * @return перо.
 */
QPen Checker::get_pen(bool selected) {
    QPen pen;
    if (selected) {
        pen.setColor(QColor(this->checker_type == CheckerType::BLACK_CHECKER ? Qt::red : Qt::blue));
    } else {
        pen.setColor(QColor(105, 105, 105));
    }
    pen.setStyle(Qt::SolidLine);
    return pen;
}

/**
 * @brief Checker::get_pos_of_center
 * Метод возвращает положение центра шашки.
 * @return точка в центре шашки.
 */
QPointF Checker::get_pos_of_center() {
    QRectF rect = this->circles[0]->rect();
    qreal x = this->pos().x() + rect.width() / 2.0;
    qreal y = this->pos().y() + rect.height() / 2.0;
    return QPointF(x, y);
}

/**
 * @brief Checker::handle_click
 * Метод отрисовывает кружки на шашке при клике по ней.
 * @param clicked - если true, то игрок кликнул по шашке.
 */
void Checker::handle_click(bool clicked) {
    for (int i = 0; i < this->CIRCLES_NUMBER; i++) {
        this->circles[i]->setPen(this->get_pen(clicked));
    }
}

/**
 * @brief Checker::mouseMoveEvent
 * Переопределение метода обработки перемещения виджета мышкой.
 * @param event - событие по перемещению мышкой виджета.
 */
void Checker::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    emit this->checker_moved(event->scenePos());
    QGraphicsItemGroup::mouseMoveEvent(event);
}

/**
 * @brief Checker::mousePressEvent
 * Переопределение метода обработки выбора виджета мышкой.
 * @param event - событие по выбору мышкой виджта.
 */
void Checker::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit this->checker_pressed_or_released(true, this);
    QGraphicsItemGroup::mousePressEvent(event);
}

/**
 * @brief Checker::mouseReleaseEvent
 * Переопределение метода обработки освобождения виджета мышкой.
 * @param event - событие по освобождению мышкой виджета.
 */
void Checker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit this->checker_pressed_or_released(false, this);
    QGraphicsItemGroup::mouseReleaseEvent(event);
}

/**
 * @brief Checker::redraw
 * Метод отрисовывает шашку.
 */
void Checker::redraw() {
    if (this->cell) {
        QRectF rect = this->cell->rect();
        int dx = rect.width() / 5;
        int dy = rect.height() / 5;
        for (int i = 0; i < this->CIRCLES_NUMBER; i++) {
            int x = i * dx;
            int y = i * dy;
            int width = dx * (5 - 2 * i);
            int height = dy * (5 - 2 * i);
            QRectF rect_for_circle(x, y, width, height);
            this->circles[i]->setRect(rect_for_circle);
        }
        this->setPos(rect.x(), rect.y());
    }
}

/**
 * @brief Checker::set_position
 * Метод помещает шашку в указанную ячейку.
 * @param cell - ячейка, куда нужно поместить шашку.
 */
void Checker::set_position(Cell *cell) {
    this->cell = cell;
    this->redraw();
}
