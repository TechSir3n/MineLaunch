#pragma once

#include <QString>

static const QString lineEditStyle =
    "QLineEdit { color: #000000; background-color: rgba(255, 255, 255, 50%); "
    "border: 2px solid #ccc; border-radius: 5px; font-size: 16px; padding: "
    "5px; background-image: url(path/to/image.png); } QLineEdit:focus { "
    "border: 2px solid #0078d7; background-color: #ffffff; }";

static const QString linkStyle = "a{"
                                 "color: #f2f2f2;"
                                 "text-decoration: underline;"
                                 "}"
                                 "a:hover {"
                                 "color: blue;"
                                 "text-decoration: none;"
                                 "}";

constexpr int COUNT = 5;

enum class Error : unsigned int{
   Unknown = 1,
   InvalidInput,
   DiskFull,
   NotFound,
   Closed
};


enum class ActionType : unsigned int {
    Login,
    SignUp,
    GetData
};
