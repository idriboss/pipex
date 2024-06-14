#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdbool.h>

#define USAGE "./pipex infile cmd1 cmd2 cmd.. outfile"
#define MALLOC_FAILED "syscall: malloc failed"
#define USAGE_BONUS "./pipex here_doc LIMITER cmd cmd1 file"
#define PIPE_FAILED "syscall: pipe failed"
#define FORK_FAILED "syscall: fork failed"

typedef struct t_data
{
	char	**envp;
	char	**command;
	pid_t	*pid;
	int		fd[2];
	char	*input_file;
	char	*output_file;
	char	*command_path;
	int		previous_pipe;
	char	*limiter;
	int		nb_command;
}	t_data;

void	print_err_and_exit(const char *err, int code);
void	free_and_exit(const char *err, int code, t_data *data, bool fail);
void	redirect(t_data *data, int j);
void	fork_command(t_data *data, char **argv, int i);
char	*command_path(char *command, t_data *data);
void	init_struct(t_data *data, int argc, char **argv, char **envp);


#endif