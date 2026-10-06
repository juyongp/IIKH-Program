cmake_minimum_required(VERSION 3.20)
project(KitchenHelper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(KitchenHelper
    main.cpp
    Greeter.cpp
    Ingredient.cpp
    Recipe.cpp
    RecipeDatabase.cpp
    Utility.cpp
)
