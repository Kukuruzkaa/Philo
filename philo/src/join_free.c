/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:52:05 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/18 21:06:14 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_and_destroy(t_table *table,t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < table->count)
	{
		if (pthread_join(philo[i].thread, 0) != 0) 
	 		return (str_error(THREAD_ERROR));
		pthread_mutex_destroy(&philo[i].m_meal);
		pthread_mutex_destroy(philo[i].forks[0]);
		i++;
	}
	pthread_mutex_destroy(&table->mutex_print);
	free(table->forks);
	free(philo);
	return (0);
}