set(INCROOT ${PROJECT_SOURCE_DIR}/inc/lamagotchi)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_HEADERS
    ${INCROOT}/ui/main_window.h
    ${INCROOT}/crypting/blow_fish.h
    ${INCROOT}/crypting/rsa.h
    ${INCROOT}/crypting/xor.h
    ${INCROOT}/containers/thread_safe_queue.hpp
    ${INCROOT}/network/tcp_client.h
    ${INCROOT}/network/tcp_connection.h
    ${INCROOT}/network/packet_handler.h
    ${INCROOT}/network/login_handler.h
    ${INCROOT}/network/gameplay_handler.h
    ${INCROOT}/network/packets/login/gameguard_auth.hpp
    ${INCROOT}/network/packets/login/init.hpp
    ${INCROOT}/network/packets/login/login_fail.hpp
    ${INCROOT}/network/packets/login/login_ok.hpp
    ${INCROOT}/network/packets/login/play_fail.hpp
    ${INCROOT}/network/packets/login/play_ok.hpp
    ${INCROOT}/network/packets/login/request_gg_auth.hpp
    ${INCROOT}/network/packets/login/request_login_auth.hpp
    ${INCROOT}/network/packets/login/request_server_list.hpp
    ${INCROOT}/network/packets/login/request_server_login.hpp
    ${INCROOT}/network/packets/login/server_list.hpp
    ${INCROOT}/network/packets/game/char_info.hpp
    ${INCROOT}/network/packets/game/char_list.hpp
    ${INCROOT}/network/packets/game/char_selected.hpp
    ${INCROOT}/network/packets/game/crypt_init.hpp
    ${INCROOT}/network/packets/game/move_to_location.hpp
    ${INCROOT}/network/packets/game/npc_info.hpp
    ${INCROOT}/network/packets/game/request_enter_world.hpp
    ${INCROOT}/network/packets/game/request_select_char.hpp
    ${INCROOT}/network/packets/game/request_manor_list.hpp
    ${INCROOT}/network/packets/game/ex_info.hpp
    ${INCROOT}/network/packets/game/net_ping.hpp
    ${INCROOT}/network/packets/game/request_net_ping.hpp
    ${INCROOT}/network/packets/game/request_auth.hpp
    ${INCROOT}/network/packets/game/protocol_version.hpp
    ${INCROOT}/bot_client.h
    ${INCROOT}/bot_session.h)

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
