# Clean Architecture Example in C++

这是一个基于《架构整洁之道》（Clean Architecture）的C++示例实现，展示了如何构建一个遵循整洁架构原则的用户管理系统。

## 架构概述

本项目严格按照整洁架构的同心圆模型组织代码：

### 整洁架构层次图

```
┌─────────────────────────────────────────────────────────────┐
│                 Frameworks & Drivers                       │
│  ┌─────────────────────────────────┐                        │
│  │ InMemoryUserRepository          │ 数据持久化              │
│  └─────────────────────────────────┘                        │
└─────────────────────────────────────────────────────────────┘
           ↑ (实现IUserRepository接口)
┌─────────────────────────────────────────────────────────────┐
│               Interface Adapters                           │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────┐  │
│  │ UserController  │  │ UserPresenter   │  │ ConsoleView │  │
│  │ (输入适配)       │  │ (输出适配)       │  │ (视图)       │  │
│  └─────────────────┘  └─────────────────┘  └─────────────┘  │
└─────────────────────────────────────────────────────────────┘
           ↑                        ↑
           ↑ (调用用例)              ↑ (实现输出边界)
┌─────────────────────────────────────────────────────────────┐
│                      Use Cases                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │              UserManager                            │    │
│  │  ┌─────────────────┐  ┌─────────────────────────┐   │    │
│  │  │ IUserRepository │  │ IUserInputBoundary      │   │    │
│  │  │ (数据接口)       │  │ IUserOutputBoundary     │   │    │
│  │  └─────────────────┘  └─────────────────────────┘   │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
                           ↑
                           ↑ (使用实体)
┌─────────────────────────────────────────────────────────────┐
│                      Entities                              │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                    User                             │    │
│  │  - 业务规则                                          │    │
│  │  - 数据验证                                          │    │
│  │  - 核心逻辑                                          │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

### 依赖流向

```
main.cpp → UserController → UserManager → User
    ↓           ↓              ↓
ConsoleView ← UserPresenter ← UserManager → IUserRepository
    ↑                                           ↑
    └─────────────────────────────────────InMemoryUserRepository
```

### 层次说明

#### 1. Entities（实体层）
- **位置**: `include/entities/` 和 `src/entities/`
- **职责**: 包含企业业务规则和最核心的业务逻辑
- **组件**: `User` - 用户实体类
- **特点**: 不依赖任何外层代码，包含业务规则、数据验证和核心逻辑

#### 2. Use Cases（用例层）
- **位置**: `include/use_cases/` 和 `src/use_cases/`
- **职责**: 包含应用程序特定的业务规则
- **组件**: 
  - `IUserRepository` - 数据访问接口
  - `UserUseCaseInterfaces` - 输入/输出边界接口
  - `UserManager` - 用例交互器
- **特点**: 定义抽象接口，不依赖具体实现

#### 3. Interface Adapters（接口适配器层）
- **位置**: `include/interface_adapters/` 和 `src/interface_adapters/`
- **职责**: 转换数据格式，适配不同的接口
- **组件**:
  - `UserController` - 控制器（输入适配）
  - `UserPresenter` - 展示器（输出适配）
  - `ConsoleView` - 视图接口和控制台实现
- **特点**: 将外部格式转换为内层可用的格式

#### 4. Frameworks & Drivers（框架和驱动层）
- **位置**: `include/frameworks_drivers/` 和 `src/frameworks_drivers/`
- **职责**: 具体的技术实现细节
- **组件**: `InMemoryUserRepository` - 内存数据仓储实现
- **特点**: 可以轻松替换不同的技术实现

## 数据流示例：创建用户

```
1. 用户输入 → UserController.createUser()
   
2. UserController → UserManager.createUser(CreateUserRequest)
   
3. UserManager 执行业务逻辑：
   - 验证输入数据
   - 检查邮箱是否已存在 (通过 IUserRepository)
   - 创建 User 实体
   - 验证 User 业务规则
   - 保存到仓储 (通过 IUserRepository)
   
4. UserManager → UserPresenter.presentCreateUserResult()
   
5. UserPresenter → ConsoleView.showUser() 或 showError()
   
6. ConsoleView → 控制台输出
```

## 关键特性

### 1. 依赖倒置 (Dependency Inversion)
- `UserManager` 依赖 `IUserRepository` 抽象，而非具体实现
- `UserPresenter` 依赖 `IView` 抽象，而非具体视图

### 2. 边界分离 (Boundary Separation)
- **输入边界**: `IUserInputBoundary` - 定义用例入口
- **输出边界**: `IUserOutputBoundary` - 定义结果输出

### 3. 数据传输对象 (DTOs)
- `CreateUserRequest/UpdateUserRequest` - 输入数据
- `UserResponse/CreateUserResponse` - 输出数据

### 4. 实体完整性 (Entity Integrity)
- `User` 实体包含业务验证逻辑
- 不依赖任何外部组件

## 依赖规则

整洁架构最重要的规则是**依赖规则**：

> 源代码依赖只能指向内层。内层的任何代码都不应该知道外层的任何事情。

在本项目中：
- `Entities` 不依赖任何其他层
- `Use Cases` 只依赖 `Entities`
- `Interface Adapters` 依赖 `Use Cases` 和 `Entities`
- `Frameworks & Drivers` 依赖所有内层

## 构建和运行

### 前置要求
- CMake 3.16+
- C++17 兼容的编译器
- 支持 `std::optional` 和 `std::regex`

### 构建步骤

```bash
# 克隆项目
git clone <repository-url>
cd CleanArchitecture

# 创建构建目录
mkdir build
cd build

# 配置和构建
cmake ..
make

# 运行程序
./clean_architecture_demo
```

### 使用说明

程序启动后会显示菜单，支持以下操作：
1. 创建用户
2. 查看用户
3. 查看所有用户
4. 更新用户
5. 删除用户

### 快速演示

运行演示脚本查看完整功能：
```bash
./demo.sh
```

## 项目结构

```
CleanArchitecture/
├── CMakeLists.txt
├── README.md
├── demo.sh
├── include/
│   ├── entities/
│   │   └── User.h
│   ├── use_cases/
│   │   ├── IUserRepository.h
│   │   ├── UserUseCaseInterfaces.h
│   │   └── UserManager.h
│   ├── interface_adapters/
│   │   ├── UserController.h
│   │   ├── UserPresenter.h
│   │   └── ConsoleView.h
│   └── frameworks_drivers/
│       └── InMemoryUserRepository.h
└── src/
    ├── main.cpp
    ├── entities/
    │   └── User.cpp
    ├── use_cases/
    │   └── UserManager.cpp
    ├── interface_adapters/
    │   ├── UserController.cpp
    │   ├── UserPresenter.cpp
    │   └── ConsoleView.cpp
    └── frameworks_drivers/
        └── InMemoryUserRepository.cpp
```

## 设计模式和原则

本项目体现了以下设计原则：

1. **单一职责原则**：每个类都有明确的单一职责
2. **开闭原则**：通过接口实现对扩展开放，对修改关闭
3. **里氏替换原则**：所有接口实现都可以相互替换
4. **接口隔离原则**：定义了小而专一的接口
5. **依赖倒置原则**：高层模块不依赖低层模块，都依赖抽象

## 可扩展性

由于采用了整洁架构，本项目具有高度的可扩展性：

### 添加新的存储方式
只需实现 `IUserRepository` 接口：
```cpp
class DatabaseUserRepository : public IUserRepository {
    // 连接实际数据库
};
```

### 添加Web接口
只需创建新的适配器：
```cpp
class WebUserController {
    // 处理HTTP请求
};

class JsonUserPresenter : public IUserOutputBoundary {
    // 输出JSON格式
};
```

### 添加新业务规则
在 `UserManager` 中增加验证逻辑，或在 `User` 实体中添加业务方法。

## 测试策略

整洁架构使得测试变得容易：

### 单元测试
- **Entities**: 测试 `User` 的业务逻辑
- **Use Cases**: 模拟 `IUserRepository` 和 `IUserOutputBoundary`
- **Adapters**: 独立测试每个适配器

### 集成测试
- 组合真实的仓储和展示器
- 测试完整的数据流

### 端到端测试
- 使用完整的组件栈
- 测试用户交互场景

## 架构优势

这种架构确保了：
1. **可测试性** - 每层都可以独立测试
2. **可维护性** - 修改一层不影响其他层
3. **可扩展性** - 易于添加新功能和替换组件
4. **业务逻辑隔离** - 核心业务不受技术细节影响

## 学习资源

- 《架构整洁之道》- Robert C. Martin
- [Clean Architecture Blog](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)

## 许可证

MIT License
