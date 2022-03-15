/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:32:55 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/15 23:18:16 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

/* Checks if program input fulfils required number of args and data types. */
static int	input_verification(int argc, char *argv[])
{
	int	i;
	int	err_msg;

	i = 1;
	err_msg = 0;
	if ((argc != 5 && argc != 6) || !argv)
		err_msg = 1;
	while (i < argc)
	{
		if (ft_isnum(argv[i]) != 0 || ft_atoi(argv[i]) <= 0)
			err_msg = 1;
		i++;
	}
	if (err_msg == 1)
	{
		printf("Error: Invalid program input\n");
		printf("./program_name [number_of_philosophers] [time_to_die]");
		printf("[time_to_eat] [time_to_sleep]");
		printf("[opt.: number_of_times_each_philosopher_must_eat]\n");
		printf("Specified numbers must be < INT_MAX > 0.\n");
		return (1);
	}
	return (0);
}

/* Checks the program input and parses information to struct t_data. */
int	parsing(t_data *data, int argc, char *argv[])
{
	if (input_verification(argc, argv) != 0)
		return (1);
	data->exit_status = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
		data->mte = ft_atoi(argv[5]);
	else
		data->mte = -1;
	data->philo = ft_calloc(sizeof(t_philo), data->num_philos);
	if (!data->philo)
	{
		printf("Error: memory allocation philo struct\n");
		return (1);
	}
	data->starttime = ft_get_time();
	return (0);
}
