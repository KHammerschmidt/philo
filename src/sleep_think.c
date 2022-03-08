/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:52:16 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/07 23:25:29 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

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
