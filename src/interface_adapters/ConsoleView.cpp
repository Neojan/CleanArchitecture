#include "interface_adapters/ConsoleView.h"

namespace InterfaceAdapters {
    void ConsoleView::showMessage(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }
    
    void ConsoleView::showUser(const std::string& userInfo) {
        std::cout << "[USER] " << userInfo << std::endl;
    }
    
    void ConsoleView::showUsers(const std::string& usersInfo) {
        std::cout << "[USERS] " << usersInfo << std::endl;
    }
    
    void ConsoleView::showError(const std::string& error) {
        std::cerr << "[ERROR] " << error << std::endl;
    }
} 