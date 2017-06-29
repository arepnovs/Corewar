//
// Created by Yevhen Yefimov on 6/7/17.
//

#include "vm.h"

void	read_args_from_char(t_car *car, unsigned char c, int pos)
{
	unsigned char	buf;
	int				i;

	i = 0;
	car->args[0].name = c >> 6;
	car->args[1].name = (buf = (c >> 4) << 6) >> 6;
	car->args[2].name = (buf = (c >> 2) << 6) >> 6;
	while (i < 3)
	{
		if (car->args[i].name == REG_CODE)
			car->args[i].name = T_REG;
		if (car->args[i].name == DIR_CODE)
			car->args[i].name = T_DIR;
		if (car->args[i].name == IND_CODE)
			car->args[i].name = T_IND;
		i++;
	}
}

int		read_one_arg(t_car *car, unsigned char *map, int read_size)
{
	int		nbr;
	int		i;

	i = 0;
	nbr = 0;
	while (read_size > i)
	{
		nbr = nbr << 8;
		nbr |= map[i];
		i++;
	}
	return (nbr);
}

int 	read_args(t_car *car, unsigned char *map)
{
	int		i;
	int		error;
	int		buf;
	int		label_size;
	int 	read_size;

	i = 0;
	error = FALSE;
	label_size = car->op_tabble.codage_octal == 0 ? DIR_SIZE : IND_SIZE;
	while (i < car->op_tabble.args_am)
	{
		if (car->args[i].name == T_REG)
			read_size = T_REG;          // CHECK IT CYKA!!!!!!OUT
		else if (car->args[i].name == T_DIR)
			read_size = car->op_tabble.codage_octal == 0 ? DIR_SIZE : IND_SIZE;
		else if (car->args[i].name == T_IND)
			read_size = IND_SIZE;
		else
				read_size = 0;
		buf = car->op_tabble.args[i] & car->args[i].name;
		if (buf != car->args[i].name || buf == 0)
			error = TRUE;
		if (error == FALSE)
		{
			car->args[i].value = read_one_arg(car, map, read_size);
			/*if (car->args[i].name == T_IND)
				car->args[i].value = (short)car->args[i].value;*/
		}
		car->arg_size += read_size;
		map += read_size;
		i++;
	}
	return (error);
}

int		get_args_nd_value(t_car *car, t_vm *main_struct)
{
	int		local_pos;
	int 	i;

	i = 0;
	car->arg_size = 0;
	local_pos = car->pos + 1;
	read_args_from_char(car, (unsigned char)main_struct->map[local_pos],
			local_pos);
	local_pos++;
	if (read_args(car, (unsigned char*)main_struct->map + local_pos))
		return FALSE;




	while (i < 2)
	{
		if (car->args[i].name == T_REG && car->op_tabble.opcode != 3 &&
				car->op_tabble.opcode != 11 && car->op_tabble.opcode != 2
			&& car->op_tabble.opcode != 4 && car->op_tabble.opcode != 5)
			car->args[i].value = car->reg[car->args[i].value - 1];
		else if (car->args[i].name == T_IND && car->op_tabble.opcode != 3 &&
				 car->op_tabble.opcode != 11 && car->op_tabble.opcode != 2
				 && car->op_tabble.opcode != 4 && car->op_tabble.opcode != 5)
		{
			if (car->op_tabble.opcode != 14)
				car->args[i].value = get_int_from_byte_code(main_struct->map +
				car->pos + car->args[i].value % IDX_MOD);
			else
				car->args[i].value = get_int_from_byte_code(main_struct->map +
				car->pos + car->args[i].value);
		}
		i++;
	}
	if (car->op_tabble.opcode == 11)
	{
		i = 1;
		while (i < 3)
		{
			if (car->args[i].name == T_REG)
				car->args[i].value = car->reg[car->args[i].value - 1];
			else if (car->args[i].name == T_IND)
			{
				car->args[i].value = get_int_from_byte_code(main_struct->map +
				car->pos + car->args[i].value % IDX_MOD);
			}
			i++;
		}
	}
	return TRUE;
}