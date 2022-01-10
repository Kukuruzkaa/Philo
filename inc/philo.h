/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:00:02 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/10 19:57:09 by ddiakova         ###   ########.fr       */
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
# include <sys/time.h>

typedef struct		s_forks
{
	pthread_mutex_t lock;
}					t_forks;

typedef	struct s_philo
{
	int		p_id;
	int		p_count;
	int		meal;
	size_t	start_time;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	last_meal;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t *forks[2]; // pointe sur les 2 forks/*
	
	
}				t_philo;

typedef struct s_table
{
	int		count;
	pthread_mutex_t mutex_print;
	pthread_mutex_t *forks; // malloc mes forks = nb_philo
}				t_table;


long int	ft_atoi(const char *str);
void	taking_forks(t_philo *philo);
void	puting_down(t_philo *philo);
#endif