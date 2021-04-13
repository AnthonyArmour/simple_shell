void free_pwd(char **env)
{
        int idx = 0;

	while (env[idx])
        {
                if (strncmp(env[idx], "OLDPWD=", 7) == 0)
                        break;
                idx++;
        }
        free(env[idx]);
	idx = 0;
	while (env[idx])
        {
                if(strncmp(env[idx], "PWD=", 4) == 0)
                        break;
                idx++;
        }
	free(env[idx]);
}

/**
 * my_exit - exits on exit cmd
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * Return: int
 */

int my_exit(char **tokes, char *argv, char **env)
{
	(void)argv;
	(void)env;
	if (tokes[1] == NULL)
		exit(0);
	else
		exit(atoi(tokes[1]));
	return (0);
}



void handle_err(char *argv, int err_num, char *token)
{
	char *temp = NULL;
	char *num;
	int error_cnt, x = 0, idx = 0;
	char *not_found = "not found\n";

	err_num = errno;
	error_cnt = err_Cnt;
	num = print_number(error_cnt);
	temp = malloc(_strlen(argv) + 3);
	for (idx = 0; argv[idx]; idx++)
		temp[idx] = argv[idx];
	temp[idx] = ':', idx++;
	temp[idx] = ' ', idx++;
	temp = _realloc(temp, _strlen(temp),
			_strlen(temp) + _strlen(num) + 2);
	for (x = 0; num[x]; x++)
	temp[idx] = num[x], idx++;
	temp[idx] = ':', idx++;
	temp[idx] = ' ', idx++;
	if (err_num == 2 || err_num == 20)
	{
		temp = _realloc(temp, _strlen(temp),
				_strlen(temp) + _strlen(token) + 2);
		for (x = 0; token[x]; x++)
				temp[idx] = token[x], idx++;
		temp[idx] = ':', idx++;
		temp[idx] = ' ', idx++;
		temp = _realloc(temp, _strlen(temp),
				_strlen(temp) + _strlen(not_found) + 1);
		for (x = 0; not_found[x]; x++)
			temp[idx] = not_found[x], idx++;
		temp[idx] = '\0';
		write(STDERR_FILENO, temp, _strlen(temp));
	}
	else
	{
		write(STDERR_FILENO, temp, _strlen(temp));
		perror(token);
	}
	free(temp);
}
