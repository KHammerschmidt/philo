/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:26:58 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/14 22:53:53 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Prints the status log of a philosophers, protecting each status
with a print_status mutex. Nothing is printed if one philosopher has died. */
void	ft_print_log(int id, int status, t_data *data)
{
	unsigned long	timestamp;

	timestamp = 0;
	// pthread_mutex_lock(&data->reaper_lock);
	// pthread_mutex_unlock(&data->reaper_lock);
	if (check_end_of_simulation(data->philo) != 0)
		return ;
	pthread_mutex_lock(&data->print_status);
	timestamp = ft_get_time() - data->starttime;
	// if (check_end_of_simulation(data->philo) != 0)
	// {
	// 	pthread_mutex_unlock(&data->print_status);
	// 	return ;
	// }
	if (status == 1)
		printf("%lu %d has taken a fork\n", timestamp, id + 1);
	if (status == 2)
	{
		printf("%lu %d is eating\n", timestamp, id + 1);
		pthread_mutex_lock(&data->reaper_lock);
		data->philo[id].last_meal_ts = ft_get_time() - data->starttime;
		pthread_mutex_unlock(&data->reaper_lock);
		data->philo[id].num_meals++;
		if (data->mte != -1 && data->philo[id].num_meals == data->mte)
			data->fed_philos++;
	}
	if (status == 3)
		printf("%lu %d is sleeping\n", timestamp, id + 1);
	if (status == 4)
		printf("%lu %d is thinking\n", timestamp, id + 1);
	pthread_mutex_unlock(&data->print_status);
}
