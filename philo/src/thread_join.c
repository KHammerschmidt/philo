/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:24:55 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/12 21:37:23 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Destroys all mutexes previously initialised in the program. */
static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&(data->philo[i].fork));
		i++;
	}
	pthread_mutex_destroy(&(data->print_status));
	pthread_mutex_destroy(&(data->assembly_lock));
	pthread_mutex_destroy(&(data->reaper_lock));
}

/* Joins all created philosopher threads as well as reaper and stuffed
thread, destroys mutexes and frees memory. */
int	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
		{
			printf("Error: A Thread could not be joined\n");
			return (1);
		}
		i++;
	}
	if (pthread_join(data->reaper, NULL) != 0)
	{
		printf("Error: B Thread could not be joined\n");
		return (1);
	}
	destroy_mutexes(data);
	free(data->philo);
	data->philo = NULL;
	return (0);
}
