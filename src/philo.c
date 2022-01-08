/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/08 18:28:06 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>

void	*routine(void *param)
{
	t_philo *ph;

	ph = (t_philo *)param;
	
	
//	printf("after init : %ld\n", mutex->__align);
	pthread_mutex_lock(ph->mutex_print);
	write (1, "Start thinking\n", 16);
//	printf("lock : %ld\n", mutex->__align);
	sleep(1);
	write (1, "End thinking\n", 14);
	pthread_mutex_unlock(ph->mutex_print);
//	printf("unlock : %ld\n", mutex->__align);
	return (NULL);
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
	
	table.p_count = ft_atoi(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * table.p_count);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * table.p_count);
	if (philo == NULL || thread == NULL)
		return (1);
	philo[0].time_to_die = ft_atoi(argv[2]);
	philo[0].time_to_eat = ft_atoi(argv[3]);
	philo[0].time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
			philo[0].meal = ft_atoi(argv[5]);
	
	pthread_mutex_init(&mutex, 0);
	
	pthread_mutex_lock(&mutex);
	
	i = 0;
	while (i < table.p_count)
	{
		philo[i].p_id = i + 1;
		printf ("Philo %d has been created\n", i + 1);
		philo[i].mutex_print = &mutex;
		if (pthread_create(&thread[i], 0, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	
	pthread_mutex_unlock(&mutex);
	
	i = 0;
	while (i < table.p_count)
	{
		if (pthread_join(thread[i], 0) != 0) 
	 		return (2);
	 	printf ("Philo %d has finished exec\n", i + 1);
		i++;
	}
	
	pthread_mutex_destroy(&mutex);
	return (0);
}