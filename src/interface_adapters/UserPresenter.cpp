#include "interface_adapters/UserPresenter.h"
#include <sstream>

namespace InterfaceAdapters {
    UserPresenter::UserPresenter(std::shared_ptr<IView> view)
        : view_(view) {}
    
    void UserPresenter::presentCreateUserResult(const UseCases::CreateUserResponse& response) {
        if (response.success) {
            std::ostringstream oss;
            oss << "User created successfully!\n"
                << "ID: " << response.user.id << "\n"
                << "Name: " << response.user.name << "\n"
                << "Email: " << response.user.email;
            view_->showUser(oss.str());
        } else {
            view_->showError("Failed to create user: " + response.message);
        }
    }
    
    void UserPresenter::presentGetUserResult(const UseCases::GetUserResponse& response) {
        if (response.success) {
            std::ostringstream oss;
            oss << "User Details:\n"
                << "ID: " << response.user.id << "\n"
                << "Name: " << response.user.name << "\n"
                << "Email: " << response.user.email << "\n"
                << "Display: " << response.user.displayName;
            view_->showUser(oss.str());
        } else {
            view_->showError("Failed to get user: " + response.message);
        }
    }
    
    void UserPresenter::presentGetAllUsersResult(const UseCases::GetAllUsersResponse& response) {
        if (response.success) {
            if (response.users.empty()) {
                view_->showMessage("No users found.");
                return;
            }
            
            std::ostringstream oss;
            oss << "All Users:\n";
            oss << "==========\n";
            for (const auto& user : response.users) {
                oss << "ID: " << user.id 
                    << " | Name: " << user.name 
                    << " | Email: " << user.email << "\n";
            }
            view_->showUsers(oss.str());
        } else {
            view_->showError("Failed to get users: " + response.message);
        }
    }
    
    void UserPresenter::presentUpdateUserResult(const UseCases::CreateUserResponse& response) {
        if (response.success) {
            std::ostringstream oss;
            oss << "User updated successfully!\n"
                << "ID: " << response.user.id << "\n"
                << "Name: " << response.user.name << "\n"
                << "Email: " << response.user.email;
            view_->showUser(oss.str());
        } else {
            view_->showError("Failed to update user: " + response.message);
        }
    }
    
    void UserPresenter::presentDeleteUserResult(bool success, const std::string& message) {
        if (success) {
            view_->showMessage("User deleted successfully!");
        } else {
            view_->showError("Failed to delete user: " + message);
        }
    }
} 