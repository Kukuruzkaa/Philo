/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:22:34 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/17 19:49:14 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, char **argv)
{
	table->dead = false;
	table->count = ft_atoi(argv[1]);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->count);
	if (!table->forks)
		return (str_error(MALLOC_ERROR));
	table->start_time = get_time();
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		pthread_mutex_init(&table->forks[i], 0);
		i++;
	}
	return (0);
}

int	fork_id(int forks, int i)
{
	if (i >= forks)
		return (i - forks);
	return (i);
}

void	set_table(t_table *table, t_philo *philo, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		philo[i].p_id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].max_meal = ft_atoi(argv[5]);
		philo[i].forks[i % 2] = &table->forks[fork_id(table->count, i)];
		philo[i].forks[(i + 1) % 2] = &table->forks[fork_id(table->count, i + 1)];	
		philo[i].dead = &table->dead;
		philo[i].start_time = &table->start_time;
		philo[i].meal = 0;
		pthread_mutex_init(&philo[i].m_meal, 0);
		i++;
	}
	pthread_mutex_init(&table->mutex_print, 0);
}

