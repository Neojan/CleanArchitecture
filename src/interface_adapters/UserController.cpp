#include "interface_adapters/UserController.h"

namespace InterfaceAdapters {
    UserController::UserController(std::shared_ptr<UseCases::IUserInputBoundary> userManager)
        : userManager_(userManager) {}
    
    void UserController::createUser(const std::string& name, const std::string& email) {
        UseCases::CreateUserRequest request{name, email};
        userManager_->createUser(request);
    }
    
    void UserController::getUser(int id) {
        userManager_->getUser(id);
    }
    
    void UserController::getAllUsers() {
        userManager_->getAllUsers();
    }
    
    void UserController::updateUser(int id, const std::string& name, const std::string& email) {
        UseCases::UpdateUserRequest request{id, name, email};
        userManager_->updateUser(request);
    }
    
    void UserController::deleteUser(int id) {
        userManager_->deleteUser(id);
    }
} 