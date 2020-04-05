# tests/CMakeLists.txt

add_executable(tests
	tests.cpp
)

target_link_libraries(tests
	Catch2::Catch2
	oping
)

add_dependencies(tests
	oping
)