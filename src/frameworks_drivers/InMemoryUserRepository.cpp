#include "frameworks_drivers/InMemoryUserRepository.h"

namespace FrameworksDrivers {
    InMemoryUserRepository::InMemoryUserRepository() : nextId_(1) {}
    
    void InMemoryUserRepository::save(const Entities::User& user) {
        users_[user.getId()] = user;
    }
    
    std::optional<Entities::User> InMemoryUserRepository::findById(int id) {
        auto it = users_.find(id);
        if (it != users_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    std::optional<Entities::User> InMemoryUserRepository::findByEmail(const std::string& email) {
        for (const auto& pair : users_) {
            if (pair.second.getEmail() == email) {
                return pair.second;
            }
        }
        return std::nullopt;
    }
    
    std::vector<Entities::User> InMemoryUserRepository::findAll() {
        std::vector<Entities::User> result;
        for (const auto& pair : users_) {
            result.push_back(pair.second);
        }
        return result;
    }
    
    bool InMemoryUserRepository::deleteById(int id) {
        auto it = users_.find(id);
        if (it != users_.end()) {
            users_.erase(it);
            return true;
        }
        return false;
    }
    
    int InMemoryUserRepository::getNextId() {
        return nextId_++;
    }
} 