#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct timeval	t_time;

typedef struct s_data
{
	int					num_of_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					num_times_to_eat;
	sem_t				*death_semaphore;
	sem_t				*print_semaphore;
	sem_t				*meal_semaphore;
	sem_t				*all_eat_sem;
	time_t				start_time;
	pid_t				*pid;
	sem_t				*forks;
}						t_data;

typedef struct s_philo
{
	pthread_t			monitor;
	int					id;
	time_t				last_meal_time;
	int					meals_eaten;
	t_data				*data;
}						t_philo;

int						is_valid_number(char *str);
int						validate_args(int ac, char **av);

t_data					*init_data(char **av);
t_philo					*init_philosopher(t_data *data);

void	print_status(t_philo *philo,
					char *action);
void					take_forks(t_philo *philo);
void					eat_action(t_philo *philo);
void					sleep_action(t_philo *philo);
void					think_action(t_philo *philo);

void					start_simulation(t_philo *philosophers);
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);

int						is_simulation_stopped(t_data *data);
void					stop_simulation(t_data *data);
int						check_philosopher_death(t_philo *philo);
int						all_philosophers_satisfied(t_philo *philosophers);

time_t					get_time_ms(void);
void					precise_sleep(time_t duration);
int						ft_atol(const char *str);
int						ft_isdigit(int c);
void					cleanup(t_philo *philosophers);
void					close_semaphores(t_data *data);
void					unlink_semaphore(void);
void					creat_semaphores(t_data *data);
int						is_active(t_philo *philosopher);

#endif