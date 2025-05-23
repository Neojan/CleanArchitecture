#pragma once
#include "use_cases/UserUseCaseInterfaces.h"
#include <memory>

namespace InterfaceAdapters {
    // Forward declaration
    class IView;
    
    // Presenter - 实现Output Boundary，格式化数据给View
    class UserPresenter : public UseCases::IUserOutputBoundary {
    private:
        std::shared_ptr<IView> view_;
        
    public:
        explicit UserPresenter(std::shared_ptr<IView> view);
        
        // IUserOutputBoundary implementation
        void presentCreateUserResult(const UseCases::CreateUserResponse& response) override;
        void presentGetUserResult(const UseCases::GetUserResponse& response) override;
        void presentGetAllUsersResult(const UseCases::GetAllUsersResponse& response) override;
        void presentUpdateUserResult(const UseCases::CreateUserResponse& response) override;
        void presentDeleteUserResult(bool success, const std::string& message) override;
    };
    
    // View Interface - 抽象视图接口
    class IView {
    public:
        virtual ~IView() = default;
        virtual void showMessage(const std::string& message) = 0;
        virtual void showUser(const std::string& userInfo) = 0;
        virtual void showUsers(const std::string& usersInfo) = 0;
        virtual void showError(const std::string& error) = 0;
    };
} 