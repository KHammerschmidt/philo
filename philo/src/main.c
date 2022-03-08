/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:19:07 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/08 12:42:51 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char *argv[])
{
	t_data data;

	data = (t_data){0};
	if (parsing(&data, argc, argv) != 0)
		return (-1);
	if (ft_init(&data) != 0)
		return (-1);
	ft_create_philo_threads(&data);
	ft_create_reaper_thread(&data);
	if (data.mte != -1)
		ft_create_stuffed_thread(&data);
	ft_join_threads(&data);
	return (0);
}
