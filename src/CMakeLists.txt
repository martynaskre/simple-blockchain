project(Blockchain_src)

find_package(OpenMP REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(HEADER_FILES Hash.h Manager.h User.h Transaction.h Pools/UsersPool.h Utils/StringGenerator.h Utils/NumberGenerator.h Pools/TransactionsPool.h Utils/Logger.h Utils/Color.h Block.h Cli.h Utils/Application.h Pools/BlocksPool.h Utils/MerkleTree.h)

set(SOURCE_FILES Hash.cpp Manager.cpp User.cpp Transaction.cpp Pools/UsersPool.cpp Utils/StringGenerator.cpp Utils/NumberGenerator.cpp Pools/TransactionsPool.cpp Utils/Logger.cpp Utils/Color.cpp Block.cpp Cli.cpp Utils/Application.cpp Pools/BlocksPool.cpp Utils/MerkleTree.cpp)

add_library(Blockchain_src STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Blockchain_src
        PUBLIC nlohmann_json::nlohmann_json
        PRIVATE OpenMP::OpenMP_CXX)