/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/05 21:31:22 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>

void	*routine(void *mutex)
{
	printf("Start thinking\n");
//	printf("after init : %ld\n", mutex->__align);
	pthread_mutex_lock(mutex);
//	printf("lock : %ld\n", mutex->__align);
	sleep(3);
	printf("End thinking\n");
	pthread_mutex_unlock(mutex);
//	printf("unlock : %ld\n", mutex->__align);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_philo			*philo;
	t_table 		table;
	int				i;
	
	if (argc != 4 && argc != 5)
		return (1);
	
	table.p_count = ft_atoi(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * table.p_count);
	if (philo == NULL)
		return (1);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
			philo->meal = ft_atoi(argv[5]);
	
	pthread_mutex_init(&mutex, 0);
	
	i = 1;
	while (i <= table.p_count)
	{
		philo->p_id = i;
		printf ("Philo %d has been created\n", i);
		pthread_create(&thread + i, 0, &routine, &mutex);
		i++;
	}
	
	i = 1;
	while (i <= table.p_count)
	{
		if (pthread_join(thread + i, 0) != 0)
	 		return (2);
	 	printf ("Philo %d has finished exec\n", i);
	}
	
	pthread_mutex_destroy(&mutex);
	return (0);
}