//
// Created by Yevhen Yefimov on 6/1/17.
//

#include "vm.h"

void get_st_func(t_car *car)
{
	car->op_tabble.nb_tours--;
}

void	check_carry(t_car *car)
{
	if (car->reg[car->args[1].value - 1] == 0 && car->carry == 0 &&
		car->args[1].name == 1)
		car->carry = 1;
	else if (car->reg[car->args[1].value - 1] != 0 && car->carry == 1 &&
			 car->args[1].name == 1)
		car->carry = 0;
}

void    do_st_func(t_vm *main_struct, t_car *car)
{
	int map_pos;

	map_pos = car->pos + car->args[1].value % IDX_MOD;
    if (car->args[0].name == T_REG && car->args[1].name == T_REG &&
			car->args[0].value > 0 && car->args[1].value > 0 && car->args_error)
        car->reg[car->args[1].value - 1] = car->reg[car->args[0].value - 1];
    else if (car->args[0].name == T_REG && car->args[1].name == T_IND &&
			car->args[0].value > 0 && car->args_error)
	{
		main_struct->coord_for_put_int_on_map = map_pos;
		put_int_on_map(main_struct, car->reg[car->args[0].value - 1],
					   main_struct->color + map_pos, car->color);
	}
    else
    {
        car->op_tabble.opcode = 0;
        car->pos++;
        return ;
    }
	check_carry(car);
	car->op_tabble.opcode = 0;
	car->pos = car->pos + car->arg_size + 2;
}