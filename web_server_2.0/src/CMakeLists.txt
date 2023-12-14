set(SRC_LIST 
    config.cpp
    http.cpp
    log.cpp
    main.cpp
    server.cpp
    sqlconn_pool.cpp
    timer.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/header)

find_library(MYSQL_LIB mysqlclient)

add_executable(XServer ${SRC_LIST})
target_link_libraries(XServer pthread ${MYSQL_LIB})