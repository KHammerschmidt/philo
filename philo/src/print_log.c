/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:26:58 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/08 11:43:27 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* check if all philos are full then nothing is printed */
static int	check_end_of_simulation(t_data *data)
{
	pthread_mutex_lock(&data->reaper_lock);
	if (data->death_lock == 1)
	{
		pthread_mutex_unlock(&data->reaper_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->reaper_lock);
	if (data->mte == -1)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	if (data->fed_lock == 1)
	{
		pthread_mutex_unlock(&data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (0);
}

/* Prints the respective status of a philosophers, protecting each status
with a print_status mutex. Nothing is printed if one philosopher has died. */
void	ft_print_log(int id, int status, t_data *data)
{
	unsigned long timestamp;

	timestamp = 0;
	if (check_end_of_simulation(data) != 0)
		return ;
	pthread_mutex_lock(&data->print_status);
	timestamp = ft_get_time() - data->starttime;
	if (status == 1)
		printf("%lu %d has taken a fork\n", timestamp, id + 1);
	if (status == 2)
		printf("%lu %d is eating\n", timestamp, id + 1);
	if (status == 3)
		printf("%lu %d is sleeping\n", timestamp, id + 1);
	if (status == 4)
		printf("%lu %d is thinking\n", timestamp, id + 1);
	pthread_mutex_unlock(&data->print_status);
}
