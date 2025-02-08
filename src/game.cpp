#include "game.h"


static const QString lookup[4] = {QString(":/images/piece1.svg"), QString(":/images/piece2.svg"), QString(":/images/piece3.svg"), QString(":/images/board.svg")};
static const QString name = QString("윷놀이");

Game::Game(QWidget* parent) : QWidget(parent), scene(), view(&scene), sign(), board(lookup[3]), pieces{Piece(lookup[0], 0, 1000, 324), Piece(lookup[0], 1, 1000, 476), Piece(lookup[0], 2, 1000, 628), Piece(lookup[0], 3, 1000, 780), Piece(lookup[1], 4, 1200, 324), Piece(lookup[1], 5, 1200, 476), Piece(lookup[1], 6, 1200, 628), Piece(lookup[1], 7, 1200, 780), Piece(lookup[2], 8, 1400, 324), Piece(lookup[2], 9, 1400, 476), Piece(lookup[2], 10, 1400, 628), Piece(lookup[2], 11, 1400, 780)}, scores{0, 0, 0} {
    scene.setSceneRect(-30, -30, 900, 900);

    scene.addItem(&sign);
    for (auto & piece : pieces) {
        scene.addItem(&piece);
    }
    scene.addItem(&board);



    view.setRenderHint(QPainter::Antialiasing);
    view.setFixedSize(1600, 960);
    view.setWindowTitle(name);

    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);

    view.show();
}

void Game::run() {
    std::deque <unsigned int> deq {0, 1, 2};

    while(!deq.empty()) {
        const unsigned int team = deq.front();
        deq.pop_front();

        updateTurn(team);

        const unsigned int id = getSelectedPiece(team);
        const unsigned int option = Dialog(team).getSelectedOption();
        move(id, option);

        if (getScore(team) < 4) {
            deq.push_back(team);
        }
    }
}

unsigned int Game::getSelectedPiece(const unsigned int team) {
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

    //qDebug() << "Clicked target item ID:" << clickedId;
    return clickedId;
}

void Game::move(const unsigned int id, const unsigned int option) {
    pieces[id].move(option);
    if (pieces[id].isScored()) {
        const unsigned int team = id / 4;
        const unsigned int score = scores[team] + 1;
        updateScore(team, score);
        scores[team] = score;
    }
}

void Game::updateTurn(const unsigned int team) {
    sign.updateTurn(team);
}

void Game::updateScore(const unsigned int team, const unsigned int score) {
    sign.updateScore(team, score);
}

unsigned int Game::getScore(const unsigned int team) const {
    return scores[team];
}
