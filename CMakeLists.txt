cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-lncurses")
add_executable(corewar main.c handle_error.c parse_flags.c handle_players.c helpers.c handle_process.c pr_memory.c op1.c operations_vm/handle_aff.c operations_vm/handle_forks.c operations_vm/handle_live.c operations_vm/handle_lds.c operations_vm/handle_st.c operations_vm/handle_add_sub.c operations_vm/handle_and_or_xor.c operations_vm/handle_zjmp.c operations_vm/handle_ldi.c operations_vm/handle_stis.c operations_vm/helpers.c)
target_link_libraries(corewar ${CMAKE_SOURCE_DIR}/libft/libft.a)