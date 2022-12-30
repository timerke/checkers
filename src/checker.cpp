#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPen>
#include "checker.h"

/**
 * @brief Checker::Checker
 * Конструктор класса для шашки.
 * @param index - индекс шашки;
 * @param checker_type - тип шашки (черная или белая);
 * @param checker_variant - вариант набора шашек.
 */
Checker::Checker(int index, CheckerType checker_type, int checker_variant) : QObject(), QGraphicsItemGroup() {
    this->cell = nullptr;
    this->checker_type = checker_type;
    this->checker_variant = checker_variant;
    this->index = index;
    this->king = false;
    QString checker_file = this->get_file_for_checker();
    this->pixmap_item = new QGraphicsPixmapItem(QPixmap(checker_file));
    this->addToGroup(this->pixmap_item);
    this->circle = new QGraphicsEllipseItem();
    this->circle->setPen(this->get_pen_for_selected_checker());
    this->circle->setVisible(false);
    this->addToGroup(this->circle);
    this->setVisible(false);
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
    if (checker_variant) {
        this->checker_variant = checker_variant;
    }
    this->king = king;
    QString pixmap_file = this->get_file_for_checker();
    this->pixmap_item->setPixmap(QPixmap(pixmap_file));
}

/**
 * @brief Checker::get_file_for_checker
 * Метод возвращает имя файла с изображением шашки.
 * @return файл с изображением.
 */
QString Checker::get_file_for_checker() {
    QString king("");
    if (this->king) {
        king = "_king";
    }
    QString color;
    if (this->checker_type == CheckerType::BLACK_CHECKER) {
        color = "black";
    } else {
        color = "white";
    }
    return ":/image/" + color + king + "_checker_" + QString::number(this->checker_variant) + ".png";
}

/**
 * @brief Checker::get_pen
 * Метод возвращает перо для выделения шашки.
 * @return перо.
 */
QPen Checker::get_pen_for_selected_checker() {
    QPen pen;
    pen.setColor(QColor(this->checker_type == CheckerType::BLACK_CHECKER ? Qt::red : Qt::blue));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    return pen;
}

/**
 * @brief Checker::handle_click
 * Метод отрисовывает кружок на шашке при клике по ней.
 * @param clicked - если true, то игрок кликнул по шашке.
 */
void Checker::handle_click(bool clicked) {
    this->setZValue(clicked * 2);
    this->circle->setVisible(clicked);
    this->circle->setZValue(clicked * 2);
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
    qDebug() << this->checker_type << " " << this->index << " " << this->boundingRect();
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
