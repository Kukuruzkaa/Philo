/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:04:48 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/23 19:06:45 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dining(void *param)
{
	t_philo	*ph;

	ph = (t_philo *)param;
	while (alive(ph))
	{
		taking_forks(ph);
		print_state(ph, PHILO, EATING, false);
		pthread_mutex_lock(&ph->m_meal);
		ph->last_meal = get_time();
		ph->meal++;
		pthread_mutex_unlock(&ph->m_meal);
		sleep_u(ph->time_to_eat);
		putting_down(ph);
		print_state(ph, PHILO, SLEEPING, false);
		sleep_u(ph->time_to_sleep);
		print_state(ph, PHILO, THINKING, false);
	}
	return (NULL);
}

bool	is_dead(t_philo *philo)
{
	size_t	time_now;

	time_now = get_time();
	pthread_mutex_lock(&philo->m_meal);
	if (time_now - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->m_meal);
		pthread_mutex_lock(philo->mutex_print);
		print_state(philo, PHILO, IS_DEAD, true);
		pthread_mutex_unlock(philo->mutex_print);
		pthread_mutex_lock(philo->mutex_dead);
		*philo->dead = true;
		pthread_mutex_unlock(philo->mutex_dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_meal);
	return (false);
}

bool	alive(t_philo *philo)
{
	bool	value;

	pthread_mutex_lock(philo->mutex_dead);
	value = !*philo->dead;
	pthread_mutex_unlock(philo->mutex_dead);
	return (value);
}

bool	someone_is_dead(t_table *table)
{
	bool	state;

	pthread_mutex_lock(&table->mutex_dead);
	state = table->dead;
	pthread_mutex_unlock(&table->mutex_dead);
	return (state);
}
