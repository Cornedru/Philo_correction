/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:43:47 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/09 03:19:50 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->sys->death_chk);
	pthread_mutex_lock(&philo->sys->print);
	if (!philo->sys->dead_flag)
		printf("%lu %d %s\n", get_time(), philo->id, str);
	pthread_mutex_unlock(&philo->sys->print);
	pthread_mutex_unlock(&philo->sys->death_chk);
}

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->sys->death_chk);
	if (philo->sys->dead_flag)
		return (pthread_mutex_unlock(&philo->sys->death_chk), 1);
	pthread_mutex_unlock(&philo->sys->death_chk);
	return (0);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!is_dead(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork_l;
		second_fork = philo->fork_r;
	}
	else
	{
		first_fork = philo->fork_r;
		second_fork = philo->fork_l;
	}
	pthread_mutex_lock(first_fork);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	pthread_mutex_lock(&philo->data);
	philo->last_meal_ts = get_time();
	philo->meal_cnt++;
	pthread_mutex_unlock(&philo->data);
	usleep(philo->sys->t_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!is_dead(philo))
	{
		eat(philo);
		print_log(philo, "is sleeping");
		usleep(philo->sys->t_sleep * 1000);
		print_log(philo, "is thinking");
	}
	return (NULL);
}
