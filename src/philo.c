/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/15 12:54:35 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

bool	am_i_dead(t_philo *philo)
{
	bool	value;
	pthread_mutex_lock(philo->mutex_print);
	value = *philo->dead;
	pthread_mutex_unlock(philo->mutex_print);
	return (value);
}

bool	someone_is_dead(t_table *table)
{
	bool	state;
	pthread_mutex_lock(&table->mutex_print);
	state = table->dead;
	pthread_mutex_unlock(&table->mutex_print);
	return (state);
}

void	*routine(void *param)
{
	t_philo *ph;

	ph = (t_philo *)param;
	
	while (!am_i_dead(ph))
	{
		taking_forks(ph);
		pthread_mutex_lock(ph->mutex_print);
		if (ph->dead)
			printf ("Philosopher %d has taken a fork\n", ph->p_id);
		if (ph->dead)
			printf ("Philosopher %d is eating\n", ph->p_id);
		pthread_mutex_unlock(ph->mutex_print);
		usleep(ph->time_to_eat * 1000);
		puting_down(ph);
	}
	return (NULL);
}

size_t	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));	
}

int	fork_id(int forks, int i)
{
	if (forks >= i)
		return (i - forks);
	return (i);
}



int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_table 		table;
	int				i;
	
	if (argc != 5 && argc != 6)
		return (1);
	
	i = 0;
	table.dead = false;
	table.count = ft_atoi(argv[1]);
	table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.count);
	while (i < table.count)
	{
		pthread_mutex_init(&table.forks[i], 0);
		i++;
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * table.count);
	table.philo = philo;
	if (philo == NULL)
		return (1);
	i = 0;
	while (i < table.count)
	{
		philo[i].p_id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].meal = ft_atoi(argv[5]);
		philo[i].forks[i % 2] = &table.forks[fork_id(table.count, i)];
		philo[i].forks[(i + 1) % 2] = &table.forks[fork_id(table.count, i + 1)];	
		philo[i].dead = &table.dead;
		i++;
	}
	
	pthread_mutex_init(&table.mutex_print, 0);
	
	
	i = 0;
	while (i < table.count)
	{
		
		// pthread_mutex_lock(&mutex);
		// printf ("Philo %d has been created\n", i + 1);
		// pthread_mutex_unlock(&mutex);
		philo[i].mutex_print = &table.mutex_print;
		philo[i].start_time = get_time();
		philo[i].last_meal = philo[i].start_time;
		if (pthread_create(&philo[i].thread, 0, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	
	i = 0;
	while (!someone_is_dead(&table))
	{
		is_dead(&philo[i]);
		i++;
		if (i == table.count)
			i = 0;	
	}

	i = 0;
	while (i < table.count)
	{
		if (pthread_join(philo[i].thread, 0) != 0) 
	 		return (2);
	 	printf ("Philo %d has finished\n", i + 1);
		i++;
	}
	
	pthread_mutex_destroy(&table.mutex_print);
	return (0);
}