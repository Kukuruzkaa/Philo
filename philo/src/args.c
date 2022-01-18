/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:54:43 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/18 18:44:19 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args_type(char *str)
{
	int	i;
	
	if (str[0] == '\0')
		return (1);
	if (str[0] == '-')
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	init_args(int argc, char **argv, t_args *args)
{
	args->nb = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_meal = ft_atoi(argv[5]);
}

int	min_and_max_int(long int nb)
{
	if (nb > INT_MAX || nb < INT_MIN)
		return (1);
	return (0);
}

int	check_int(t_args *args)
{
	if (min_and_max_int(args->nb))
		return (str_error(ARG_ERROR));
	if (min_and_max_int(args->t_eat))
		return (str_error(ARG_ERROR));
	if (min_and_max_int(args->t_sleep))
		return (str_error(ARG_ERROR));
	if (min_and_max_int(args->t_die))
		return (str_error(ARG_ERROR));
	if (args->nb_meal)
	{
		if (min_and_max_int(args->nb_meal))
			return (str_error(ARG_ERROR));
	}	
	return (0);
}

int		check_args(t_args *args, int argc, char **argv)
{
	int	i;

	ft_memset(args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6)
		return (str_error(ARG_NB_ERROR));
	i = 1;
	while (i < argc)
	{
		if (check_args_type(argv[i]))
			return (str_error(ARG_ERROR));
		i++;
	}
	init_args(argc, argv, args);
	if (check_int(args) != 0)
		return (1);
	return (0);
}