/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:07:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/03/25 00:36:30 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* includes ***************************************************************** */
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* typedef ****************************************************************** */

struct s_sys;

typedef struct	s_philo
{
	int				id;
	int				meal_cnt;
	uintmax_t		last_meal_ts;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	struct s_sys	*sys;
	pthread_mutex_t	data;
}	t_philo;

typedef struct	s_sys
{
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				dead_flag;
	pthread_mutex_t	death_chk;
	pthread_mutex_t	print;
}	t_sys;

/* ext ********************************************************************** */
unsigned long	ft_strlen(const char *str);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
int				ft_putstr(char *s);
int				ft_putstr_fd(char *s, int fd);

/* cleanup ****************************************************************** */
void			cleanup(t_sys *sys);
void			fail_cleanup(t_sys *sys, int i);

/* init ********************************************************************* */
int				init_sys(t_sys **sys, int argc, char **argv);

/* philo ******************************************************************** */
void			print_log(t_philo *philo, char *str);
void			*philosopher_routine(void *arg);

/* main ********************************************************************* */
long int		get_time(void);

#endif