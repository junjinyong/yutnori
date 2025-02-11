#ifndef YUTNORI_SIGN_H
#define YUTNORI_SIGN_H

#include <QGraphicsItemGroup>

static const QString lookup[6][3] = {
        {"<div style='text-align: center; font-size:72pt; color: red;'>0</div>", "<div style='text-align: center; font-size:72pt; color: yellow;'>0</div>", "<div style='text-align: center; font-size:72pt; color: blue;'>0</div>"},
        {"<div style='text-align: center; font-size:72pt; color: red;'>1</div>", "<div style='text-align: center; font-size:72pt; color: yellow;'>1</div>", "<div style='text-align: center; font-size:72pt; color: blue;'>1</div>"},
        {"<div style='text-align: center; font-size:72pt; color: red;'>2</div>", "<div style='text-align: center; font-size:72pt; color: yellow;'>2</div>", "<div style='text-align: center; font-size:72pt; color: blue;'>2</div>"},
        {"<div style='text-align: center; font-size:72pt; color: red;'>3</div>", "<div style='text-align: center; font-size:72pt; color: yellow;'>3</div>", "<div style='text-align: center; font-size:72pt; color: blue;'>3</div>"},
        {"<div style='text-align: center; font-size:72pt; color: red;'>4</div>", "<div style='text-align: center; font-size:72pt; color: yellow;'>4</div>", "<div style='text-align: center; font-size:72pt; color: blue;'>4</div>"},
        {"<div style='text-align: center; font-size:72pt; color: red;'>Team Red</div>", "<div style='text-align: center; font-size:72pt; color: yellow;'>Team Yellow</div>", "<div style='text-align: center; font-size:72pt; color: blue;'>Team Blue</div>"},
};

class Sign final : public QGraphicsItemGroup {
public:
    Sign(QGraphicsItem* parent = nullptr) : QGraphicsItemGroup(parent), turn(), scores() {
        turn.setTextWidth(600);
        turn.setPos(1200 - 300 + 45, 20);
        addToGroup(&turn);

        for (unsigned int i = 0; i < 3; ++i) {
            scores[i].setTextWidth(100);
            scores[i].setPos(1000 + 200 * i - 50 + 45, 172);
            addToGroup(&scores[i]);
        }

        scores[0].setHtml(lookup[0][0]);
        scores[1].setHtml(lookup[0][1]);
        scores[2].setHtml(lookup[0][2]);
    }
    void updateTurn(unsigned int team) {
        turn.setHtml(lookup[5][team]);
    }
    void updateScore(unsigned int team, unsigned int score) {
        scores[team].setHtml(lookup[score][team]);
    }

private:
    QGraphicsTextItem turn;
    QGraphicsTextItem scores[3];
};

#endif //YUTNORI_SIGN_H
