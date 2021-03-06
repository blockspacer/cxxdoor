cmake_minimum_required(VERSION 3.0)
project(cxxdoor CXX)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
include_directories(SYSTEM /usr/local/include /usr/include)
link_directories(SYSTEM /usr/local/lib /usr/lib)

find_library(ROCKSDB rocksdb)

set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.60 COMPONENTS date_time filesystem system atomic thread serialization)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

find_library(FOLLY folly)
find_library(WANGLE wangle)
find_library(PTHREAD pthread)
find_library(GLOG glog)
find_library(Z z)
find_library(GFLAGS gflags)
find_library(SSL ssl)
find_library(CRYPTO crypto)
find_library(PROXYGENLIB proxygenlib)
find_library(PROXYGENHTTPSERVER proxygenhttpserver)
find_library(DCONV double-conversion)
find_library(GTEST gtest)
find_library(GTEST_MAIN gtest_main)
find_library(DL dl)
find_library(DEMANGLE demangle)
set(SRC
        usuario.cpp
        rocksentity.cpp
        dbmanager.cpp
        booking.cpp
        usuariocontroller.cpp
        BookingController.cpp
        UsuarioHandler.cpp
        CommandProcessor.cpp
        HandlerFactory.cpp
        AuthenticationProcessor.cpp
        AddUserProcessor.cpp
        authenticationfilter.cpp
        LoggingFilter.cpp)

set(TEST_SRC ${SRC}
        usuariotest.cpp
        bookingstest.cpp)

set(MAIN main.cpp)

# add_library(LIBCXXDOOR SHARED ${SRC})
# d_library(LIBCXXDOOR_TEST SHARED ${TEST_SRC})

set(LIBS
        ${DL}
        ${Boost_LIBRARIES}
        ${ROCKSDB}
        ${Z}
        ${PTHREAD}
        ${CRYPTO}
        ${SSL}
        ${DCONV}
        ${GLOG}
        ${GFLAGS}
        ${FOLLY}
        ${WANGLE}
        ${PROXYGENLIB}
        ${PROXYGENHTTPSERVER}
        )

set(LIBS_TEST
        ${LIBS}
        ${GTEST}
        ${GTEST_MAIN}
        )


add_executable(${PROJECT_NAME} ${MAIN} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})


add_executable(main_test main_test.cpp ${TEST_SRC})
target_link_libraries(main_test ${LIBS_TEST})

enable_testing()
add_test(NAME main_test
        COMMAND main_test)
