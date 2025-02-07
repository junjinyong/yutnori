#ifndef TEAM_H
#define TEAM_H

#include <QGraphicsItemGroup>

class Team final : public QGraphicsItemGroup {
public:
    Team();

private:
    QGraphicsTextItem pieces[3];

    unsigned int team;
};

#endif //TEAM_H
