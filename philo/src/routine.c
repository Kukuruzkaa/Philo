/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:04:48 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/18 18:29:36 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_at_table(t_table *table, t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < table->count)
	{
		philo[i].mutex_print = &table->mutex_print;
		philo[i].last_meal = table->start_time;
		if (pthread_create(&philo[i].thread, 0, &dining, &philo[i]) != 0)
			return (str_error(THREAD_ERROR));
		i++;
	}
	return (0);
}


bool	is_dead(t_philo *philo) // en dehors de routine
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
		while (!am_i_dead(philo))
			usleep(100);
}

void	puting_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[1]);
	if (philo->forks[0] != philo->forks[1])
		pthread_mutex_unlock(philo->forks[0]);
	print_state(philo, PHILO, SLEEPING, false);
}