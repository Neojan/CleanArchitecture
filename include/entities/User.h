#pragma once
#include <string>
#include <memory>

namespace Entities {
    class User {
    private:
        int id_;
        std::string name_;
        std::string email_;
        
    public:
        User() = default;
        User(int id, const std::string& name, const std::string& email);
        
        // Getters
        int getId() const;
        const std::string& getName() const;
        const std::string& getEmail() const;
        
        // Setters
        void setName(const std::string& name);
        void setEmail(const std::string& email);
        
        // Business logic
        bool isValidEmail() const;
        std::string getDisplayName() const;
    };
} 