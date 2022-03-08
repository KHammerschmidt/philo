/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:11:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/08 12:41:08 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* A single philosopher can only grab his fork and wait to die as he is unable
to eat with only one fork. But he manages to put it back before dying! */
static void	single_philo(t_data *data, int id)
{
	pthread_mutex_lock(&(data->philo[id].fork));
	ft_print_log(id, 1, data);
	ft_usleep(data->ttd + 5);
	pthread_mutex_unlock(&(data->philo[id].fork));
}

/* Depending on status a philosopher either takes his fork and the one next to
him or returns the mentioned forks. */
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

/* Philosopher is actually eating and he checks if he has eating as many
meals as has been requested. */
static void chewing(t_data *data, int id)
{
	ft_print_log(id, 2, data);
	data->philo[id].last_meal_ts = ft_get_time() - data->starttime;
	ft_usleep(data->tte);
	pthread_mutex_lock(&(data->philo[id].check_lock));
	data->philo[id].num_meals++;
	if (data->mte != -1 && data->philo[id].num_meals == data->mte)
		data->fed_philos++;
	pthread_mutex_unlock(&(data->philo[id].check_lock));
}

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

/* Philosopher enters the eating ceremony of grabbing forks, eating and
returning the forks. */
int	ft_eating_ceremony(int id, t_data *data)
{
	if (data->num_philos == 1)
	{
		single_philo(data, id);
		return (1);
	}
	else
	{
		fork_handling(data, id, GRABBING_FORKS);
		if (check_death_lock(data) != 0)
		{
			fork_handling(data, id, RETURNING_FORKS);
			return (1);
		}
		chewing(data, id);
		fork_handling(data, id, RETURNING_FORKS);
	}
	return (0);
}





/* Locks the philo's fork and the one next to him and prints this status */
// static void	grabbing_forks(t_data *data, int id)
// {
// 	pthread_mutex_lock(&(data->philo[id].fork));
// 	ft_print_log(id, 1, data);
// 	if (id == 0)
// 		pthread_mutex_lock(&data->philo[data->num_philos - 1].fork);
// 	else
// 		pthread_mutex_lock(&data->philo[id - 1].fork);
// }

// /*  Releases the philo's fork and the one next to him after a successful meal */
// static void	returning_forks(t_data *data, int id)
// {
// 	pthread_mutex_unlock(&data->philo[id].fork);
// 	if (id == 0)
// 		pthread_mutex_unlock(&data->philo[data->num_philos - 1].fork);
// 	else
// 		pthread_mutex_unlock(&data->philo[id - 1].fork);
// }