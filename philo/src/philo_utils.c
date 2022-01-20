/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:59:57 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/20 15:13:18 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

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

size_t	print_time(t_philo *philo)
{
	size_t	time;
	size_t	time_to_print;

	time = get_time();
	return (time_to_print = time - *philo->start_time);
}

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	print_state(philo, PHILO, TAKEN_FORK, false);
	if (philo->forks[0] != philo->forks[1])
	{
		pthread_mutex_lock(philo->forks[1]);
		print_state(philo, PHILO, TAKEN_FORK, false);
	}
	else
		while (alive(philo))
			usleep(100);
}

void	putting_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[1]);
	if (philo->forks[0] != philo->forks[1])
		pthread_mutex_unlock(philo->forks[0]);
	print_state(philo, PHILO, SLEEPING, false);
}
