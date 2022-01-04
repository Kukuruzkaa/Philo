/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/04 17:24:34 by ddiakova         ###   ########.fr       */
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
	printf("Test\n");
//	printf("after init : %ld\n", mutex->__align);
	pthread_mutex_lock(mutex);
//	printf("lock : %ld\n", mutex->__align);
	sleep(3);
	printf("Ending thread\n");
	pthread_mutex_unlock(mutex);
//	printf("unlock : %ld\n", mutex->__align);
}

int	main(int argc, char **argv)
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_philo			philo;
	int				i;
	
	if (argc == 4 || argc == 5)
		philo.p_count = ft_atoi(argv[1]);	
	pthread_mutex_init(&mutex, 0);
	i = 1;
	while (i < philo.p_count)
	{
		
	}
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(&thread[i], 0, &routine, &mutex) != 0)
			return (1);
		printf ("Thread %d has started\n", i);
		
	}
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(thread[i], 0) != 0)
			return (2);
		printf ("Thread %d has finished exec\n", i);
	}
	

	pthread_mutex_destroy(&mutex);
	return (0);
}