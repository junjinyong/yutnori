#ifndef YUTNORI_PIECE_H
#define YUTNORI_PIECE_H

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <utility>

#include "manager.hpp"

static const QString labels[5] = {"<div style='font-size:48px; color:black; text-align:center;'>0</div>", "<div style='font-size:48px; color:black; text-align:center;'>1</div>", "<div style='font-size:48px; color:black; text-align:center;'>2</div>", "<div style='font-size:48px; color:black; text-align:center;'>3</div>", "<div style='font-size:48px; color:black; text-align:center;'>4</div>"};

class Piece final : public QGraphicsSvgItem {
public:
    explicit Piece(const ID& id) : Piece(id.x, id.y, (const char*[]){":/images/piece1.svg", ":/images/piece2.svg", ":/images/piece3.svg"}[id.x], nullptr) {}

    explicit Piece(const unsigned int x, const unsigned int y, const QString &filePath, QGraphicsItem* parent = nullptr) : QGraphicsSvgItem(filePath, parent), x(x), y(y), label("", this) {
        setSharedRenderer(new QSvgRenderer(filePath));

        initialize();
    }

    void setLabel(const QString& html) {
        label.setHtml(html);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsSvgItem::mousePressEvent(event);
        Manager::getInstance().clicked(x, y);
    }

private:
    void initialize() {
        label.setTextWidth(100);
        label.setHtml(labels[1]);
        label.setPos(boundingRect().center() - label.boundingRect().center());
    }

    const unsigned int x;
    const unsigned int y;
    QGraphicsTextItem label;
};

#endif //YUTNORI_PIECE_H
