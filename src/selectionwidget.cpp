#include "selectionwidget.h"

#define MIN_SIZE 100

/**
 * @brief SelectionWidget::SelectionWidget
 * Конструктор класса.
 */
SelectionWidget::SelectionWidget() {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(MIN_SIZE);
    this->setMinimumWidth(MIN_SIZE);

    this->scene = new QGraphicsScene();
    this->setScene(this->scene);
}

/**
 * @brief SelectionWidget::~SelectionWidget
 * Деструктор класса.
 */
SelectionWidget::~SelectionWidget() {

}

void SelectionWidget::add_option() {

}

void SelectionWidget::remove_option() {

}

void SelectionWidget::scroll_left() {

}

void SelectionWidget::scroll_right() {

}
