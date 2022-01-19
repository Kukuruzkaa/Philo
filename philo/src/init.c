/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:22:34 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/19 20:13:04 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, t_args args)
{
	table->dead = false;
	table->count = args.nb;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->count);
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

void	set_table(t_table *table, t_philo *philo, t_args args, int argc)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		philo[i].p_id = i + 1;
		philo[i].time_to_die = args.t_die;
		philo[i].time_to_eat = args.t_eat;
		philo[i].time_to_sleep = args.t_sleep;
		if (argc == 6)
			philo[i].max_meal = args.nb_meal;
		philo[i].forks[i % 2] = &table->forks[fork_id(table->count, i)];
		philo[i].forks[(i + 1) % 2]
			= &table->forks[fork_id(table->count, i + 1)];
		philo[i].dead = &table->dead;
		philo[i].start_time = &table->start_time;
		philo[i].meal = 0;
		pthread_mutex_init(&philo[i].m_meal, 0);
		i++;
	}
	pthread_mutex_init(&table->mutex_print, 0);
}

int	philos_at_table(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		philo[i].mutex_print = &table->mutex_print;
		philo[i].last_meal = table->start_time;
		if (pthread_create(&philo[i].thread, 0, &dining, &philo[i]) != 0)
			return (str_error(THREAD_ERROR));
		i++;
	}
	return (0);
}
