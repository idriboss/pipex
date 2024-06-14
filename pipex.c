#include "pipex.h"

int		main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc < 5)
		return (1);
	init_struct(&data, argc, argv, envp);
	fork_command(&data, argv, 2 + (data.limiter != NULL));

	free_and_exit("FINISH", EXIT_SUCCESS, &data, false);
}
