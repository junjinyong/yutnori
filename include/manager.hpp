#ifndef YUTNORI_MANAGER_H
#define YUTNORI_MANAGER_H

#include <atomic>

#include <QEventLoop>

struct ID {
    unsigned int x;
    unsigned int y;

    bool operator==(const ID&) const = default;
    constexpr ID& operator=(const ID&) = default;
    auto operator<=>(const ID&) const = default;
} typedef ID;

class Manager final {
public:
    static Manager& getInstance() {
        static Manager instance;
        return instance;
    }

    void clicked(const unsigned int a, const unsigned int b) {
        if (loop && loop -> isRunning() && x == a) {
            loop -> quit();
            y = b;
        }
    }

    ID getSelectedPiece(const unsigned int a) {
        x = a;
        loop = std::make_unique<QEventLoop>();
        loop -> exec();
        loop.reset();
        return {.x=x, .y=y};
    }

private:
    std::unique_ptr<QEventLoop> loop = nullptr;
    unsigned int x = 999;
    unsigned int y = 999;

    Manager() = default;
    ~Manager() = default;
};

#endif //YUTNORI_MANAGER_H
