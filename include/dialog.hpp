#ifndef YUTNORI_DIALOG_H
#define YUTNORI_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>



class Dialog final : public QDialog {
    Q_OBJECT

public:
    static Dialog& getInstance() {
        static Dialog instance;
        return instance;
    }

    unsigned int getSelectedOption(const unsigned int team) {
        set((QString[]){"Red Team", "Yellow Team", "Blue Team"}[team], (QString[]){"color: red; font-size: 40px; font-weight: bold;", "color: yellow; font-size: 40px; font-weight: bold;", "color: blue; font-size: 40px; font-weight: bold;"}[team]);
        if(exec() == QDialog::Rejected) {
            return 999;
        }
        return selectedOption;
    }

private:
    explicit Dialog(const QString& message = "", const QString& styles = "", QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) : QDialog(parent, f), layout(this), label(message, this), buttons{QPushButton("뒷도", this), QPushButton("도", this), QPushButton("개", this), QPushButton("걸", this), QPushButton("윷", this), QPushButton("모", this)} {
        setWindowFlags(Qt::WindowStaysOnTopHint);
        setFixedSize(300, 500);

        label.setStyleSheet(styles);
        label.setFixedSize(300, 50);
        label.setAlignment(Qt::AlignCenter);
        layout.addWidget(&label);

        for (unsigned int i = 0; i < 6; ++i) {
            buttons[i].setMinimumSize(QSize(200, 50));
            connect(&buttons[i], &QPushButton::clicked, this, [this, i]() -> void {
                selectedOption = i;
                accept();
            }, Qt::DirectConnection);
            layout.addWidget(&buttons[i]);
        }

        setLayout(&layout);
    }

    void set(const QString& message, const QString& styles) {
        label.setText(message);
        label.setStyleSheet(styles);
    }

    QVBoxLayout layout;
    QLabel label;
    QPushButton buttons[6];

    unsigned int selectedOption = 0;
};

#endif //YUTNORI_DIALOG_H
