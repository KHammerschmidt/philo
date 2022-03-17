/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:19:07 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/17 16:57:34 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	ft_free_and_exit(t_data *data, int status)
{
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	if (status == 1)
		exit(data->exit_status);
	if (status == -1)
		exit(1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data = (t_data){0};
	if (parsing(&data, argc, argv) != 0)
		return (-1);
	if (init(&data) != 0)
		return (-1);
	data.exit_status = philo_simulation_main(&data);
	ft_free_and_exit(&data, 0);
	return (data.exit_status);
}

/*
TEST CASES

ONE PHILOSOPHER
./philo_bonus 1 800 200 200
die after 800 milliseconds

RUN FOREVER CASES
./philo_bonus 2 420 200 200
run for ever
./philo_bonus 4 410 200 200
run for ever
./philo_bonus 5 800 200 200
run for ever
./philo_bonus 30 600 200 200
run for ever
./philo_bonus 99 620 200 200
run for ever
./philo_bonus 98 440 200 200
run for ever
./philo_bonus 198 440 200 200
run for ever
./philo_bonus 199 620 200 200
run for ever

ONE PHILOSOPHER MUST DIE
./philo_bonus 4 310 200 100
1 must die
./philo_bonus 3 550 200 200
1 must die
./philo_bonus 3 550 200 200
1 must die

ENDING AFTER AMOUNT OF MEALS-TO-EAT
./philo_bonus 5 800 200 200 7
end after 7 meals_per_philo
./philo_bonus 2 100 10 10 3
end after 2 meals_per_philo
./philo_bonus 30 800 200 200 7
end after 7 meals_per_philo
./philo_bonus 30 600 200 200 7
end after 7 meals_per_philo

*/
