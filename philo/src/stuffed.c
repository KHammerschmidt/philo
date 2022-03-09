/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuffed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:17:26 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/08 15:17:28 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*stuffed_main(void *varg)
{
	t_data 			*data;
	int				i;

	i = 0;
	data = (t_data *)varg;
	while (1)
	{

		pthread_mutex_lock(&(data->reaper_lock));
		if (data->death_lock == 1)
		{
			pthread_mutex_unlock(&(data->reaper_lock));
			break ;
		}
		pthread_mutex_unlock(&(data->reaper_lock));

		if (data->fed_philos == data->num_philos)
		{
			pthread_mutex_lock(&(data->meal_lock));
			pthread_mutex_lock(&(data->print_status));
			printf("%ld All philosophers are full!\n", ft_get_time() - data->starttime);
			data->fed_lock++;
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

int	ft_create_stuffed_thread(t_data *data)
{
	if (pthread_create(&(data->stuffed), NULL, &stuffed_main, data) != 0)
	{
		printf("Error: thread creation\n");
		return (1);
	}
	return (0);
}
