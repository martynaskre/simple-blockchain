project(Blockchain_src)

set(HEADER_FILES Hash.h Manager.h User.h Transaction.h)

set(SOURCE_FILES Hash.cpp Manager.cpp User.cpp Transaction.cpp)

add_library(Blockchain_src STATIC ${SOURCE_FILES} ${HEADER_FILES})