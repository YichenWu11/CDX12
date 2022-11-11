project(UGraphviz)

add_library(${PROJECT_NAME} 
    src/core/Graph.cpp
    src/core/Registry.cpp
    src/core/Subgraph.cpp
)

add_library(Ubpa::UGraphviz ALIAS ${PROJECT_NAME})

# target_include_directories(${PROJECT_NAME}
#     PUBLIC ${UGraphviz_SOURCE_DIR}/include
# )
