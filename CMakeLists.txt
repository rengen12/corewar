cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-lncurses")
add_executable(corewar main.c handle_error.c parse_flags.c handle_players.c helpers.c handle_process.c pr_memory.c visual1.c operations_vm/handle_aff.c operations_vm/handle_forks.c operations_vm/handle_live.c operations_vm/handle_lds.c operations_vm/handle_st.c operations_vm/handle_add_sub.c operations_vm/handle_and_or_xor.c operations_vm/handle_zjmp.c operations_vm/handle_ldis.c operations_vm/handle_sti.c operations_vm/helpers.c prerr_fr.c start_game.c visual.c find_winner.c set_waiting.c handle_player.c helpers_player.c helpers_process.c handle_events.c)
include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/)

target_link_libraries(corewar ${CMAKE_SOURCE_DIR}/libft/libft.a)