/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:59:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/17 14:22:16 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Simlutation would end if either one philosopher dies or all are stuffed. */
int	check_end_of_simulation(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->reaper_lock));
	if (philo->data->death_lock == 1)
	{
		pthread_mutex_unlock(&(philo->data->reaper_lock));
		return (1);
	}
	if (philo->data->fed_philos == philo->data->num_philos)
	{
		pthread_mutex_unlock(&(philo->data->reaper_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->reaper_lock));
	return (0);
}

/* Philos are waiting until all philosophers are created. Odd numbered philos
are thinking and waiting so their even numbered colleagues can start their
lifecycle of eating, sleeping and thinking. The simulation breaks if either
a philosopher has died or all philosophers have eaten enough. */
void	*philo_lifecycle(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	pthread_mutex_lock(&(philo->data->assembly_lock));
	pthread_mutex_unlock(&(philo->data->assembly_lock));
	if ((philo->id % 2) == 0 && philo->data->num_philos != 1)
	{
		ft_think(philo->id, philo->data);
		ft_usleep(philo->data->tte - 1);
	}
	while (check_end_of_simulation(philo) != 1)
	{
		if (ft_eating_ceremony(philo->id, philo->data) != 0)
			break ;
		ft_sleep(philo->id, philo->data);
		ft_think(philo->id, philo->data);
	}
	return (NULL);
}

/* Creates philosopher threads. */
int	ft_create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->assembly_lock));
	while (i < data->num_philos)
	{
		data->philo[i].data = data;
		if (pthread_create(&(data->philo[i].thread_id), NULL,
				&philo_lifecycle, &(data->philo[i])) != 0)
		{
			printf("Error: thread creation\n");
			return (1);
		}
		i++;
	}
	data->starttime = ft_get_time();
	pthread_mutex_unlock(&(data->assembly_lock));
	return (0);
}
