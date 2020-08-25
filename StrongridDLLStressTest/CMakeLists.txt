set (app_StrongridDLLStressTest_SRCS
./Common.h
./main.cpp
)

add_executable (StrongridDLLTest ${app_StrongridDLLStressTest_SRCS})

target_link_libraries (StrongridDLLTest  StrongridDLL)
