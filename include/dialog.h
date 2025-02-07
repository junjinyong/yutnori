#ifndef DIALOG_H
#define DIALOG_H

#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QDebug>

class Dialog final : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(unsigned int team, QWidget* parent = nullptr);
    [[nodiscard]] unsigned int getSelectedOption();
private:
    QVBoxLayout layout;
    QLabel label;
    QPushButton buttons[6];

    unsigned int selectedOption = 999;
};

#endif //DIALOG_H
