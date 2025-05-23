#include "entities/User.h"
#include <regex>

namespace Entities {
    User::User(int id, const std::string& name, const std::string& email)
        : id_(id), name_(name), email_(email) {}
    
    int User::getId() const {
        return id_;
    }
    
    const std::string& User::getName() const {
        return name_;
    }
    
    const std::string& User::getEmail() const {
        return email_;
    }
    
    void User::setName(const std::string& name) {
        name_ = name;
    }
    
    void User::setEmail(const std::string& email) {
        email_ = email;
    }
    
    bool User::isValidEmail() const {
        // Simple email validation regex
        std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email_, email_pattern);
    }
    
    std::string User::getDisplayName() const {
        return name_ + " (" + email_ + ")";
    }
} 