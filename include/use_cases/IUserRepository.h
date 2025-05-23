#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "entities/User.h"

namespace UseCases {
    // Data Access Interface (抽象接口)
    class IUserRepository {
    public:
        virtual ~IUserRepository() = default;
        
        virtual void save(const Entities::User& user) = 0;
        virtual std::optional<Entities::User> findById(int id) = 0;
        virtual std::optional<Entities::User> findByEmail(const std::string& email) = 0;
        virtual std::vector<Entities::User> findAll() = 0;
        virtual bool deleteById(int id) = 0;
        virtual int getNextId() = 0;
    };
} 