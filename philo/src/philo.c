/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:02:00 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/18 18:52:59 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	am_i_dead(t_philo *philo)
{
	bool	value;
	pthread_mutex_lock(philo->mutex_print);
	value = *philo->dead;
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

void	*dining(void *param)
{
	t_philo *ph;

	ph = (t_philo *)param;
	
	while (!am_i_dead(ph))
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
		puting_down(ph);
		sleep_u(ph->time_to_sleep);
		print_state(ph, PHILO, THINKING, false);
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_table 		table;
	t_args			args;
	int				i;
	
	if (check_args(&args, argc, argv) != 0)
		return (1);
	ft_memset(&table, 0, sizeof(t_table));
	init_table(&table, args);
	philo = (t_philo *)malloc(sizeof(t_philo) * table.count);
	ft_memset(philo, 0, sizeof(t_philo) * table.count);
	table.philo = philo;
	if (philo == NULL)
		return (str_error(MALLOC_ERROR));
	init_forks(&table);
	set_table(&table, philo, args, argc);
	philos_at_table(&table, philo);

	i = 0;
	while (!someone_is_dead(&table))
	{
		if (is_dead(&philo[i]))
			i++;
		if (i == table.count)
			i = 0;	
	}
	if (someone_is_dead(&table))
		join_and_destroy(&table, philo);
	return (0);
}