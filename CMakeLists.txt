cmake_minimum_required(VERSION 3.16)

project(rtkit-unix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

option(BUILD_RTKIT_TEST "Compile the rtkit-test program from the original rtkit codebase")
set(RTKIT_USER root CACHE STRING "User to run the daemon under")

include(cmake/setup_platform.cmake)

find_package(ECM)
if (ECM_FOUND)
  include(${ECM_MODULE_DIR}/ECMEnableSanitizers.cmake)
endif()

find_package(Qt6Core REQUIRED)
find_package(Qt6DBus REQUIRED)
find_package(PolkitQt6-1 REQUIRED)

configure_file(
    data/org.freedesktop.RealtimeKit1.service.in
    data/org.freedesktop.RealtimeKit1.service
    @ONLY
)

configure_file(
    data/org.freedesktop.RealtimeKit1.conf.in
    data/org.freedesktop.RealtimeKit1.conf
    @ONLY
)

add_subdirectory(daemon)
add_subdirectory(lib)
if (BUILD_RTKIT_TEST)
    add_subdirectory(poettering-rtkit-test)
endif()

install(FILES "${CMAKE_BINARY_DIR}/data/org.freedesktop.RealtimeKit1.conf"
    DESTINATION "share/dbus-1/system.d")
install(FILES "data/org.freedesktop.RealtimeKit1.policy"
    DESTINATION "share/polkit-1/actions")
install(FILES "${CMAKE_BINARY_DIR}/data/org.freedesktop.RealtimeKit1.service"
    DESTINATION "share/dbus-1/system-services")
