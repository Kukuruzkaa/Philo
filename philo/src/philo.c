/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/22 16:56:40 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	easy_living(t_table *table, t_philo *philo)
{
	int				i;
	int				eat_enough;

	i = 0;
	eat_enough = 0;
	while (!someone_is_dead(table))
	{
		is_dead(&philo[i]);
		pthread_mutex_lock(&philo[i].m_meal);
		if (philo[i].max_meal && philo[i].meal >= philo[i].max_meal)
			eat_enough++;
		if (eat_enough == table->count)
			*philo->dead = true;
		pthread_mutex_unlock(&philo[i].m_meal);
		i++;
		if (i == table->count)
		{
			i = 0;
			eat_enough = 0;
		}
		usleep(400);	
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_table	table;
	t_args	args;

	if (check_args(&args, argc, argv))
		return (1);
	ft_memset(&table, 0, sizeof(t_table));
	init_table(&table, args);
	philo = (t_philo *)malloc(sizeof(t_philo) * table.count);
	ft_memset(philo, 0, sizeof(t_philo) * table.count);
	table.philo = philo;
	if (philo == NULL)
		return (str_error(MALLOC_ERROR));
	init_forks(&table);
	set_table(&table, philo, args, argc);
	philos_at_table(&table, philo);
	easy_living(&table, philo);
	join_and_destroy(&table, philo);
	return (0);
}
