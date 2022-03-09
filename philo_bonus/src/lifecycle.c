/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:11:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/09 21:43:28 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

/* A single philosopher can only grab his fork and wait to die as he is unable
to eat with only one fork. But he manages to put it back before dying! */
static void	single_philo(t_data *data, int id)
{
	sem_wait(data->sem_forks);
	ft_print_log(id, 1, data);
	ft_usleep(data->ttd);
	sem_post(data->sem_forks);
	sem_wait(data->sem_reaper);
	ft_print_log(id, 5, data);
	sem_post(data->sem_reaper);
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
	sem_wait(data->sem_forks);
	ft_print_log(id, 1, data);
	sem_wait(data->sem_forks);
	ft_print_log(id, 2, data);
	sem_wait(data->sem_reaper);
	data->philo[id].last_meal_ts = ft_get_time() - data->starttime;
	ft_usleep(data->tte);
	data->philo[id].num_meals++;
	if (data->mte != -1 && data->philo[id].num_meals == data->mte)
		data->fed_philos++;
	sem_post(data->sem_reaper);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
	return (0);
}

/* Philosopher sleeps for time-to-sleep duration. */
void	ft_sleep(int id, t_data *data)
{
	ft_print_log(id, 3, data);
	ft_usleep(data->tts);
}

/* Philosopher thinks, no time limit. */
void	ft_think(int id, t_data *data)
{
	ft_print_log(id, 4, data);
}
