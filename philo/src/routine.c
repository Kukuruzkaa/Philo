/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:04:48 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/20 15:14:14 by ddiakova         ###   ########.fr       */
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
		pthread_mutex_lock(ph->mutex_print);
		if (ph->dead)
		{
			print_state(ph, PHILO, EATING, true);
			pthread_mutex_lock(&ph->m_meal);
			ph->last_meal = get_time();
			ph->meal++;
			pthread_mutex_unlock(&ph->m_meal);
		}
		pthread_mutex_unlock(ph->mutex_print);
		sleep_u(ph->time_to_eat);
		putting_down(ph);
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
		*philo->dead = true;
		pthread_mutex_unlock(philo->mutex_print);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_meal);
	return (false);
}

bool	alive(t_philo *philo)
{
	bool	value;

	pthread_mutex_lock(philo->mutex_print);
	value = !*philo->dead;
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
