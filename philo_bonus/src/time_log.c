/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:17:13 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/16 14:52:43 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

/* Adapted usleep function with more precision.  */
void	ft_usleep(useconds_t ms)
{
	long	time;

	time = ft_get_time();
	while (ft_get_time() < (time + ms))
		usleep(500);
}

/* Gets the current time in milliseconds. */
long	ft_get_time(void)
{
	long			current_time;
	int				err_msg;
	struct timeval	time;

	err_msg = 0;
	current_time = 0;
	err_msg = gettimeofday(&time, NULL);
	if (err_msg != 0)
	{
		printf("Error: current time could not be determined\n");
		return (-1);
	}
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

static void	print_eating(unsigned long timestamp, int id, t_data *data)
{
	printf("%lu %d is eating\n", timestamp, id + 1);
	sem_wait(data->sem_reaper);
	data->philo[id].last_meal_ts = ft_get_time() - data->starttime;
	data->philo[id].num_meals++;
	if (data->philo[id].num_meals == data->mte)
	{
		printf("%lu %d has eaten enough\n",
			ft_get_time() - data->starttime, id + 1);
		sem_post(data->sem_forks);
		sem_post(data->sem_forks);
		sem_post(data->sem_print);
		sem_post(data->sem_reaper);
		exit(3);
	}
	sem_post(data->sem_reaper);
}

/* Prints the respective status of a philosophers, protecting each status
with a print_status mutex. Nothing is printed if one philosopher has died. */
void	ft_print_log(int id, int status, t_data *data)
{
	unsigned long	timestamp;

	timestamp = 0;
	sem_wait(data->sem_print);
	timestamp = ft_get_time() - data->starttime;
	if (status == 1)
		printf("%lu %d has taken a fork\n", timestamp, id + 1);
	if (status == 2)
		print_eating(timestamp, id, data);
	if (status == 3)
		printf("%lu %d is sleeping\n", timestamp, id + 1);
	if (status == 4)
		printf("%lu %d is thinking\n", timestamp, id + 1);
	sem_post(data->sem_print);
}
