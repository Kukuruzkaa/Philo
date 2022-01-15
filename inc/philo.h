/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:00:02 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/15 21:58:52 by ddiakova         ###   ########.fr       */
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
# include <stdbool.h>

typedef	struct s_philo
{
	int		p_id;
	int		max_meal;
	int		meal;
	size_t	*start_time;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	last_meal;
	bool	*dead;
	pthread_mutex_t 	m_meal;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t *forks[2]; 
	pthread_t thread;
}				t_philo;

typedef struct s_table
{
	int		count;
	size_t	start_time;
	bool	dead;
	t_philo *philo;
	pthread_mutex_t mutex_print;
	pthread_mutex_t *forks; 
}				t_table;

size_t	get_time();
size_t	print_time(t_philo *philo);
long int	ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
bool	is_dead(t_philo *philo);
void	taking_forks(t_philo *philo);
void	puting_down(t_philo *philo);
#endif