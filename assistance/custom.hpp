#pragma once

#include <QString>
#include <QObject>
#include <QLocale>

class Custom : public QObject{
    Q_OBJECT
public:
    explicit Custom(QObject *parent = nullptr);

    ~Custom() = default;

public slots:
    void setLanguage(const char *language);

public:
   [[nodiscard]] QString getLanguage() const  noexcept;

private:
    QString m_language;
};
