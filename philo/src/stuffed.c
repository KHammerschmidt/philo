/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuffed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:17:26 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/11 21:44:18 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Checks if a philosopher has already died. */
static int	check_death_lock(t_data *data)
{
	pthread_mutex_lock(&(data->reaper_lock));
	if (data->death_lock == 1)
	{
		pthread_mutex_unlock(&(data->reaper_lock));
		return (1);
	}
	pthread_mutex_unlock(&(data->reaper_lock));
	return (0);
}

/* Thread checks if either a philosopher has already died or if
everyone has eaten enough to stop the simulation. */
void	*stuffed_main(void *varg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)varg;
	while (1)
	{
		if (check_death_lock(data) != 0)
			break ;
		if (data->fed_philos == data->num_philos)
		{
			pthread_mutex_lock(&(data->meal_lock));
			pthread_mutex_lock(&(data->print_status));
			data->fed_lock++;
			printf("%ld All philosophers are full!\n", \
				ft_get_time() - data->starttime);
			pthread_mutex_unlock(&(data->print_status));
			pthread_mutex_unlock(&(data->meal_lock));
			break ;
		}
		i++;
		if (i == data->num_philos)
			i = 0;
	}
	return (NULL);
}

/* Creates thread that checks if all philosophers ate enough. */
int	ft_create_stuffed_thread(t_data *data)
{
	if (pthread_create(&(data->stuffed), NULL, &stuffed_main, data) != 0)
	{
		printf("Error: thread creation\n");
		return (1);
	}
	return (0);
}
