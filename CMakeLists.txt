cmake_minimum_required(VERSION 3.16)
project(CleanArchitectureExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(clean_architecture_demo
    src/main.cpp
    src/entities/User.cpp
    src/use_cases/UserManager.cpp
    src/interface_adapters/UserController.cpp
    src/interface_adapters/UserPresenter.cpp
    src/interface_adapters/ConsoleView.cpp
    src/frameworks_drivers/InMemoryUserRepository.cpp
)

# Include directories
target_include_directories(clean_architecture_demo PRIVATE
    include
)

# Compiler-specific options
if(MSVC)
    target_compile_options(clean_architecture_demo PRIVATE /W4)
else()
    target_compile_options(clean_architecture_demo PRIVATE -Wall -Wextra -Wpedantic)
endif() 