/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:59:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/08 12:43:54 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Philosophers are waiting until a  philosophers are assembled.  */
static void	wait_for_assembly(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->assembly_lock));
	philo->data->num_philos_created++;
	pthread_mutex_unlock(&(philo->data->assembly_lock));
	while (philo->data->num_philos_created != philo->data->num_philos)
		ft_usleep(1);
}

/* Simlutation would end if either one philosopher died or all are stuffed. */
static int	check_end_of_simulation(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->reaper_lock));
	if (philo->data->death_lock == 1)
	{ 
		pthread_mutex_unlock(&(philo->data->reaper_lock));
		return (1) ;
	} 
	pthread_mutex_unlock(&(philo->data->reaper_lock));
	if (philo->data->mte == -1)
		return (0);
	pthread_mutex_lock(&(philo->data->meal_lock));
	if (philo->data->fed_lock == 1)
	{
		pthread_mutex_unlock(&(philo->data->meal_lock));
		return (1) ;
	}
	pthread_mutex_unlock(&(philo->data->meal_lock));
	return (0);
}

void	*philo_main(void *varg)
{
	t_philo *philo;

	philo = (t_philo *)varg;
	wait_for_assembly(philo);
	if (philo->id % 2 == 0 && philo->data->num_philos != 1)
	{
		ft_think(philo->id, philo->data);
		if (philo->data->num_philos > 50)			//waiting times!
			ft_usleep(10);
		else if (philo->data->num_philos <= 3)
			ft_usleep(1);
		else if (philo->data->num_philos <= 5)
			ft_usleep(1);
		else if (philo->data->num_philos < 10)
			ft_usleep(3);
		else
			ft_usleep(5);
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
			&philo_main, &(data->philo[i])) != 0)
		{
			printf("Error: thread creation\n");
			return (1);
		}
		i++;
	}
	return (0);
}

