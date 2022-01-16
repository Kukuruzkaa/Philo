/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:04:48 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/16 14:04:11 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo) // en dehors de routine
{
	size_t	time_now;

	time_now = get_time();
	pthread_mutex_lock(&philo->m_meal);
	if (time_now - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->m_meal);
		pthread_mutex_lock(philo->mutex_print);
		*philo->dead = true;
		// ft_putnbr_fd(print_time(philo), 1);
		// ft_putstr_fd(" Philosopher ", 1);
		// ft_putnbr_fd(philo->p_id, 1);
		// ft_putstr_fd(" is dead\n", 1);
		pthread_mutex_unlock(philo->mutex_print);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_meal);
	return (false);
}

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	pthread_mutex_lock(philo->mutex_print);
	ft_putnbr_fd(print_time(philo), 1);
	ft_putstr_fd(" Philosopher ", 1);
	ft_putnbr_fd(philo->p_id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(philo->mutex_print);
	
	pthread_mutex_lock(philo->forks[1]);
	pthread_mutex_lock(philo->mutex_print);
	ft_putnbr_fd(print_time(philo), 1);
	ft_putstr_fd(" Philosopher ", 1);
	ft_putnbr_fd(philo->p_id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(philo->mutex_print);	
}

void	puting_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_lock(philo->mutex_print);
	ft_putnbr_fd(print_time(philo), 1);
	ft_putstr_fd(" Philosopher ", 1);
	ft_putnbr_fd(philo->p_id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(philo->mutex_print);
}