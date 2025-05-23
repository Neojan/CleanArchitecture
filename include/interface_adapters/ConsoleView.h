#pragma once
#include "UserPresenter.h"
#include <iostream>

namespace InterfaceAdapters {
    // Console View - 控制台具体视图实现
    class ConsoleView : public IView {
    public:
        void showMessage(const std::string& message) override;
        void showUser(const std::string& userInfo) override;
        void showUsers(const std::string& usersInfo) override;
        void showError(const std::string& error) override;
    };
} 