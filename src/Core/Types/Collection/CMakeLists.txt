add_library(collection TArray.cpp TDictionary.cpp)

target_include_directories(collection PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Core/Types/Collection)