#include "piece.h"
#include <QDebug>


Piece::Piece(const QString& filePath, const unsigned int id, const int x, const int y) : QGraphicsSvgItem(filePath), id(id), pos(0), multiplicity(1), x(x), y(y) {
    setSharedRenderer(new QSvgRenderer(filePath));
    initialize();
}

void Piece::initialize() {
    //setFlags(QGraphicsItem::ItemIsMovable);
    setPos(x, y);
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Piece clicked!" << this -> id;
    emit clicked(this -> id);
    QGraphicsSvgItem::mousePressEvent(event);
}

static constexpr unsigned int lookup[3][37] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 23, 24, 25, 26, 27, 28, 16, 34, 31, 32, 33, 34, 35, 36, 21},
    {1, 2, 3, 4, 22, 6, 7, 8, 9, 30, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 23, 24, 29, 26, 27, 28, 16, 34, 31, 32, 33, 34, 35, 36, 21},
    {0, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 4, 22, 23, 24, 25, 26, 27, 24, 9, 30, 31, 32, 33, 34, 35},
};

static constexpr qreal coordinates[37][2] = {{0, 0}, {780, 628}, {780, 476}, {780, 324}, {780, 172}, {780, 20}, {628, 20}, {476, 20}, {324, 20}, {172, 20}, {20, 20}, {20, 172}, {20, 324}, {20, 476}, {20, 628}, {20, 780}, {172, 780}, {324, 780}, {476, 780}, {628, 780}, {780, 780}, {0, 0}, {780, 20}, {653.3333, 146.6667}, {526.6667, 273.3333}, {400, 400}, {273.3333, 526.6667}, {146.6667, 653.3333}, {20, 780}, {400, 400}, {20, 20}, {146.6667, 146.6667}, {273.3333, 273.3333}, {400, 400}, {526.6667, 526.6667}, {653.3333, 653.3333}, {780, 780}};

void Piece::move(const unsigned int option) {
    if (option == 0) {
        pos = lookup[2][pos];
    } else {
        unsigned int iter = option;
        while (--iter) {
            pos = lookup[0][pos];
        }
        pos = lookup[1][pos];
    }

    if (pos == 0) {
        setPos(x, y);
    } else if (pos == 21) {
        this -> setVisible(false);
    } else {
        setPos(coordinates[pos][0], coordinates[pos][1]);
    }
}

bool Piece::isScored() const {
    return pos == 21;
}