#pragma once
#include "use_cases/IUserRepository.h"
#include <map>
#include <vector>

namespace FrameworksDrivers {
    // In-Memory User Repository - 数据库具体实现
    class InMemoryUserRepository : public UseCases::IUserRepository {
    private:
        std::map<int, Entities::User> users_;
        int nextId_;
        
    public:
        InMemoryUserRepository();
        
        // IUserRepository implementation
        void save(const Entities::User& user) override;
        std::optional<Entities::User> findById(int id) override;
        std::optional<Entities::User> findByEmail(const std::string& email) override;
        std::vector<Entities::User> findAll() override;
        bool deleteById(int id) override;
        int getNextId() override;
    };
} 