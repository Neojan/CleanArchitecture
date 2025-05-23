#pragma once
#include "UserUseCaseInterfaces.h"
#include "IUserRepository.h"
#include <memory>

namespace UseCases {
    // Use Case Interactor - 包含应用程序的业务逻辑
    class UserManager : public IUserInputBoundary {
    private:
        std::shared_ptr<IUserRepository> repository_;
        std::shared_ptr<IUserOutputBoundary> presenter_;
        
        UserResponse mapToUserResponse(const Entities::User& user) const;
        
    public:
        UserManager(std::shared_ptr<IUserRepository> repository,
                   std::shared_ptr<IUserOutputBoundary> presenter);
        
        // IUserInputBoundary implementation
        void createUser(const CreateUserRequest& request) override;
        void getUser(int id) override;
        void getAllUsers() override;
        void updateUser(const UpdateUserRequest& request) override;
        void deleteUser(int id) override;
    };
} 