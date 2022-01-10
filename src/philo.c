/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/10 20:00:30 by ddiakova         ###   ########.fr       */
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

void	*routine(void *param)
{
	t_philo *ph;

	ph = (t_philo *)param;
	
	check_state();
	taking_forks(ph);
	pthread_mutex_lock(ph->mutex_print);
	write (1, "Start thinking\n", 16);
	sleep(1);
	write (1, "End thinking\n", 14);
	pthread_mutex_unlock(ph->mutex_print);
	return (NULL);
}

size_t	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));	
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	pthread_mutex_t	mutex;
	t_philo			*philo;
	t_table 		table;
	int				i;
	
	if (argc != 5 && argc != 6)
		return (1);
	
	table.count = ft_atoi(argv[1]);
	table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.count);
	philo = (t_philo *)malloc(sizeof(t_philo) * table.count);
	philo->p_count = table.count;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * table.count);
	if (philo == NULL || thread == NULL)
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
		philo[i].start_time = get_time();
		philo[i].last_meal = philo->start_time;
		i++;
	}
	
	pthread_mutex_init(&mutex, 0);
	
	i = 0;
	while (i < table.count)
	{
		
		pthread_mutex_lock(&mutex);
		printf ("Philo %d has been created\n", i + 1);
		pthread_mutex_unlock(&mutex);
		philo[i].mutex_print = &mutex;
		if (pthread_create(&thread[i], 0, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	

	i = 0;
	while (i < table.count)
	{
		if (pthread_join(thread[i], 0) != 0) 
	 		return (2);
	 	printf ("Philo %d has finished exec\n", i + 1);
		i++;
	}
	
	pthread_mutex_destroy(&mutex);
	return (0);
}