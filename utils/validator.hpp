#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <boost/regex.hpp>


class Validator  {
public:
    bool isValidEmail(const std::string& email) const {
        static const boost::regex pattern("^([\\w\\.\\-]+)@([\\w\\-]+)((\\.(\\w){2,3})+)$");
        return boost::regex_match(email, pattern);
    }

    bool isValidPassword(const std::string& password) const {
        static const boost::regex pattern("^([a-zA-Z0-9]+)$");

        if(password.size() < 8) {
            return false;
        }

        if(!boost::regex_match(password, pattern)){
            return false;
        }

        return  true;
    }

    bool isValidUsername(const std::string& username) {
        static const boost::regex pattern("^[a-zA-Z][a-zA-Z0-9]{2,19}$");
        return boost::regex_match(username, pattern);
    }
};


#endif
