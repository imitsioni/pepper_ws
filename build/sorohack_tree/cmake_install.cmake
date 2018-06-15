# Install script for directory: /home/igmitsio/pepper_ws/src/sorohack_tree

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/igmitsio/pepper_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sorohack_tree/action" TYPE FILE FILES "/home/igmitsio/pepper_ws/src/sorohack_tree/action/BT.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sorohack_tree/msg" TYPE FILE FILES
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTAction.msg"
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTActionGoal.msg"
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTActionResult.msg"
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTActionFeedback.msg"
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTGoal.msg"
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTResult.msg"
    "/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg/BTFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sorohack_tree/cmake" TYPE FILE FILES "/home/igmitsio/pepper_ws/build/sorohack_tree/catkin_generated/installspace/sorohack_tree-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/igmitsio/pepper_ws/devel/include/sorohack_tree")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/igmitsio/pepper_ws/devel/share/roseus/ros/sorohack_tree")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/igmitsio/pepper_ws/devel/share/common-lisp/ros/sorohack_tree")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/igmitsio/pepper_ws/devel/share/gennodejs/ros/sorohack_tree")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/igmitsio/pepper_ws/devel/lib/python2.7/dist-packages/sorohack_tree")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/igmitsio/pepper_ws/devel/lib/python2.7/dist-packages/sorohack_tree")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/igmitsio/pepper_ws/build/sorohack_tree/catkin_generated/installspace/sorohack_tree.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sorohack_tree/cmake" TYPE FILE FILES "/home/igmitsio/pepper_ws/build/sorohack_tree/catkin_generated/installspace/sorohack_tree-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sorohack_tree/cmake" TYPE FILE FILES
    "/home/igmitsio/pepper_ws/build/sorohack_tree/catkin_generated/installspace/sorohack_treeConfig.cmake"
    "/home/igmitsio/pepper_ws/build/sorohack_tree/catkin_generated/installspace/sorohack_treeConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sorohack_tree" TYPE FILE FILES "/home/igmitsio/pepper_ws/src/sorohack_tree/package.xml")
endif()

