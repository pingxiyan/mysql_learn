CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET (TARGET_NAME call_mysql)

PROJECT(${TARGET_NAME})

MESSAGE(STATUS "==================================")
MESSAGE(STATUS "Start:${TARGET_NAME}")

ADD_DEFINITIONS(-std=c++11)
ADD_DEFINITIONS(-DIMPLEMENT_MYSQL_API=1)

IF (WIN32)
	SET(MySQL_INCDIR "C:/Program Files/MySQL/Connector C++ 8.0/include")
	SET(MySQL_LIBS "C:/Program Files/MySQL/Connector C++ 8.0/lib64/vs14/mysqlcppconn.lib")
	SET(BOOST_INCDIR "C:/local/boost_1_67_0")
ELSE ()
	SET(MySQL_INCDIR "/usr/local/include")
	SET(MySQL_LIBS "/usr/local/lib/mysqlcppconn.lib")
ENDIF ()

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/public
	${CMAKE_CURRENT_SOURCE_DIR}/private
	${BOOST_INCDIR}
	${MySQL_INCDIR}
	)

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_FILES)

FILE(GLOB_RECURSE HEADER_FILES  *.h *.hpp)
SOURCE_GROUP("Include" FILES ${HEADER_FILES})

ADD_LIBRARY(${TARGET_NAME} SHARED ${HEADER_FILES} ${SRC_FILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} 
	${MySQL_LIBS}
	)

# Set output directory: build
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#set export lib and header path
#==========================================
set(${PROJECT_NAME}_LIBS
	${TARGET_NAME}
	CACHE INTERNAL "export include path variable")

set(${PROJECT_NAME}_INCDIR
	${CMAKE_CURRENT_SOURCE_DIR}/public
	CACHE INTERNAL "export include path variable")

add_subdirectory(test)