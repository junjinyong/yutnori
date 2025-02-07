#ifndef SIGN_H
#define SIGN_H

#include <QGraphicsItemGroup>

class Sign final : public QGraphicsItemGroup {
public:
    Sign();
    void updateTurn(unsigned int team);
    void updateScore(unsigned int team, unsigned int score);

private:
    QGraphicsTextItem turn;
    QGraphicsTextItem scores[3];
};


#endif //SIGN_H
