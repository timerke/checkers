#include "fieldwidget.h"

#define MIN_SIZE 100

/**
 * @brief FieldWidget::FieldWidget
 * Конструктор класса виджета с игровым полем.
 */
FieldWidget::FieldWidget() : QGraphicsView() {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(MIN_SIZE);
    this->setMinimumWidth(MIN_SIZE);

    this->scene = new QGraphicsScene();
    this->scene->setBackgroundBrush(QBrush(QColor(208, 208, 208)));
    this->setScene(this->scene);
}

/**
 * @brief FieldWidget::~FieldWidget
 * Деструктор класса.
 */
FieldWidget::~FieldWidget() {
    delete this->scene;
}

/**
 * @brief FieldWidget::resizeEvent
 * Переопределение метода, обрабатывающего событие изменения размера виджета.
 * @param event - событие изменения размера виджета.
 */
void FieldWidget::resizeEvent(QResizeEvent *event) {
    qreal cell_size = this->field->calculate_cell_size(this->size().height(), this->size().width());
    this->scene->setSceneRect(0, 0, this->field->column_number * cell_size, this->field->row_number * cell_size);
    this->field->draw_cells(cell_size);
    this->field->draw_checkers();
    QGraphicsView::resizeEvent(event);
}

/**
 * @brief FieldWidget::set_field
 * Метод задает игровое поле в виджет.
 * @param field - поле.
 */
void FieldWidget::set_field(Field *field) {
    this->field = field;
    this->field->set_to_scence(this->scene);
}
