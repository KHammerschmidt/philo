/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:36:22 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/15 23:16:08 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

static int	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_REAPER);
	data->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
		S_IRWXU, data->num_philos);
	data->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, S_IRWXU, 1);
	data->sem_reaper = sem_open(SEM_REAPER, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED
		|| data->sem_reaper == SEM_FAILED)
		{
			printf("Error: assembly\n"); 		// perror("Error: sem_open");
			return (1);
		}
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_REAPER);

	return (0);
}

/* Initialises variables in t_philo. */
// static void	init_philo_struct(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->num_philos_created)
// 	{
// 		data->philo[i].id = i;
// 		data->philo[i].pid = 0;
// 		data->philo[i].num_meals = 0;
// 		data->philo[i].stuffed = 0;
// 		data->philo[i].last_meal_ts = 0;
// 		data->philo[i].data = data;
// 		//is data already ready to be assigned?
// 		i++;
// 	}
// }

int	init(t_data *data)
{
	// init_philo_struct(data);
	if (init_semaphores(data) != 0)
	{
		perror("Init semaphores failed");
		return (1);
	}
	return (0);
}