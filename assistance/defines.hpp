#pragma once

#include <QString>

enum class Error : unsigned int {
  Unknown = 1,
  InvalidInput,
  DiskFull,
  NotFound,
  Closed
};

enum class FileState {
  NotExists = 1,
  OpenError = 2,
  WrongPath = 3,
  AlreadyExists = 4,
  IncorrectFile = 5,
};

enum class LauncherType : unsigned int { Update, Download, Play, Cancel };

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

static const QString tabStyle = "QTabWidget::tab:selected {"
                         "background-color: #FF0000;" // Красный цвет фона
                         "color: #FFFFFF;" // Белый цвет текста
                         "}";

static const QString sliderStyle =
    "QSlider::groove:horizontal {"
    "border: 1px solid #999999;"
    "background: qlineargradient(x1:0, y1:0, x2:0, "
    "y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
    "height: 8px;"
    "border-radius: 4px;"
    "}"

    "QSlider::handle:horizontal {"
    "background: qlineargradient(x1:0, y1:0, x2:1, "
    "y2:1, stop:0 #b4b4b4, stop:1 #8C8C8C);"
    "border: 1px solid #5c5c5c;"
    "width: 18px;"
    "margin: -2px 0;"
    "border-radius: 6px;"
    "}";
