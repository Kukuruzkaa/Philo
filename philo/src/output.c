/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:22:21 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/22 20:25:43 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	print_state(t_philo *philo, char *s1, char *s2, bool locked)
{
	if (!locked)
		pthread_mutex_lock(philo->mutex_print);
	pthread_mutex_lock(philo->mutex_dead);
	if (!*philo->dead)
	{
		pthread_mutex_unlock(philo->mutex_dead);
		printf("philo is dead? %d\n", *philo->dead);
		ft_putnbr_fd(print_time(philo), 1);
		ft_putstr_fd(s1, 1);
		ft_putnbr_fd(philo->p_id, 1);
		ft_putstr_fd(s2, 1);
	}
	else
		pthread_mutex_unlock(philo->mutex_dead);
	if (!locked)
		pthread_mutex_unlock(philo->mutex_print);
}
