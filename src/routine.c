/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:04:48 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/13 01:28:57 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo) // en dehors de routine
{
	size_t	time_now;

	time_now = get_time();
	// lock
	if (time_now - philo->last_meal > philo->time_to_die)
	{
		//unlock
		pthread_mutex_lock(philo->mutex_print);
		*philo->dead = true;
		pthread_mutex_unlock(philo->mutex_print);
		return (true);
	}
	//unlock
	return (false);
}

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	pthread_mutex_lock(philo->forks[1]);
}

void	puting_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
}