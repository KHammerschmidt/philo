/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:19:07 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/09 20:26:58 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

//int philo?? == 0 child philos were not created
//if different than 0 they were created and have to be freed
void	ft_free_and_exit(t_data *data, int status)
{
	// if (data->philo)		//why can't I free this?
	// {
	// 	free(data->philo);
	// 	data->philo = NULL;
	// }
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	sem_close(data->sem_stuffed);
	sem_close(data->sem_assembly);
	if (status == 1)
		exit(data->exit_status);
	if (status == -1)
		exit(1);
}

int	main(int argc, char *argv[])
{
	t_data 	data;

	data = (t_data){0};
	if (parsing(&data, argc, argv) != 0)
		return (-1);
	if (init(&data) != 0)
		return (-1);
	data.exit_status = philo_simulation_main(&data);
	ft_free_and_exit(&data, 0);
	return (data.exit_status);
}
