//
// Created by Yevhen Yefimov on 6/1/17.
//

void    get_add_func(char *map, t_car *car, int *pos)
{
    car->data = ft_strsub(map + *pos + 1, 0, 4);
    car->op_type = 1;
    car->c_for_op = 9;
    *pos = (*pos) + 5;
    ft_printf ("-> зчитали інструкцію і її аргументи ADD = %s\n", car->data);
}



void    do_add_func(char *map, t_car *car)
{
    car->op_type = 0;
    ft_printf("ADD OPERATION LAUNCHED!!!!!\n");
}