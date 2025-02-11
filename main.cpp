#include <QApplication>

#include "game.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Game game;
    game.run();
    return QApplication::exec();
}
