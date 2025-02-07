#include <deque>

#include "window.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Window window(nullptr);

    std::deque <unsigned int> deq {0, 1, 2};

    while(!deq.empty()) {
        const unsigned int team = deq.front();
        deq.pop_front();

        window.updateTurn(team);

        const unsigned int id = window.getSelectedPiece(team);
        const unsigned int option = Dialog(team).getSelectedOption();
        window.move(id, option);

        if (window.getScore(team) < 4) {
            deq.push_back(team);
        }
    }

    return QCoreApplication::exec();
}
