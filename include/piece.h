#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QtTypes>

#include "dialog.h"


class Piece final : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit Piece(const QString &filePath, unsigned int id, int x, int y);
    void move(unsigned int option);
    [[nodiscard]] bool isScored() const;
    signals:
    void clicked(unsigned int id);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
    unsigned int id;
    unsigned int pos = 0;
    unsigned int multiplicity = 1;
    int x;
    int y;

    void initialize();
};

#endif //PIECE_H
