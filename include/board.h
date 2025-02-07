#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>


class Board final : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit Board(const QString &filePath);
    static unsigned int getNextPos(unsigned int pos, int option);
private:
    void initialize();
};


#endif //BOARD_H
