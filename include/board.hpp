#ifndef YUTNORI_BOARD_H
#define YUTNORI_BOARD_H

#include <QGraphicsSvgItem>

class Board final : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit Board(const QString &filePath = ":/images/board.svg", QGraphicsItem *parent = nullptr) : QGraphicsSvgItem(filePath, parent) {
        const QRectF rect = this -> boundingRect();
        const qreal scaleX = 900 / rect.width();
        const qreal scaleY = 900 / rect.height();
        setTransform(QTransform::fromScale(scaleX, scaleY));
        setZValue(-1);
    }
};

#endif //YUTNORI_BOARD_H
