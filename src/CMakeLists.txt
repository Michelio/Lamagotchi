set(INCROOT ${PROJECT_SOURCE_DIR}/inc)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_HEADERS
    ${INCROOT}/lamagotchi/ui/main_window.h
    ${INCROOT}/lamagotchi/crypting/blow_fish.h
    ${INCROOT}/lamagotchi/crypting/rsa.h
    ${INCROOT}/lamagotchi/crypting/xor.h
    ${INCROOT}/lamagotchi/containers/thread_safe_queue.hpp
    ${INCROOT}/lamagotchi/network/tcp_client.h
    ${INCROOT}/lamagotchi/network/tcp_connection.h
    ${INCROOT}/lamagotchi/network/packet_handler.h
    ${INCROOT}/lamagotchi/network/login_handler.h
    ${INCROOT}/lamagotchi/network/gameplay_handler.h
    ${INCROOT}/lamagotchi/network/packets/login/gameguard_auth.hpp
    ${INCROOT}/lamagotchi/network/packets/login/init.hpp
    ${INCROOT}/lamagotchi/network/packets/login/login_fail.hpp
    ${INCROOT}/lamagotchi/network/packets/login/login_ok.hpp
    ${INCROOT}/lamagotchi/network/packets/login/play_fail.hpp
    ${INCROOT}/lamagotchi/network/packets/login/play_ok.hpp
    ${INCROOT}/lamagotchi/network/packets/login/request_gg_auth.hpp
    ${INCROOT}/lamagotchi/network/packets/login/request_login_auth.hpp
    ${INCROOT}/lamagotchi/network/packets/login/request_server_list.hpp
    ${INCROOT}/lamagotchi/network/packets/login/request_server_login.hpp
    ${INCROOT}/lamagotchi/network/packets/login/server_list.hpp
    ${INCROOT}/lamagotchi/network/packets/game/protocol_version.hpp
    ${INCROOT}/lamagotchi/bot_client.h
    ${INCROOT}/lamagotchi/bot_session.h)

set(PROJECT_SOURCES
    ${SRCROOT}/main.cpp
    ${SRCROOT}/ui/main_window.cpp
    ${SRCROOT}/crypting/blow_fish.cpp
    ${SRCROOT}/crypting/rsa.cpp
    ${SRCROOT}/crypting/xor.cpp
    ${SRCROOT}/network/tcp_client.cpp
    ${SRCROOT}/network/tcp_connection.cpp
    ${SRCROOT}/network/packet_handler.cpp
    ${SRCROOT}/network/login_handler.cpp
    ${SRCROOT}/bot_client.cpp
    ${SRCROOT}/bot_session.cpp
    ${SRCROOT}/network/gameplay_handler.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(Lamagotchi MANUAL_FINALIZATION ${PROJECT_SOURCES}
                    ${PROJECT_HEADERS})
  # Define target properties for Android with Qt 6 as: set_property(TARGET
  # Lamagotchi APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  # ${CMAKE_CURRENT_SOURCE_DIR}/android) For more information, see
  # https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(Lamagotchi SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})
    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(Lamagotchi ${PROJECT_SOURCES} ${PROJECT_HEADERS})
  endif()
endif()

target_include_directories(
  Lamagotchi
  PUBLIC ${INCROOT} ${Boost_INCLUDE_DIRS}
  PRIVATE)
target_link_libraries(Lamagotchi PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                         OpenSSL::SSL ${Boost_LIBRARIES})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1. If
# you are developing for iOS or macOS you should consider setting an explicit,
# fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER Lamagotchi)
endif()
set_target_properties(
  Lamagotchi
  PROPERTIES ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)

include(GNUInstallDirs)
install(
  TARGETS Lamagotchi
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Lamagotchi)
endif()
