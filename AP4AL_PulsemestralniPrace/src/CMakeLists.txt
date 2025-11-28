set(SOURCES_LIST list.c data.c)

set(HEADERS_LIST include/list.h include/data.h)

set(LIBNAME_LIST "list")

include(FetchContent)
FetchContent_Declare(
  ioutils
  GIT_REPOSITORY https://ioutils:aFiG6LqzyabnzhxzbhNC@git.vyuka.fai.utb.cz/ads/common/ioutils.git
)

FetchContent_MakeAvailable(ioutils)

FetchContent_Declare(
  myMalloc
  GIT_REPOSITORY https://mymalloc:8zj7GZZNmWyLGgQSyzsN@git.vyuka.fai.utb.cz/ads/common/mymalloc.git
)

FetchContent_MakeAvailable(myMalloc)

add_library(${LIBNAME_LIST} ${SOURCES_LIST} ${HEADERS_LIST})
target_link_libraries(${LIBNAME_LIST} PUBLIC myMalloc ioutils)
target_include_directories(${LIBNAME_LIST} PUBLIC include)
