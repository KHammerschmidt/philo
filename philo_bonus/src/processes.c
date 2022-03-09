/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:21:23 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/09 23:27:44 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

/* Philosophers are waiting until a  philosophers are assembled.  */
static int	wait_for_assembly(t_philo *philo)
{
	sem_wait(philo->data->sem_assembly);
	philo->data->num_philos_created++;
	if (philo->data->num_philos_created != philo->data->num_philos)
	{
		sem_post(philo->data->sem_assembly);
		ft_usleep(1);
		sem_wait(philo->data->sem_assembly);
	}
	sem_post(philo->data->sem_assembly);
	return (0);
}

int	philo_lifecycle(t_philo *philo)
{
	if (ft_create_reaper_thread(philo) != 0)
		exit (1);
	wait_for_assembly(philo);
	if ((philo->id % 2) == 0 && philo->data->num_philos != 1)
	{
		// ft_think(philo->id, philo->data);
		ft_usleep(philo->data->tte - 1);
	}
	while (1)
	{
		ft_eating_ceremony(philo->id, philo->data);
		ft_sleep(philo->id, philo->data);
		ft_think(philo->id, philo->data);
	}
	exit(0);
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
	{
		data->philo[i].id = i;
		data->philo[i].num_meals = 0;
		data->philo[i].stuffed = 0;
		data->philo[i].last_meal_ts = 0;
		data->philo[i].data = data;
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
		{
			perror("Error: process could not be forked\n");
			ft_free_and_exit(data, -1);
		}
		if (data->philo[i].pid == 0)
			philo_lifecycle(&data->philo[i]);
		i++;
	}
	pid = waitpid(-1, &status, WEXITSTATUS(status));
	while (pid > 0)
	{
		if (status == 256)			//multiplies it by 8, actually returns 1?
			kill(0, SIGINT);		// kill(0, SIGKILL);
		pid = waitpid(-1, &status, WEXITSTATUS(status));
	}
	data->exit_status = WEXITSTATUS(status);
	return (data->exit_status);

	//my function from minishell and pipex bonus part :) 
	// i = 0;
	// int save = 0;
	// while (i != -1)
	// {
	// 	i = waitpid(0, &save, pid);
	// 	if (i == pid)
	// 		data->exit_status = save;
	// }
}



	// philo->sem_forks = sem_open(SEM_FORKS, 0);
	// philo->sem_print = sem_open(SEM_PRINT, 0);
	// philo->sem_stuffed = sem_open(SEM_STUFFED, 0);
	// philo->sem_assembly = sem_open(SEM_ASSEMBLY, 0);
	// if (philo->sem_forks == SEM_FAILED || philo->sem_print == SEM_FAILED
	// 	|| philo->sem_stuffed == SEM_FAILED || philo->sem_assembly == SEM_FAILED)
	// {
	// 	printf("Error: semaphore child process.\n");
	// 	return (1);
	// 	// ft_free_and_exit(data, phil???, 1);
	// 	// exit(1);
	// }







	// sem_unlink(SEM_CHECK_MEAL);
	// philo->sem_check_meal = sem_open(SEM_CHECK_MEAL, O_CREAT | O_EXCL, S_IRWXU, 1);
	// if (philo->sem_check_meal == SEM_FAILED)
	// {
	// 	printf("Error: semaphore check_meal child process.\n");
	// 	exit(1); 		//	return (1);
	// }




	// int		i;
	// int		err;
	// int		save;
	// pid_t	pid;

	// i = 0;
	// pid = 0;
	// err = 0;
	// save = 0;
	// while (i < data->num_philos)
	// {
	// 	printf("philo_simualation_main\n");
	// 	err = philo_simulation_processes(data, &pid, i);
	// 	if (err)		//which value needs err to break? why break?
	// 		break ;
	// 	i++;
	// }
	// printf("Before waiting!\n");
	// int	ret = 0;
	// for (int k = 0; k < data->num_philos; k++)
	// {
	// 	ret = wait(NUll);
	// 	if (ret == 0)
	// 		continue;
	// }
		// wait(NULL);

	// while (i != -1)
	// {
	// 	i = waitpid(0, &save, pid);
	// 	if (i == pid)
	// // 		data->exit_status = save;
	// // }
	// return (data->exit_status);
// }



// int philo_simulation_processes(t_data *data, int *pid, int i)
// {
// 	*pid = fork();
// 	if (*pid < 0)
// 	{
// 		perror("Error: process could not be forked\n");
// 		return (data->philo[i].id);
// 		// return (data->philo[i].id);		//why this return value?
// 	}
// 	if (*pid == 0)
// 	{
// 		data->philo[i].pid = *pid;
// 		printf("%d philo_simulation_processes %d %d\n", i + 1, *pid, data->philo[i].pid);
// 		if (philo_child_process(data, &data->philo[i]) != 0)
// 			return (data->philo[i].id);
// 	}
// 	printf("Parent process\n");
// 	return (0);
// }



	//necessary?
	// while (i < philo->data->num_philos)
	// {
	// 	if (philo->data->philo[i].pid == -1)
	// 	{
	// 		//not all processes could be forked, so each process has to terminate
	// 		ft_free_and_exit(philo->data);
	// 		return (1);
	// 	}
	// 	i++;
	// }




	/* Simlutation would end if either one philosopher died or all are stuffed. */
// static int	check_end_of_simulation(t_philo *philo)
// {
// 	sem_wait(philo->data->sem_reaper);
// 	if (philo->data->death_lock == 1)
// 	{ 
// 		sem_post(philo->data->sem_reaper);
// 		// kill(philo->id, SIGINT);
// 		exit(1);
// 	} 
// 	sem_post(philo->data->sem_reaper);

// 	// if (philo->data->mte == -1)
// 	// 	return (0);
// 	// sem_wait(philo->data->sem_stuffed);
// 	// if (philo->data->fed_lock == 1)
// 	// {
// 	// 	sem_post(philo->data->sem_stuffed);
// 	// 	return (1) ;
// 	// }
// 	// sem_post(philo->data->sem_stuffed);
// 	return (0);
// }