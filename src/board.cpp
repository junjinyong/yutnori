#include "board.h"

Board::Board(const QString &filePath): QGraphicsSvgItem(filePath) {
    initialize();
}

void Board::initialize() {
    const QRectF rect = this -> boundingRect();
    const qreal scaleX = 900 / rect.width();
    const qreal scaleY = 900 / rect.height();
    this -> setTransform(QTransform::fromScale(scaleX, scaleY));
    this -> setZValue(-1);
}
