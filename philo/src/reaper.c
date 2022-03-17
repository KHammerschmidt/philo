/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:04:26 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/17 16:54:57 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Status change of a dead philo is printed and death_lock set to 1. */
static void	activate_reaper(t_data *data, int i)
{
	data->death_lock++;
	ft_print_log(i, 6, data);
	pthread_mutex_unlock(&(data->reaper_lock));
}

static void	activate_stuffed(t_data *data, int i)
{
	ft_print_log(i, 5, data);
	pthread_mutex_unlock(&(data->reaper_lock));
}

static void	reset_i(int *i)
{
	*i = 0;
	ft_usleep(5);
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
			activate_stuffed(data, i);
			break ;
		}
		pthread_mutex_unlock(&(data->reaper_lock));
		i++;
		if (i == data->num_philos)
			reset_i(&i);
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
