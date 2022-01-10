/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:04:48 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/10 19:57:02 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	pthread_mutex_lock(philo->forks[1 % philo->p_count]);
}

void	puting_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[1 % philo->p_count]);
	pthread_mutex_unlock(philo->forks[0]);
}