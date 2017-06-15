//
// Created by Yevhen Yefimov on 6/1/17.
//

#include "vm.h"

void get_st_func(t_car *car)
{
   // car->data = ft_memdup(4, map, (*pos) + 1);
	car->op_tabble.nb_tours = car->op_tabble.nb_tours - 1;
	ft_printf ("-> read ST intruction, data =\n");
}

void    do_st_func(t_vm *main_struct, t_car *car)
{
    if (car->args[0].name == 1 && car->args[1].name == 1 && car->args[0]
         .value > 0 && car->args[1].value > 0)
        car->reg[car->args[1].value - 1] = car->reg[car->args[0].value - 1];
    else if (car->args[0].name == 1 && car->args[1].name == 2 && car->args[0]
                                                                         .value > 0)
		put_int_on_map(main_struct->map + car->pos + car->args[1].value %
													 IDX_MOD,
					   car->reg[car->args[0]
												.value - 1],
					   main_struct->color, car->color);
    else
    {
        car->op_tabble.opcode = 0;
        car->pos = car->pos++;
        return ;
    }
	car->op_tabble.opcode = 0;
	car->pos = car->pos + car->arg_size + 2;
    ft_printf("ST HAX!!!!\n");
    car->data = NULL;
}
