set (lib_StrongridClientBase_SRCS
./PdcClient.cpp
./TcpClient.cpp
)

set (lib_StrongridClientBase_HDRS
./PdcClient.h
./TcpClient.h
)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fPIC")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_library(StrongridClientBase STATIC ${lib_StrongridClientBase_SRCS} ${lib_StrongridClientBase_HDRS})
