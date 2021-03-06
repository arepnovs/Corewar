/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dburtnja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:36:30 by dburtnja          #+#    #+#             */
/*   Updated: 2017/07/03 18:36:32 by dburtnja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_int_from_byte_code(char *byte_array)
{
	int	i;

	i = ((byte_array[0] & 0xFF) << 24) + ((byte_array[1] & 0xFF) << 16)
			+ ((byte_array[2] & 0xFF) << 8) + (byte_array[3] & 0xFF);
	return (i);
}

void	get_live_func(t_car *car)
{
	car->op_tabble.nb_tours--;
}

int		check_who_live(unsigned int number, t_vm *main_struct)
{
	int	i;

	i = 0;
	while (main_struct->players[i])
	{
		if (number == (unsigned int)main_struct->players[i]->name)
		{
			main_struct->players[i]->lives_in_current_period++;
			main_struct->nbr_of_lifes++;
			if (main_struct->f_alive)
				ft_printf("Player %d (%s) is said to be alive\n",
					-number, main_struct->players[i]->bot_name);
			return (main_struct->players[i]->name);
		}
		i++;
	}
	return (0);
}

void	do_live_func(t_vm *main_struct, t_car *car)
{
	unsigned int	number;
	int				new_life;
	int				ptr;

	car->live = 1;
	ptr = car->pos + 1;
	if (ptr > MEM_SIZE - 1)
		ptr = ptr - MEM_SIZE;
	main_struct->count_live_functions++;
	number = (unsigned int)get_int_from_byte_code(main_struct->map + ptr);
	new_life = check_who_live(number, main_struct);
	if (new_life != 0)
	{
		main_struct->last_live[0] = new_life;
		main_struct->last_live[1] = main_struct->cycle;
	}
	car->pos = car->pos + DIR_SIZE + 1;
	car->op_tabble.opcode = 0;
	fix_car_pos(car);
}
