/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:11:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/12 21:38:00 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* A single philosopher can only grab his fork and wait to die as he is unable
to eat with only one fork. But he manages to put it back before dying! */
static void	single_philo(t_data *data, int id)
{
	pthread_mutex_lock(&(data->philo[id].fork));
	ft_print_log(id, 1, data);
	ft_usleep(data->ttd + 3);
	pthread_mutex_unlock(&(data->philo[id].fork));
}

/* Depending on the status, a philosopher either takes his fork and the one
next to him or returns the mentioned forks. */
static void	fork_handling(t_data *data, int id, int status)
{
	if (status == GRABBING_FORKS)
	{
		pthread_mutex_lock(&(data->philo[id].fork));
		ft_print_log(id, 1, data);
		if (id == 0)
			pthread_mutex_lock(&data->philo[data->num_philos - 1].fork);
		else
			pthread_mutex_lock(&data->philo[id - 1].fork);
	}
	else if (status == RETURNING_FORKS)
	{
		pthread_mutex_unlock(&data->philo[id].fork);
		if (id == 0)
			pthread_mutex_unlock(&data->philo[data->num_philos - 1].fork);
		else
			pthread_mutex_unlock(&data->philo[id - 1].fork);
	}
}

/* Philosopher is eating and the number of meals incremented. */
static void	chewing(t_data *data, int id)
{
	ft_print_log(id, 2, data);
	if (check_end_of_simulation(data->philo) != 0)
		return ;
	ft_usleep(data->tte);
}

/* Philosopher enters the eating ceremony of grabbing forks, eating and
returning the forks. */
int	ft_eating_ceremony(int id, t_data *data)
{
	if (data->num_philos == 1)
	{
		single_philo(data, id);
		return (1);
	}
	fork_handling(data, id, GRABBING_FORKS);
	if (check_end_of_simulation(data->philo) != 0)
	{
		fork_handling(data, id, RETURNING_FORKS);
		return (1);
	}
	chewing(data, id);
	fork_handling(data, id, RETURNING_FORKS);
	return (0);
}
