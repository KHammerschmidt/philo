/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:11:04 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/15 23:21:03 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

/* A single philosopher can only grab his fork and wait to die as he is unable
to eat with only one fork. But he manages to put it back before dying! */
static void	single_philo(t_data *data, int id)
{
	sem_wait(data->sem_forks);
	ft_print_log(id, 1, data);
	ft_usleep(data->ttd + 2);
	sem_post(data->sem_forks);
	sem_wait(data->sem_reaper);
	ft_print_log(id, 5, data);
	sem_post(data->sem_reaper);
}

static void	fork_handling(t_data *data, int id, int status)
{
	//how to return forks when process is killed
	if (status == GRABBING_FORKS)
	{
		sem_wait(data->sem_forks);
		ft_print_log(id, 1, data);
		sem_wait(data->sem_forks);
	}
	if (status == RETURNING_FORKS)
	{
		sem_post(data->sem_forks);
		sem_post(data->sem_forks);
	}
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
	ft_print_log(id, 2, data);
	ft_usleep(data->tte);
	fork_handling(data, id, RETURNING_FORKS);
	sem_wait(data->sem_reaper);
	if (data->philo[id].num_meals == data->mte)
	{
		printf("%lu %d has eaten enough\n",
			ft_get_time() - data->starttime, id + 1);
		sem_post(data->sem_forks);
		sem_post(data->sem_forks);
		sem_post(data->sem_print);
		sem_post(data->sem_reaper);
		exit(0);
	}
	sem_post(data->sem_reaper);
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

int	philo_lifecycle(t_philo *philo)
{
	if (ft_create_reaper_thread(philo) != 0)
		exit (1);
	//set one starttime for each of them
	// while(ft_get_time() < philo->data->starttime)
	// 	ft_usleep(5);
	if ((philo->id % 2) == 0 && philo->data->num_philos != 1)
	{
		ft_think(philo->id, philo->data);
		ft_usleep(philo->data->tte - 1);
	}
	while (1)
	{
		ft_eating_ceremony(philo->id, philo->data);
		ft_sleep(philo->id, philo->data);
		ft_think(philo->id, philo->data);
	}
	exit(0);
}