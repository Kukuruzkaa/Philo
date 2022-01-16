/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/16 19:00:59 by ddiakova         ###   ########.fr       */
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

size_t	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));	
}

void	sleep_u(int given_time)
{
	size_t	delay;

	delay = get_time() + given_time;
	while (get_time() < delay)
		usleep(40);	
}

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
		{
			ft_putnbr_fd(print_time(ph), 1);
			ft_putstr_fd(" Philosopher ", 1);
			ft_putnbr_fd(ph->p_id, 1);
			ft_putstr_fd(" is eating\n", 1);
			pthread_mutex_lock(&ph->m_meal);
			ph->last_meal = get_time();
			ph->meal++;
			pthread_mutex_unlock(&ph->m_meal);	
		}
		pthread_mutex_unlock(ph->mutex_print);
		sleep_u(ph->time_to_eat);
		puting_down(ph);
		sleep_u(ph->time_to_sleep);
		pthread_mutex_lock(ph->mutex_print);
		ft_putnbr_fd(print_time(ph), 1);
		ft_putstr_fd(" Philosopher ", 1);
		ft_putnbr_fd(ph->p_id, 1);
		ft_putstr_fd(" is thinking\n", 1);
		pthread_mutex_unlock(ph->mutex_print);
	}
	return (NULL);
}


size_t	print_time(t_philo *philo)
{
	size_t time;
	size_t time_to_print;

	time = get_time();
	return (time_to_print = time - *philo->start_time);
}


int	fork_id(int forks, int i)
{
	if (i >= forks)
		return (i - forks);
	return (i);
}


int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_table 		table;
	int				i;
	
	if (check_args(argc,argv) != 0)
		return (1);
	i = 0;
	table.dead = false;
	table.count = ft_atoi(argv[1]);
	table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.count);
	table.start_time = get_time();
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
			philo[i].max_meal = ft_atoi(argv[5]);
		philo[i].forks[i % 2] = &table.forks[fork_id(table.count, i)];
		philo[i].forks[(i + 1) % 2] = &table.forks[fork_id(table.count, i + 1)];	
		philo[i].dead = &table.dead;
		philo[i].start_time = &table.start_time;
		philo[i].meal = 0;
		pthread_mutex_init(&philo[i].m_meal, 0);
		i++;
	}
	
	pthread_mutex_init(&table.mutex_print, 0);
	
	i = 0;
	while (i < table.count)
	{
		philo[i].mutex_print = &table.mutex_print;
		philo[i].last_meal = table.start_time;
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