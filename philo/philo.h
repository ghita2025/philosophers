#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_time;

typedef struct s_data
{
	int					num_of_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					num_times_to_eat;
	int					simulation_stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		simulation_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		print_mutex;
	time_t				start_time;
	t_time				start_times;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	time_t				last_meal_time;
	int					meals_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

typedef struct s_monitor
{
	pthread_t			thread;
	t_philo				*philos;
}						t_monitor;

int						is_valid_number(char *str);
int						validate_args(int ac, char **av);

t_data					*init_data(char **av);
t_philo					*init_philosophers(t_data *data);

void	print_status(t_philo *philo,
					char *action);
void					take_forks(t_philo *philo);
void					eat_action(t_philo *philo);
void					sleep_action(t_philo *philo);
void					think_action(t_philo *philo);

int						start_simulation(t_philo *philosophers);
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);

int						is_simulation_stopped(t_data *data);
void					stop_simulation(t_data *data);
int						check_philosopher_death(t_philo *philo);
int						all_philosophers_satisfied(t_philo *philosophers);

time_t					get_time_ms(void);
void					precise_sleep(time_t duration, t_data *data);
long					ft_atol(const char *str);
int						ft_isdigit(int c);
void					cleanup(t_philo *philosophers);
time_t					get_time(t_time start, t_time end);
#endif

// init structs;
//  lanch my threads
// lanch my monitor
//  free and return
