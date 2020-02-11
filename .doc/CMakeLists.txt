find_package(Doxygen)

set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}//doc)

if(DOXYGEN_FOUND)
        doxygen_add_docs(
                dadengine-doc
                ${PROJECT_SOURCE_DIR}
        )
endif()
