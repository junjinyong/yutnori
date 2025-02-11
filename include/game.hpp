#ifndef YUTNORI_GAME_H
#define YUTNORI_GAME_H

#include <deque>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "board.hpp"
#include "sign.hpp"
#include "piece.hpp"
#include "dialog.hpp"

struct Input {
    ID id;
    unsigned int option;
} typedef Input;

struct State {
    std::map<ID, ID> parent;
    std::map<ID, unsigned int> position;
} typedef State;

struct Result {
    bool captured;
    unsigned int score;
} typedef Result;

struct Score {
    unsigned int team;
    unsigned int score;
};

static constexpr QPointF coordinates[37] = {{0, 0}, {780, 628}, {780, 476}, {780, 324}, {780, 172}, {780, 20}, {628, 20}, {476, 20}, {324, 20}, {172, 20}, {20, 20}, {20, 172}, {20, 324}, {20, 476}, {20, 628}, {20, 780}, {172, 780}, {324, 780}, {476, 780}, {628, 780}, {780, 780}, {0, 0}, {780, 20}, {653.3333, 146.6667}, {526.6667, 273.3333}, {400, 400}, {273.3333, 526.6667}, {146.6667, 653.3333}, {20, 780}, {400, 400}, {20, 20}, {146.6667, 146.6667}, {273.3333, 273.3333}, {400, 400}, {526.6667, 526.6667}, {653.3333, 653.3333}, {780, 780}};

static constexpr QPointF initial[3][4] = {
    {{1000, 324}, {1000, 476},  {1000, 628}, {1000, 780}},
    {{1200, 324}, {1200, 476}, {1200, 628}, {1200, 780}},
    {{1400, 324}, {1400, 476}, {1400, 628}, {1400, 780}},
};

static constexpr unsigned int table[5][37] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 23, 24, 25, 34, 27, 28, 16, 34, 31, 32, 33, 34, 35, 36, 21},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 23, 24, 25, 26, 27, 28, 16, 34, 31, 32, 33, 34, 35, 36, 21},
    {1, 2, 3, 4, 22, 6, 7, 8, 9, 30, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 23, 24, 29, 26, 27, 28, 16, 34, 31, 32, 33, 34, 35, 36, 21},
    {1, 2, 3, 4, 22, 6, 7, 8, 9, 30, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 23, 24, 29, 34, 27, 28, 16, 34, 31, 32, 33, 34, 35, 36, 21},
    {0, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 4, 22, 23, 24, 25, 26, 27, 24, 9, 30, 31, 32, 33, 34, 35},
};

static const std::map<unsigned int, std::vector<unsigned int>> equivalents = {
    {0, {}}, {21, {}},
    {1, {1}}, {2, {2}}, {3, {3}}, {4, {4}}, {6, {6}}, {7, {7}}, {8, {8}}, {9, {9}}, {11, {11}}, {12, {12}}, {13, {13}}, {14, {14}}, {16, {16}}, {17, {17}}, {18, {18}}, {19, {19}}, {23, {23}}, {24, {24}}, {26, {26}}, {27, {27}}, {31, {31}}, {32, {32}}, {34, {34}}, {35, {35}},
    {5, {5, 22}}, {22, {5, 22}},
    {10, {10, 30}}, {30, {10, 30}},
    {15, {15, 28}}, {28, {15, 28}},
    {20, {20, 36}}, {36, {20, 36}},
    {25, {25, 29, 33}}, {29, {25, 29, 33}}, {33, {25, 29, 33}},
};

class Game final : public QWidget {
public:
    explicit Game(QWidget *parent = nullptr) : QWidget(parent), scene(this), view(&scene, this), layout(this) {
        setWindowTitle("윷놀이");
        setFixedSize(1600, 960);

        for (unsigned int i = 0; i < 3; ++i) {
            for (unsigned int j = 0; j < 4; ++j) {
                pieces[i][j] = std::make_unique<Piece>(ID {i, j});
                scene.addItem(pieces[i][j].get());
            }
        }
        scene.addItem(&board);
        scene.addItem(&sign);
        scene.setSceneRect(-30, -30, 900, 900);

        view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
        view.setFrameStyle(QFrame::NoFrame);

        layout.addWidget(&view);
        setLayout(&layout);
        show();
    }

    State initialize() {
        State state;
        for (unsigned int i = 0; i < 3; ++i) {
            for (unsigned int j = 0; j < 4; ++j) {
                const ID id = {.x = i, .y = j};
                state.parent[id] = id;
                state.position[id] = 0;
            }
        }
        for (unsigned int i = 0; i < 3; ++i) {
            const Score score = {.team = i, .score = 0};
            renderFrame(score, state);
        }
        return state;
    }

    Input processInput(const unsigned int team) {
        const ID id = Manager::getInstance().getSelectedPiece(team);
        const unsigned int option = Dialog::getInstance().getSelectedOption(team);
        if (option == 999) {
            return processInput(team);
        }  else {
            return {.id = id, .option = option};
        }
    }

    unsigned int getNextPos(unsigned int pos, unsigned int option) {
        if (option == 0) {
            return table[4][pos];
        } else {
            for (int i = 0; i < option; ++i) {
                const bool first = (i == 0);
                const bool last = (i == option - 1);
                const unsigned int idx = (last << 1) + (first == last);
                pos = table[idx][pos];
            }
            return pos;
        }
    }

    Result updateState(const Input& input, State& state) {
        const unsigned int team = input.id.x;
        const unsigned int pos = getNextPos(state.position[input.id], input.option);
        const auto iter = equivalents.find(pos);
        if (iter == equivalents.end()) {
            throw std::bad_cast();
        }
        const auto& vec = iter -> second;
        bool flag = false;
        for (unsigned int i = 0; i < 3; ++i) {
            for (unsigned int j = 0; j < 4; ++j) {
                const ID id = {.x = i, .y = j};
                if (state.parent[id] == input.id) {
                    state.position[id] = pos;
                    continue;
                }
                if (std::ranges::find(vec, state.position[id]) == vec.end()) {
                    continue;
                }

                if (team == i) {
                    state.parent[id] = input.id;
                    state.position[id] = pos;
                } else {
                    state.parent[id] = id;
                    state.position[id] = 0;
                    flag = true;
                }
            }
        }
        unsigned int score = 0;
        for (unsigned int j = 0; j < 4; ++j) {
            const ID id = {.x = team, .y = j};
            if (state.position[id] == 21) {
                ++score;
            }
        }
        return {.captured = flag, .score = score};
    }

    void renderFrame(const Score& score, State& state) {
        std::map<ID, unsigned int> m;
        for (unsigned int i = 0; i < 3; ++i) {
            for (unsigned int j = 0; j < 4; ++j) {
                const ID id = {.x = i, .y = j};
                ++m[state.parent[id]];
                if (state.parent[id] != id || state.position[id] == 21) {
                    pieces[i][j] -> setVisible(false);
                } else {
                    const unsigned int pos = state.position[id];
                    pieces[i][j] -> setPos(pos == 0 ? initial[i][j] : coordinates[pos]);
                    pieces[i][j] -> setVisible(true);
                }
            }
        }
        sign.updateScore(score.team, score.score);
        for (unsigned int i = 0; i < 3; ++i) {
            for (unsigned int j = 0; j < 4; ++j) {
                const ID id = {.x = i, .y = j};
                const unsigned int multiplicity = m[id];
                pieces[i][j] -> setLabel(labels[multiplicity]);
            }
        }
    }

    void run() {
        State state = initialize();
        std::deque<unsigned int> teams {0, 1, 2};
        while(!teams.empty()) {
            const unsigned int team = teams.front();
            teams.pop_front();
            sign.updateTurn(team);

            const Input input = processInput(team);
            const Result result = updateState(input, state);
            const Score score = {.team = team, .score = result.score};
            renderFrame(score, state);

            if (result.score == 4) {
                continue;
            }
            if (result.captured) {
                teams.push_front(team);
            } else {
                teams.push_back(team);
            }
        }
    }

private:
    QGraphicsScene scene;
    QGraphicsView view;
    QVBoxLayout layout;

    Board board;
    Sign sign;
    std::unique_ptr<Piece> pieces[3][4];
};


#endif //YUTNORI_GAME_H
