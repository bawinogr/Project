TRIBITS_ADD_EXECUTABLE_AND_TEST(
  HFtest
  SOURCES
      HFtest.cpp
)

TRIBITS_COPY_FILES_TO_BINARY_DIR(
HFtest_input SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Water_STO-3G
	     SOURCE_FILES enuc.dat T.dat overlap.dat v_int.dat v_nuc.dat
             DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/Water_STO-3G
             EXEDEPS HFtest
)



