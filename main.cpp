#include "game.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Game().run();

    return QCoreApplication::exec();
}
