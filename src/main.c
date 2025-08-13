/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:06:25 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/18 23:36:24 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	log_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->sys->death_chk);
	pthread_mutex_lock(&philo->sys->print);
	if (philo->sys->dead_flag)
	{
		pthread_mutex_unlock(&philo->sys->print);
		pthread_mutex_unlock(&philo->sys->death_chk);
		return ;
	}
	philo->sys->dead_flag = 1;
	printf("%lu %d died\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->sys->print);
	pthread_mutex_unlock(&philo->sys->death_chk);
}

long int	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	end_sim(t_sys *sys, int full_philos)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&sys->death_chk);
	if (full_philos == sys->n_philo || sys->dead_flag)		
		stop = 1;
	pthread_mutex_unlock(&sys->death_chk);
	return (stop);
}

static int	handle_single_philo(t_sys *sys)
{
	print_log(&sys->philos[0], "has taken a fork");
	usleep(sys->t_death * 1000);
	print_log(&sys->philos[0], "died");
	cleanup(sys);
	return (0);
}

static void	supervisor(t_sys *sys)
{
	int	full_philos;
	int	i;

	while (1)
	{
		full_philos = 0;
		i = -1;
		while (++i < sys->n_philo)
		{
			pthread_mutex_lock(&sys->philos[i].data);
			if (get_time() - sys->philos[i].last_meal_ts > 
				(unsigned long)sys->t_death)
				log_death(&sys->philos[i]);
			if (sys->philos[i].meal_cnt == sys->n_meals)
				full_philos++;
			pthread_mutex_unlock(&sys->philos[i].data);
		}
		if (end_sim(sys, full_philos))
			break ;
	}
}

static int	start_sim(t_sys *sys)
{
	pthread_t	*tid;
	int			i;

	tid = (pthread_t *)malloc(sizeof(pthread_t) * sys->n_philo);
	i = -1;
	while (++i < sys->n_philo)
	{
		if (pthread_create(&tid[i], NULL, philosopher_routine, &sys->philos[i]))
			return (1);
	}
	supervisor(sys);
	i = -1;
	while (++i < sys->n_philo)
		pthread_join(tid[i], NULL);
	free(tid);
	cleanup(sys);
	return (0);
}

int	main(int argc, char **argv)
{
	t_sys	*sys;

	if (init_sys(&sys, argc, argv))
		return (ft_putstr_fd("Initialization failure.\n", 2), 1);
	if (sys->n_philo == 1)
		return (handle_single_philo(sys));
	else
		return (start_sim(sys));
	return (0);
}
