# CMake generated Testfile for 
# Source directory: /export/zgid/bawinogr/Test
# Build directory: /export/zgid/bawinogr/Test/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_HFtest "/export/zgid/bawinogr/Test/build/Test_HFtest.exe")
set_tests_properties(Test_HFtest PROPERTIES  FAIL_REGULAR_EXPRESSION "The following Teuchos::RCPNode objects were created" LABELS "Test" PROCESSORS "1" REQUIRED_FILES "/export/zgid/bawinogr/Test/build/Test_HFtest.exe")
subdirs(ScientificComputingProject/HF_source)
