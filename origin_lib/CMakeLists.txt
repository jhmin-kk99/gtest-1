project(RvcController)

set(HEADER_FILE RvcController.h)
set(SOURCE_FILE RvcController.c)

add_library(origin_lib STATIC ${SOURCE_FILE} ${HEADER_FILE})