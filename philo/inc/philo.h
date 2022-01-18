/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:00:02 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/18 18:52:47 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ARG_NB_ERROR "Error: invalid argument number\n"
# define ARG_ERROR "Error: invalid argument\n"
# define THREAD_ERROR "Error: thread failed\n"
# define MALLOC_ERROR "Error: malloc failed\n"
# define PHILO " Philosopher "
# define TAKEN_FORK " has taken a fork\n"
# define EATING " is eating\n"
# define THINKING " is thinking\n"
# define SLEEPING " is sleeping\n"
# define IS_DEAD " is dead\n"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_args
{
	int		nb;
	size_t	t_die;
	size_t	t_eat;
	size_t	t_sleep;
	size_t	nb_meal;
}				t_args;

typedef struct s_philo
{
	int				p_id;
	int				max_meal;
	int				meal;
	bool			*dead;
	size_t			*start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*forks[2];
	pthread_t		thread;
}				t_philo;

typedef struct s_table
{
	int				count;
	bool			dead;
	size_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
}				t_table;

size_t		get_time(void);
void		sleep_u(int given_time);

size_t		print_time(t_philo *philo);
void		print_state(t_philo *philo, char *s1, char *s2, bool locked);

int			ft_strlen(const char *s);
int			ft_isdigit(int c);
int			str_error(char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
long int	ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);

int			check_args(t_args *args, int argc, char **argv);
int			init_table(t_table *table, t_args args);
int			init_forks(t_table *table);
void		set_table(t_table *table, t_philo *philo, t_args args, int argc);
int			philos_at_table(t_table *table, t_philo *philo);
void		*dining(void *param);

bool		is_dead(t_philo *philo);
bool		am_i_dead(t_philo *philo);
void		taking_forks(t_philo *philo);
void		puting_down(t_philo *philo);

int			join_and_destroy(t_table *table, t_philo *philo);
#endif