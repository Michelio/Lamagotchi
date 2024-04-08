set(INCROOT ${PROJECT_SOURCE_DIR}/inc)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_HEADERS
    ${INCROOT}/lamagotchi/ui/main_window.h
    ${INCROOT}/lamagotchi/network/tcp_client.h
    ${INCROOT}/lamagotchi/network/tcp_connection.h)
set(PROJECT_SOURCES
    ${SRCROOT}/main.cpp ${SRCROOT}/ui/main_window.cpp
    ${SRCROOT}/network/tcp_client.cpp ${SRCROOT}/network/tcp_connection.cpp)

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
  PUBLIC ${INCROOT}
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
