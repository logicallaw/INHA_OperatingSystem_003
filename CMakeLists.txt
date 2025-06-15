cmake_minimum_required(VERSION 3.13)
project(INHA_OperatingSystem_003)

set(CMAKE_CXX_STANDARD 14)

# Producer/Consumer sol - condition variable
add_executable(Producer_Consumer_Sol_Condition_Variable src/producer_consumer_problems/producer_consumer_sol_condition_variable.c)
target_link_libraries(Producer_Consumer_Sol_Condition_Variable pthread)

# Readers/Writers - Reader Preference
add_executable(ReaderPreference src/readers_writers_problems/reader_preference.c)
target_link_libraries(ReaderPreference pthread)

# Readers/Writers - Writer Preference
add_executable(WriterPreference src/readers_writers_problems/writer_preference.c)
target_link_libraries(WriterPreference pthread)