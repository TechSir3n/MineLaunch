#ifndef CODE_SUBMIT_HPP
#define CODE_SUBMIT_HPP

#include "signup.hpp"

class CodeDialog : public QDialog {
public:
    CodeDialog(QWidget* parent = nullptr): QDialog(parent) {
        QPushButton* buttonSubmitCode = new QPushButton(tr("Submit"));
        QLabel* labelSubmitCode = new QLabel((tr("Submit Code")));
        QLineEdit* lineSubmitCode = new QLineEdit();

        QHBoxLayout* hbox_layout = new QHBoxLayout;
        hbox_layout->addWidget(buttonSubmitCode);
        hbox_layout->setAlignment(Qt::AlignCenter);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(labelSubmitCode);
        layout->addWidget(lineSubmitCode);
        layout->addLayout(hbox_layout);
        layout->setSpacing(20);

        QObject::connect(buttonSubmitCode,&QPushButton::clicked,[&,this]() {
            const QString username = signup.lineUsername->text();
            const QString password = signup.linePassword->text();
            const QString email = signup.lineEmail->text();
            signup.sendBackend(username, password, email);
            this->close();
        });
    }

    ~CodeDialog() = default;

public:
    static CodeDialog& getInstance() {
        static CodeDialog instance;
        return instance;
    }

private:
    SignUp signup;
};


#endif
