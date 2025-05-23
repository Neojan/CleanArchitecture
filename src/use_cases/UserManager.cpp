#include "use_cases/UserManager.h"
#include "entities/User.h"

namespace UseCases {
    UserManager::UserManager(std::shared_ptr<IUserRepository> repository,
                            std::shared_ptr<IUserOutputBoundary> presenter)
        : repository_(repository), presenter_(presenter) {}
    
    UserResponse UserManager::mapToUserResponse(const Entities::User& user) const {
        return UserResponse{
            user.getId(),
            user.getName(),
            user.getEmail(),
            user.getDisplayName()
        };
    }
    
    void UserManager::createUser(const CreateUserRequest& request) {
        // Business logic validation
        if (request.name.empty()) {
            presenter_->presentCreateUserResult({
                false, "Name cannot be empty", {}
            });
            return;
        }
        
        if (request.email.empty()) {
            presenter_->presentCreateUserResult({
                false, "Email cannot be empty", {}
            });
            return;
        }
        
        // Check if user already exists
        auto existingUser = repository_->findByEmail(request.email);
        if (existingUser.has_value()) {
            presenter_->presentCreateUserResult({
                false, "User with this email already exists", {}
            });
            return;
        }
        
        // Create new user entity
        int newId = repository_->getNextId();
        Entities::User newUser(newId, request.name, request.email);
        
        // Validate business rules
        if (!newUser.isValidEmail()) {
            presenter_->presentCreateUserResult({
                false, "Invalid email format", {}
            });
            return;
        }
        
        // Save to repository
        repository_->save(newUser);
        
        // Present success response
        presenter_->presentCreateUserResult({
            true, "User created successfully", mapToUserResponse(newUser)
        });
    }
    
    void UserManager::getUser(int id) {
        auto user = repository_->findById(id);
        if (user.has_value()) {
            presenter_->presentGetUserResult({
                true, "User found", mapToUserResponse(user.value())
            });
        } else {
            presenter_->presentGetUserResult({
                false, "User not found", {}
            });
        }
    }
    
    void UserManager::getAllUsers() {
        auto users = repository_->findAll();
        std::vector<UserResponse> userResponses;
        
        for (const auto& user : users) {
            userResponses.push_back(mapToUserResponse(user));
        }
        
        presenter_->presentGetAllUsersResult({
            true, "Users retrieved successfully", userResponses
        });
    }
    
    void UserManager::updateUser(const UpdateUserRequest& request) {
        auto existingUser = repository_->findById(request.id);
        if (!existingUser.has_value()) {
            presenter_->presentUpdateUserResult({
                false, "User not found", {}
            });
            return;
        }
        
        // Business logic validation
        if (request.name.empty()) {
            presenter_->presentUpdateUserResult({
                false, "Name cannot be empty", {}
            });
            return;
        }
        
        if (request.email.empty()) {
            presenter_->presentUpdateUserResult({
                false, "Email cannot be empty", {}
            });
            return;
        }
        
        // Check if email is already used by another user
        auto userWithEmail = repository_->findByEmail(request.email);
        if (userWithEmail.has_value() && userWithEmail->getId() != request.id) {
            presenter_->presentUpdateUserResult({
                false, "Email is already used by another user", {}
            });
            return;
        }
        
        // Update user entity
        Entities::User updatedUser = existingUser.value();
        updatedUser.setName(request.name);
        updatedUser.setEmail(request.email);
        
        // Validate business rules
        if (!updatedUser.isValidEmail()) {
            presenter_->presentUpdateUserResult({
                false, "Invalid email format", {}
            });
            return;
        }
        
        // Save updated user
        repository_->save(updatedUser);
        
        presenter_->presentUpdateUserResult({
            true, "User updated successfully", mapToUserResponse(updatedUser)
        });
    }
    
    void UserManager::deleteUser(int id) {
        bool deleted = repository_->deleteById(id);
        if (deleted) {
            presenter_->presentDeleteUserResult(true, "User deleted successfully");
        } else {
            presenter_->presentDeleteUserResult(false, "User not found");
        }
    }
} 