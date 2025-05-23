#pragma once
#include <string>
#include <vector>
#include <memory>

namespace UseCases {
    // Input Data structures
    struct CreateUserRequest {
        std::string name;
        std::string email;
    };
    
    struct UpdateUserRequest {
        int id;
        std::string name;
        std::string email;
    };
    
    // Output Data structures
    struct UserResponse {
        int id;
        std::string name;
        std::string email;
        std::string displayName;
    };
    
    struct CreateUserResponse {
        bool success;
        std::string message;
        UserResponse user;
    };
    
    struct GetUserResponse {
        bool success;
        std::string message;
        UserResponse user;
    };
    
    struct GetAllUsersResponse {
        bool success;
        std::string message;
        std::vector<UserResponse> users;
    };
    
    // Input Boundary (Use Case Interface)
    class IUserInputBoundary {
    public:
        virtual ~IUserInputBoundary() = default;
        virtual void createUser(const CreateUserRequest& request) = 0;
        virtual void getUser(int id) = 0;
        virtual void getAllUsers() = 0;
        virtual void updateUser(const UpdateUserRequest& request) = 0;
        virtual void deleteUser(int id) = 0;
    };
    
    // Output Boundary (Presenter Interface)
    class IUserOutputBoundary {
    public:
        virtual ~IUserOutputBoundary() = default;
        virtual void presentCreateUserResult(const CreateUserResponse& response) = 0;
        virtual void presentGetUserResult(const GetUserResponse& response) = 0;
        virtual void presentGetAllUsersResult(const GetAllUsersResponse& response) = 0;
        virtual void presentUpdateUserResult(const CreateUserResponse& response) = 0;
        virtual void presentDeleteUserResult(bool success, const std::string& message) = 0;
    };
} 