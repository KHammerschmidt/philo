/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:04:26 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/15 12:22:50 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Status change of a dead philo is printed and death_lock set to 1. */
static void	activate_reaper(t_data *data, int i)
{
	unsigned long	timestamp;

	timestamp = 0;
	timestamp = ft_get_time() - data->starttime;
	data->death_lock++;
	pthread_mutex_unlock(&(data->reaper_lock));
	pthread_mutex_lock(&(data->print_status));
	printf("%lu %d died\n", timestamp, i + 1);
	pthread_mutex_unlock(&(data->print_status));
}

static void activate_stuffed(t_data *data)
{
	data->fed_lock++;
	pthread_mutex_unlock(&(data->reaper_lock));
	pthread_mutex_lock(&(data->print_status));
	printf("%ld All philosophers are full!\n", \
		ft_get_time() - data->starttime);
	pthread_mutex_unlock(&(data->print_status));
}

/* Checks in a loop if philosophers are already stuffed or if a philo exceeded
ttd with his last meal. */
void	*reaper_main(void *varg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)varg;
	while (1)
	{
		pthread_mutex_lock(&(data->reaper_lock));
		if ((ft_get_time() - data->starttime) - data->philo[i].last_meal_ts
			> data->ttd)
		{
			activate_reaper(data, i);
			break ;
		}
		if (data->num_philos == data->fed_philos)
		{
			activate_stuffed(data);
			break ;
		}
		pthread_mutex_unlock(&(data->reaper_lock));
		i++;
		if (i == data->num_philos)
			i = 0;
	}
	return (NULL);
}

/* Creates thread reaper and calles reaper_main(). */
int	ft_create_reaper_thread(t_data *data)
{
	if (pthread_create(&(data->reaper), NULL, &reaper_main, data) != 0)
	{
		printf("Error: thread creation\n");
		return (1);
	}
	return (0);
}
