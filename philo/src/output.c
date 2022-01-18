/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:22:21 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/18 18:30:40 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *s1, char *s2, bool locked)
{
	if (!locked)
		pthread_mutex_lock(philo->mutex_print);
	if (!*philo->dead)
	{
		ft_putnbr_fd(print_time(philo), 1);
		ft_putstr_fd(s1, 1);
		ft_putnbr_fd(philo->p_id, 1);
		ft_putstr_fd(s2, 1);
	}
	if (!locked)
		pthread_mutex_unlock(philo->mutex_print);
}