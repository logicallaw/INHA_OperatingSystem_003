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

# Dining Phiosophers - No Hold and Wait
add_executable(NoHoldAndWait src/dining_philosophers_problems/dining_philosophers_sol_no_hold_and_wait.c)
target_link_libraries(NoHoldAndWait pthread)

# Dining Phiosophers - Resource Ordering
add_executable(ResourceOrdering src/dining_philosophers_problems/dining_philosophers_sol_no_hold_and_wait.c)
target_link_libraries(ResourceOrdering pthread)

# Dining Phiosophers - Bankers algorithm
add_executable(BankersAlgorithm src/dining_philosophers_problems/dining_philosophers_sol_bankers_algorithm.c)
target_link_libraries(BankersAlgorithm pthread)