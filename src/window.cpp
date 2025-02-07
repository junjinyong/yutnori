#include "window.h"


Window::Window(QWidget* parent) : QWidget(parent), scene(), view(&scene), sign(), board(":/images/board.svg"), pieces{Piece(":/images/piece1.svg", 0, 1000, 324), Piece(":/images/piece1.svg", 1, 1000, 476), Piece(":/images/piece1.svg", 2, 1000, 628), Piece(":/images/piece1.svg", 3, 1000, 780), Piece(":/images/piece2.svg", 4, 1200, 324), Piece(":/images/piece2.svg", 5, 1200, 476), Piece(":/images/piece2.svg", 6, 1200, 628), Piece(":/images/piece2.svg", 7, 1200, 780), Piece(":/images/piece3.svg", 8, 1400, 324), Piece(":/images/piece3.svg", 9, 1400, 476), Piece(":/images/piece3.svg", 10, 1400, 628), Piece(":/images/piece3.svg", 11, 1400, 780)}, scores{0, 0, 0} {
    scene.setSceneRect(-30, -30, 900, 900);

    scene.addItem(&sign);
    for (auto & piece : pieces) {
        scene.addItem(&piece);
    }
    scene.addItem(&board);



    view.setRenderHint(QPainter::Antialiasing);
    view.setFixedSize(1600, 960);
    view.setWindowTitle("윷놀이");

    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);

    view.show();
}

unsigned int Window::getSelectedPiece(const unsigned int team) {
    QEventLoop loop;
    int clickedId = -1;
    for (unsigned int i = 0; i < 12; ++i) {
        QObject::disconnect(&pieces[i], &Piece::clicked, nullptr, nullptr);
    }

    const auto start = team * 4;
    const auto end = start + 4;
    for (unsigned int i = start; i < end; ++i) {
        QObject::connect(&pieces[i], &Piece::clicked, [&loop, &clickedId](const int id) -> void {
            clickedId = id;
            loop.quit();
        });
    }

    loop.exec();

    qDebug() << "Clicked target item ID:" << clickedId;
    return clickedId;
}

void Window::move(const unsigned int id, const unsigned int option) {
    pieces[id].move(option);
    if (pieces[id].isScored()) {
        const unsigned int team = id / 4;
        const unsigned int score = scores[team] + 1;
        updateScore(team, score);
        scores[team] = score;
    }
}

void Window::updateTurn(const unsigned int team) {
    sign.updateTurn(team);
}

void Window::updateScore(const unsigned int team, const unsigned int score) {
    sign.updateScore(team, score);
}

unsigned int Window::getScore(const unsigned int team) const {
    return scores[team];
}
