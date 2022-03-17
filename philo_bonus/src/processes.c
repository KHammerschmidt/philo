/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:21:23 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/16 14:59:45 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

static void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i;
	philo->num_meals = 0;
	philo->stuffed = 0;
	philo->last_meal_ts = 0;
	philo->data = data;
}

static void	process_loop(t_data *data, int *i)
{
	init_philo(data, &data->philo[*i], *i);
	data->philo[*i].pid = fork();
	if (data->philo[*i].pid < 0)
	{
		perror("Error: process could not be forked\n");
		ft_free_and_exit(data, -1);
	}
	if (data->philo[*i].pid == 0)
		philo_lifecycle(&data->philo[*i]);
	(*i)++;
}

int	philo_simulation_main(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	pid = 1;
	status = 0;
	while (i < data->num_philos)
		process_loop(data, &i);
	pid = waitpid(-1, &status, WEXITSTATUS(status));
	while (pid > 0)
	{
		if (status == 256)
			kill(0, SIGINT);
		pid = waitpid(-1, &status, WEXITSTATUS(status));
	}
	if (status == (3 * 256))
	{
		sem_wait(data->sem_print);
		printf("%ld Everyone ate enough!\n", \
			ft_get_time() - data->starttime + data->tte);
		kill(0, SIGINT);
	}
	data->exit_status = WEXITSTATUS(status);
	return (data->exit_status);
}
