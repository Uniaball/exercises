cmake_minimum_required(VERSION 3.10)
project(project1
        VERSION 1.0
        LANGUAGES CXX)

# 基本设置
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON  )   # 不强制使用指定标准

# 如果使用Qt或其他GUI库可取消注释
# set(CMAKE_AUTOMOC ON)               # Qt项目需要
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# 可执行文件配置
add_executable(${PROJECT_NAME}        # 使用项目名称作为可执行文件名
    src/main/main.cpp     # 主源文件
                                      # 其他源文件             
                                      # 头文件
)

# 包含目录
#target_include_directories(${PROJECT_NAME} PRIVATE 
#    ${PROJECT_SOURCE_DIR}/include     # 头文件目录
#)
