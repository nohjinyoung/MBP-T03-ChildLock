# CMake generated Testfile for 
# Source directory: D:/CarPart/MBP-T03-ChildLock
# Build directory: D:/CarPart/MBP-T03-ChildLock/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(RescueLogicTest "D:/CarPart/MBP-T03-ChildLock/build/Debug/test_rescue.exe")
  set_tests_properties(RescueLogicTest PROPERTIES  _BACKTRACE_TRIPLES "D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;36;add_test;D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(RescueLogicTest "D:/CarPart/MBP-T03-ChildLock/build/Release/test_rescue.exe")
  set_tests_properties(RescueLogicTest PROPERTIES  _BACKTRACE_TRIPLES "D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;36;add_test;D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(RescueLogicTest "D:/CarPart/MBP-T03-ChildLock/build/MinSizeRel/test_rescue.exe")
  set_tests_properties(RescueLogicTest PROPERTIES  _BACKTRACE_TRIPLES "D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;36;add_test;D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(RescueLogicTest "D:/CarPart/MBP-T03-ChildLock/build/RelWithDebInfo/test_rescue.exe")
  set_tests_properties(RescueLogicTest PROPERTIES  _BACKTRACE_TRIPLES "D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;36;add_test;D:/CarPart/MBP-T03-ChildLock/CMakeLists.txt;0;")
else()
  add_test(RescueLogicTest NOT_AVAILABLE)
endif()
