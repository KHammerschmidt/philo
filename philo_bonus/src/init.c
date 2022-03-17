/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:36:22 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/16 15:32:04 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

static int	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_REAPER);
	data->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
			0644, data->num_philos);
	data->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	data->sem_reaper = sem_open(SEM_REAPER, O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED
		|| data->sem_reaper == SEM_FAILED)
	{
		printf("Error: assembly\n");
		return (1);
	}
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_REAPER);
	return (0);
}

int	init(t_data *data)
{
	if (init_semaphores(data) != 0)
	{
		perror("Init semaphores failed");
		return (1);
	}
	return (0);
}
