/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:00:02 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/05 18:47:22 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>


typedef struct		s_forks
{
	pthread_mutex_t lock;
}					t_forks;

typedef	struct s_philo
{
	int		p_id;
	int		meal;
	long	start_time;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	
}				t_philo;

typedef struct s_table
{
	int		p_count;
}				t_table;


long int	ft_atoi(const char *str);
#endif