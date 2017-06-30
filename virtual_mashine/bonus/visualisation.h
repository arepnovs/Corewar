//
// Created by denys on 13.06.17.
//

#ifndef VIRTUAL_MASHINE_VISUALISATION_H
#define VIRTUAL_MASHINE_VISUALISATION_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "../vm.h"
#include <ncurses.h>
#include <time.h>

# define	COL_ARENA	10
# define	COL_CAR		20
# define	COL_NEW_MEM			30
# define	RED_TEXT_ON_CYAN	40
# define	TIME_TWO_MS			20000
# define	TIME_ONE_S			1000000

void	w_print_arena(t_vm *main_struct);
void	erase_all(t_vis *vis);
void	refresh_all(t_vis *vis);
void	w_print_param(t_vm *main_struct);
void	w_print_usage(WINDOW *win);
void	read_commands(t_vm *main_struct);
void	time_pause(t_vm *main_struct);
void	change_time(t_vm *main_struct, int c);
int		check_if_refresh(t_vm *main_struct);
void	read_commands(t_vm *main_struct);
void	stop_vis_and_exit(t_vm *main_struct);






#endif //VIRTUAL_MASHINE_VISUALISATION_H
