#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSvgItem>
#include <QMouseEvent>
#include <QEventLoop>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>


#include <vector>

#include "board.h"
#include "piece.h"
#include "sign.h"


class Window final : public QWidget {
    Q_OBJECT

public:
    explicit Window(QWidget* parent = nullptr);
    unsigned int getSelectedPiece(unsigned int team);
    void move(unsigned int id, unsigned int option);
    void updateTurn(unsigned int team);
    void updateScore(unsigned int team, unsigned int score);
    unsigned int getScore(unsigned int team) const;
private:
    QGraphicsScene scene;
    QGraphicsView view;

    Sign sign;
    Board board;
    Piece pieces[12];

    unsigned int scores[3];
};

#endif //WINDOW_H
