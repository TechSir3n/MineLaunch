#pragma once

class JsonParse {
public:
    JsonParse();

private:
  [[nodiscard]] QStringList gameArguments() const;

  [[nodiscard]] QStringList classPath() const;

  [[nodiscard]] QString mainClass() const;
};
