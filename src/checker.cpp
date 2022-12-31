#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPen>
#include "checker.h"

/**
 * @brief Checker::Checker
 * Конструктор класса для шашки.
 * @param index - индекс шашки;
 * @param checker_type - тип шашки (черная или белая).
 */
Checker::Checker(int index, CheckerType checker_type) : QObject(), QGraphicsItemGroup() {
    this->cell = nullptr;
    this->checker_type = checker_type;
    this->index = index;
    this->king = false;
    this->pixmap_item = new QGraphicsPixmapItem();
    this->addToGroup(this->pixmap_item);
    this->circle = new QGraphicsEllipseItem();
    this->circle->setVisible(false);
    this->addToGroup(this->circle);
    this->setVisible(false);
    this->setAcceptHoverEvents(true);
}

/**
 * @brief Checker::~Checker
 * Деструктор класса.
 */
Checker::~Checker() {

}

/**
 * @brief Checker::change_checker_status
 * Метод переводит шашку в дамки и обратно.
 * @param king - если true, то шашка становится дамкой;
 * @param checker_variant - вариант набора шашек.
 */
void Checker::change_checker_status(bool king, int checker_variant) {
    this->king = king;
    QString pixmap_file = this->get_file_for_checker(checker_variant);
    this->pixmap_item->setPixmap(QPixmap(pixmap_file));
}

/**
 * @brief Checker::get_file_for_checker
 * Метод возвращает имя файла с изображением шашки.
 * @param checker_variant - вариант набора шашек.
 * @return файл с изображением.
 */
QString Checker::get_file_for_checker(int checker_variant) {
    QString king = this->king ? "_king" : "";
    QString color = this->checker_type == CheckerType::BLACK_CHECKER ? "black" : "white";
    return ":/image/" + color + king + "_checker_" + QString::number(checker_variant) + ".png";
}

/**
 * @brief Checker::get_pen
 * Метод возвращает перо для выделения шашки.
 * @param width - толщина пера.
 * @return перо.
 */
QPen Checker::get_pen(int width) {
    QPen pen;
    pen.setColor(QColor(this->checker_type == CheckerType::BLACK_CHECKER ? Qt::black : Qt::white));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(width);
    return pen;
}

/**
 * @brief Checker::handle_click
 * Метод отрисовывает кружок на шашке при клике по ней или при наведении на нее мышки.
 * @param checker_status - состояние шашки (на нее навели мышку, кликнули по ней или
 * ничего не сделали).
 */
void Checker::handle_mouse_action(CheckerStatus checker_status) {
    bool visible = false;
    int width = 0;
    int z_value = 0;
    if (checker_status == CheckerStatus::PRESSED || checker_status == CheckerStatus::HOVER_STARTED) {
        visible = true;
        z_value = 2;
        width = checker_status == CheckerStatus::PRESSED ? 2 : 1;
    }
    this->setZValue(z_value);
    this->circle->setPen(this->get_pen(width));
    this->circle->setVisible(visible);
    this->circle->setZValue(z_value);
}

/**
 * @brief Checker::hoverEnterEvent
 * Переопределение метода обработки наведения мышки на шашку.
 * @param event - событие, когда мышка оказывается над шашкой.
 */
void Checker::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    emit this->mouse_action_happened(this, CheckerStatus::HOVER_STARTED);
    QGraphicsItemGroup::hoverEnterEvent(event);
}

/**
 * @brief Checker::hoverLeaveEvent
 * Переопределение метода обработки завершения наведения мыщки на шашку.
 * @param event - событие, когда мышка оказывается вне шашки.
 */
void Checker::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    emit this->mouse_action_happened(this, CheckerStatus::HOVER_STOPPED);
    QGraphicsItemGroup::hoverLeaveEvent(event);
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
    emit this->mouse_action_happened(this, CheckerStatus::PRESSED);
    QGraphicsItemGroup::mousePressEvent(event);
}

/**
 * @brief Checker::mouseReleaseEvent
 * Переопределение метода обработки освобождения виджета мышкой.
 * @param event - событие по освобождению мышкой виджета.
 */
void Checker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit this->mouse_action_happened(this, CheckerStatus::RELEASED);
    QGraphicsItemGroup::mouseReleaseEvent(event);
}

/**
 * @brief Checker::redraw
 * Метод отрисовывает шашку.
 */
void Checker::redraw() {
    if (this->cell) {
        QRectF cell_rect = this->cell->rect();
        QRect pixmap_rect = this->pixmap_item->pixmap().rect();
        qreal pixmap_size = cell_rect.width() * 0.8;
        this->pixmap_item->pixmap().scaled(pixmap_size, pixmap_size);
        this->pixmap_item->setScale(pixmap_size / pixmap_rect.width());
        qreal x = cell_rect.x() + (cell_rect.width() - pixmap_size) / 2;
        qreal y = cell_rect.y() + (cell_rect.height() - pixmap_size) / 2;
        this->circle->setRect(0, 0, pixmap_size, pixmap_size);
        this->removeFromGroup(this->pixmap_item);
        this->addToGroup(this->pixmap_item);
        this->setPos(x, y);
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
