#include <iostream>
#include <memory>
#include <string>
#include <limits>

#include "entities/User.h"
#include "use_cases/UserManager.h"
#include "interface_adapters/UserController.h"
#include "interface_adapters/UserPresenter.h"
#include "interface_adapters/ConsoleView.h"
#include "frameworks_drivers/InMemoryUserRepository.h"

class Application {
private:
    std::shared_ptr<InterfaceAdapters::UserController> controller_;

public:
    Application() {
        // Dependency injection setup following Clean Architecture principles
        
        // Frameworks & Drivers layer
        auto repository = std::make_shared<FrameworksDrivers::InMemoryUserRepository>();
        
        // Interface Adapters layer - View
        auto view = std::make_shared<InterfaceAdapters::ConsoleView>();
        
        // Interface Adapters layer - Presenter
        auto presenter = std::make_shared<InterfaceAdapters::UserPresenter>(view);
        
        // Use Cases layer
        auto userManager = std::make_shared<UseCases::UserManager>(repository, presenter);
        
        // Interface Adapters layer - Controller
        controller_ = std::make_shared<InterfaceAdapters::UserController>(userManager);
    }
    
    void run() {
        std::cout << "=================================\n";
        std::cout << "Clean Architecture Example\n";
        std::cout << "User Management System\n";
        std::cout << "=================================\n\n";
        
        bool running = true;
        while (running) {
            showMenu();
            int choice = getChoice();
            
            switch (choice) {
                case 1:
                    createUserMenu();
                    break;
                case 2:
                    getUserMenu();
                    break;
                case 3:
                    getAllUsersMenu();
                    break;
                case 4:
                    updateUserMenu();
                    break;
                case 5:
                    deleteUserMenu();
                    break;
                case 0:
                    running = false;
                    std::cout << "Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
            
            if (running) {
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
        }
    }

private:
    void showMenu() {
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. Create User\n";
        std::cout << "2. Get User\n";
        std::cout << "3. Get All Users\n";
        std::cout << "4. Update User\n";
        std::cout << "5. Delete User\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
    }
    
    int getChoice() {
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
    
    void createUserMenu() {
        std::cout << "\n=== Create User ===\n";
        std::cout << "Name: ";
        std::string name;
        std::getline(std::cin, name);
        
        std::cout << "Email: ";
        std::string email;
        std::getline(std::cin, email);
        
        controller_->createUser(name, email);
    }
    
    void getUserMenu() {
        std::cout << "\n=== Get User ===\n";
        std::cout << "User ID: ";
        int id = getChoice();
        
        controller_->getUser(id);
    }
    
    void getAllUsersMenu() {
        std::cout << "\n=== Get All Users ===\n";
        controller_->getAllUsers();
    }
    
    void updateUserMenu() {
        std::cout << "\n=== Update User ===\n";
        std::cout << "User ID: ";
        int id = getChoice();
        
        std::cout << "New Name: ";
        std::string name;
        std::getline(std::cin, name);
        
        std::cout << "New Email: ";
        std::string email;
        std::getline(std::cin, email);
        
        controller_->updateUser(id, name, email);
    }
    
    void deleteUserMenu() {
        std::cout << "\n=== Delete User ===\n";
        std::cout << "User ID: ";
        int id = getChoice();
        
        controller_->deleteUser(id);
    }
};

int main() {
    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 