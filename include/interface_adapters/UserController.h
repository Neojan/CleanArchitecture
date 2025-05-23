#pragma once
#include "use_cases/UserUseCaseInterfaces.h"
#include <memory>
#include <string>

namespace InterfaceAdapters {
    // Controller - 处理用户输入并调用相应的用例
    class UserController {
    private:
        std::shared_ptr<UseCases::IUserInputBoundary> userManager_;
        
    public:
        explicit UserController(std::shared_ptr<UseCases::IUserInputBoundary> userManager);
        
        void createUser(const std::string& name, const std::string& email);
        void getUser(int id);
        void getAllUsers();
        void updateUser(int id, const std::string& name, const std::string& email);
        void deleteUser(int id);
    };
} 