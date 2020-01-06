cmake_minimum_required(VERSION 3.13)
project(ex3_mtm)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(io_files)
include_directories(tests)

add_executable(ex3_mtm
#        io_files/input1.txt
#        io_files/input2.txt
#        io_files/input3.txt
#        io_files/output1.txt
#        io_files/output2.txt
#        io_files/output3.txt
        tests/UniqueArrayTest.cpp
#        final_check.py
#        MtmParkingLot.cpp
#        ParkingLot.h
#        ParkingLotPrinter.cpp
#        ParkingLotPrinter.h
#        ParkingLotTypes.h
#        ParkingSpot.cpp
#        ParkingSpot.h
#        Time.cpp
#        Time.h
#        UniqueArray.cpp
        UniqueArray.h
        UniqueArrayImp.h)