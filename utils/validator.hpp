#pragma once

#include <boost/regex.hpp>

class Validator {
public:
    bool isValidEmail(const std::string &email) const {
        static const boost::regex pattern(
            "^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
        return boost::regex_match(email, pattern);
    }

    bool isValidPassword(const std::string &password) const {
        static const boost::regex pattern("^[a-zA-Z0-9]{8,}$");
        return boost::regex_match(password, pattern);
    }

    bool isValidUsername(const std::string &username) const{
        static const boost::regex pattern("^[a-zA-Z0-9]{1,15}$");
        return boost::regex_match(username, pattern);
    }
};
