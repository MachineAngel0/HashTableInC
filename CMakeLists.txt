cmake_minimum_required(VERSION 3.30)
project(HashTableInC C)

set(CMAKE_C_STANDARD 11)

add_executable(HashTableInC main.c
        HashTable_Tut.c
        HashTable_Tut.h
        HashTable_Mine.c
        HashTable_Mine.h)
