/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:19:07 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/16 16:19:29 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	data = (t_data){0};
	if (parsing(&data, argc, argv) != 0)
		return (-1);
	if (ft_init(&data) != 0)
		return (-1);
	ft_create_philo_threads(&data);
	ft_create_reaper_thread(&data);
	ft_join_threads(&data);
	return (0);
}

/*
TEST CASES

ONE PHILOSOPHER
./philo 1 800 200 200
die after 800 milliseconds

RUN FOREVER CASES
./philo 2 420 200 200
run for ever
./philo 4 410 200 200
run for ever
./philo 5 800 200 200
run for ever
./philo 30 600 200 200
run for ever
./philo 99 620 200 200
run for ever
run for ever
./philo 198 440 200 200
run for ever
./philo 199 620 200 200
run for ever

ONE PHILOSOPHER MUST DIE
./philo 4 310 200 100
1 must die
./philo 3 550 200 200
1 must die
./philo 3 550 200 200
1 must die

ENDING AFTER AMOUNT OF MEALS-TO-EAT
./philo 5 800 200 200 7
end after 7 meals_per_philo
./philo 2 100 10 10 3
end after 2 meals_per_philo
./philo 30 800 200 200 7
end after 7 meals_per_philo
./philo 30 600 200 200 7
end after 7 meals_per_philo

*/