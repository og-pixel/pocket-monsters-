# cmake_minimum_required(VERSION <specify CMake version here>)
project(PocketMonstersPrototype)

set(CMAKE_CXX_STANDARD 11)

add_executable(PocketMonstersPrototype
        Main.cpp
        Menu.cpp
        Menu.h
        Monster/FireMonster.cpp
        Monster/FireMonster.h
        Player.cpp
        Player.h
        stdafx.cpp
        stdafx.h
        targetver.h
        Monster/Monster.cpp Monster/Monster.h Monster/WaterMonster.cpp Monster/WaterMonster.h LoadingSystem.cpp LoadingSystem.h RandomGenerator.cpp RandomGenerator.h Main.h Items/Item.cpp Items/Item.h Items/HealingPotion.cpp Items/HealingPotion.h Items/FirePotion.cpp Items/FirePotion.h Arena.cpp Arena.h Monster/RockMonster.cpp Monster/RockMonster.h)
