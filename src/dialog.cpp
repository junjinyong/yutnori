#include "dialog.h"

static const QString styles[] = {QString("color: red; font-size: 40px; font-weight: bold; "), QString("color: yellow; font-size: 40px; font-weight: bold; "), QString("color: blue; font-size: 40px; font-weight: bold; ")};
static const QString messages[] = {QString("Red Team "), QString("Yellow Team "), QString("Blue Team ")};


Dialog::Dialog(const unsigned int team, QWidget* parent) : QDialog(parent), layout(this), label(messages[team], this), buttons{QPushButton(QString("뒷도"), this), QPushButton(QString("도"), this), QPushButton(QString("개"), this), QPushButton(QString("걸"), this), QPushButton(QString("윷"), this), QPushButton(QString("모"), this)}, selectedOption(999) {
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setFixedSize(300, 500);

    label.setStyleSheet(styles[team]);
    label.setFixedSize(300, 50);
    label.setAlignment(Qt::AlignCenter);
    layout.addWidget(&label);

    for (unsigned int i = 0; i < 6; ++i) {
        buttons[i].setMinimumSize(QSize(200, 50));
        connect(&buttons[i], &QPushButton::clicked, this, [this, i]() -> void {
            selectedOption = i;
            accept();
        });
        layout.addWidget(&buttons[i]);
    }

    setLayout(&layout);
}

unsigned int Dialog::getSelectedOption() {
    selectedOption = 999;
    this -> exec();
    //qDebug() << "Selected option:" << selectedOption;
    return selectedOption;
}
