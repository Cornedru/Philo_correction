/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:42:46 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/18 22:42:58 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup(t_sys *sys)
{
	int	i;

	i = -1;
	while (++i < sys->n_philo)
	{
		pthread_mutex_destroy(&sys->forks[i]);
		pthread_mutex_destroy(&sys->philos[i].data);
	}
	free(sys->philos);
	free(sys->forks);
	free(sys);
}

void	fail_cleanup(t_sys *sys, int i)
{
	int	j;
	
	j = -1;
	while (++j < i)
		pthread_mutex_destroy(&sys->philos[j].data);
	free(sys->philos);
	j = -1;
	while (++j < sys->n_philo)
		pthread_mutex_destroy(&sys->forks[j]);
	free(sys->forks);
}
