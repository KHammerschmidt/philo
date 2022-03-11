/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:59:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/11 21:40:31 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Philosophers are waiting until all philosophers are assembled. If all are
created, the starttime is set once. */
static void	wait_for_assembly(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->assembly_lock));
	philo->data->num_philos_created++;
	while (philo->data->num_philos_created != philo->data->num_philos)
	{
		pthread_mutex_unlock(&(philo->data->assembly_lock));
		ft_usleep(1);
		pthread_mutex_lock(&(philo->data->assembly_lock));
	}
	if (philo->data->starttime == 0)
		philo->data->starttime = ft_get_time();
	pthread_mutex_unlock(&(philo->data->assembly_lock));
}

/* Simlutation would end if either one philosopher dies or all are stuffed. */
static int	check_end_of_simulation(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->reaper_lock));
	if (philo->data->death_lock == 1)
	{
		pthread_mutex_unlock(&(philo->data->reaper_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->reaper_lock));
	if (philo->data->mte == -1)
		return (0);
	pthread_mutex_lock(&(philo->data->meal_lock));
	if (philo->data->fed_lock == 1)
	{
		pthread_mutex_unlock(&(philo->data->meal_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->meal_lock));
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
	wait_for_assembly(philo);
	if (philo->id % 2 == 0 && philo->data->num_philos != 1)
	{
		ft_think(philo->id, philo->data);
		ft_usleep(philo->data->tte - 1);
	}
	while (1)
	{
		if (check_end_of_simulation(philo) != 0)
			break ;
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
	return (0);
}
