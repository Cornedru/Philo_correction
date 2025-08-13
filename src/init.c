/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:39:41 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/18 23:07:11 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

static int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (ft_putstr_fd("Too few arguments (min. 4 required).\n", 2), 1);
	if (argc > 6)
		return (ft_putstr_fd("Too many arguments (max. 5).\n", 2), 1);
	i = 0;
	while (argv[++i])
		if (!ft_isnum(argv[i]))
			return (ft_putstr_fd("Invalid arguments.\n", 2), 1);
	return (0);
}

static int	init_forks(t_sys *sys)
{
	int	i;
	int	j;

	sys->forks = malloc(sizeof(pthread_mutex_t) * sys->n_philo);
	if (!sys->forks)
		return (1);
	i = -1;
	while (++i < sys->n_philo)
	{
		if (pthread_mutex_init(&sys->forks[i], NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&sys->forks[j]);
			return (free(sys->forks), 1);
		}
	}
	return (0);
}

static int	init_philos(t_sys *sys)
{
	int	i;

	sys->philos = (t_philo *)malloc(sizeof(t_philo) * sys->n_philo);
	if (!sys->philos)
		return (1);
	i = -1;
	while (++i < sys->n_philo)
	{
		sys->philos[i].id = i + 1;
		sys->philos[i].meal_cnt = 0;
		sys->philos[i].last_meal_ts = get_time();
		sys->philos[i].fork_l = &sys->forks[i];
		sys->philos[i].fork_r = &sys->forks[(i + 1) % sys->n_philo];
		sys->philos[i].sys = sys;
		if (pthread_mutex_init(&sys->philos[i].data, NULL))
			return (fail_cleanup(sys, i), 1);
	}
	return (0);
}

int	init_sys(t_sys **sys, int argc, char **argv)
{
	if (check_arg(argc, argv))
		return (1);
	*sys = (t_sys *)malloc(sizeof(t_sys));
	(*sys)->dead_flag = 0;
	(*sys)->n_philo = ft_atoi(argv[1]);
	(*sys)->t_death = ft_atoi(argv[2]);
	(*sys)->t_eat = ft_atoi(argv[3]);
	(*sys)->t_sleep = ft_atoi(argv[4]);
	(*sys)->n_meals = -1;
	if (argv[5])
		(*sys)->n_meals = ft_atoi(argv[5]);
	(*sys)->forks = NULL;
	(*sys)->philos = NULL;
	if (init_forks(*sys))
		return (free(*sys), 1);
	if (init_philos(*sys))
		return (free((*sys)->forks), free(*sys), 1);
	return (0);
}
