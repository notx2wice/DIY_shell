#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFS 4000

typedef struct			s_redir
{
	int					out_flag;
	int					in_flag;
	int					d_out_flag;
	char				*str;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_split_one
{
	int					redir_flag;
	int					pipe_flag;
	int					quote_flag;
	int					d_quote_flag;
	int					termi_flag;
	int					top;
	int					disable;
	char				*str;
	char				**split_str;
	struct s_redir		*redir_first;
	struct s_split_one	*next;
}						t_split_one;

typedef struct			s_cmd_list
{
	int					disable;
	char				*str;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct			s_split_two
{
	int					redir_flag;
	int					pipe_flag;
	int					termi_flag;
	t_cmd_list			*cmd_first;
	struct s_redir		*redir_first;
	struct s_split_two	*next;
}						t_split_two;

void					init_s_two(t_split_two **two)
{
	(*two)->cmd_first = NULL;
	(*two)->next = NULL;
	(*two)->pipe_flag = 0;
	(*two)->redir_first = NULL;
	(*two)->redir_flag = 0;
	(*two)->termi_flag = 0;
}

void					add_back_two(t_split_two **first, t_split_two *added)
{
	t_split_two			*t_one;

	t_one = (*first);
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

static	int			count_words(char const *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int			words_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void			*failed(char **splitted, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (NULL);
}

static char			**fill(char const *s, int words, char c, char **splitted)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = words_len(s, c);
		if (!(splitted[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (failed(splitted, i));
		j = 0;
		while (j < len)
			splitted[i][j++] = *(s++);
		splitted[i][j] = '\0';
	}
	splitted[i] = NULL;
	return (splitted);
}

char				**ft_split(char	const *s, char c)
{
	char	**splitted;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!(splitted = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	splitted = fill(s, words, c, splitted);
	return (splitted);
}

void					init_redir_list(t_redir **r_list)
{
	(*r_list)->d_out_flag = 0;
	(*r_list)->in_flag = 0;
	(*r_list)->out_flag = 0;
	(*r_list)->next = NULL;
	(*r_list)->str = NULL;
	(*r_list)->str = (char*)malloc(sizeof(char) * BUFFS);
}

void					init_cmd_list(t_cmd_list **r_list)
{
	(*r_list)->disable = 0;
	(*r_list)->str  = NULL;
	(*r_list)->next = NULL;
}

void					add_back_cmd(t_cmd_list **first, t_cmd_list *added)
{
	t_cmd_list				*t_one;

	t_one = (*first);
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

void					add_back_env(t_env **first, t_env *added)
{
	t_env				*t_one;

	if (added == NULL)
		return ;
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	t_one = (*first);
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

void					add_back_redir(t_redir **first, t_redir *added)
{
	t_redir				*t_one;

	if (added == NULL)
		return ;
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	t_one = (*first);
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

void					init_s_one(t_split_one **one)
{
	(*one)->d_quote_flag = 0;
	(*one)->pipe_flag = 0;
	(*one)->quote_flag = 0;
	(*one)->termi_flag = 0;
	(*one)->disable = 0;
	(*one)->top = 0;
	(*one)->next = NULL;
	(*one)->redir_first = NULL;
	(*one)->str = NULL;
	(*one)->split_str = NULL; // *** 포인터는 초기화가 자동으로 안됨 !!!
	(*one)->str = (char*)malloc(sizeof(char) * BUFFS);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		len;
	int		i;

	len = ft_strlen(s1);
	if (!(s2 = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i += 1;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	s1_letter;
	unsigned char	s2_letter;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && (size_t)i < n)
	{
		i++;
	}
	if ((size_t)i == n)
		return (0);
	s1_letter = (unsigned char)s1[i];
	s2_letter = (unsigned char)s2[i];
	return (s1_letter - s2_letter);
}

t_split_one				*find_last_one(t_split_one *first)
{
	t_split_one			*temp;

	temp = first;
	while (temp->next)
		temp = temp->next;
	return temp;
}

void					add_back_one(t_split_one **first, t_split_one *added)
{
	t_split_one			*t_one;

	t_one = (*first);
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;

	if (!s || ft_strlen(s) < start)
	{
		dest = malloc(sizeof(char));
		*dest = '\0';
		return (dest);
	}
	dest = malloc(len * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (len > 0 && s[start])
	{
		dest[i] = s[start];
		i++;
		start++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*str;

	if (s1 && s2)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		str = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[s1_len] = s2[i];
			s1_len++;
		}
		str[s1_len] = '\0';
		return (str);
	}
	return (NULL);
}

void			free_2d_arr(char ***arr)
{
	int			idx;

	idx = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[idx])
	{
		free((*arr)[idx]);
		idx++;
	}
	free(*arr);
	*arr = NULL;
}
void			get_env(char *env[], t_env **env_first)
{
	int			idx;
	int			e_idx;
	int			len;
	t_env		*tmp_env;

	idx = 0;
	while (env[idx])
	{
		e_idx = 0;
		while (env[idx][e_idx])
		{
			if(env[idx][e_idx] == '=')
				break;
			e_idx++;
		} //env 는 value 있는 것만 출력 되는 것 같은디
		len = ft_strlen(env[idx]);
		if (len == 0)
		{
			idx++;
			continue ;
		}
		tmp_env = (t_env*)malloc(sizeof(t_env));
		tmp_env->key = NULL;
		tmp_env->value = NULL;
		tmp_env->next = NULL; //****************** next도 널로 초기화 해주어야 하는 군!!
		tmp_env->key = ft_substr(env[idx], 0, e_idx);
		if (len - e_idx > 0)
			tmp_env->value = ft_substr(env[idx], e_idx + 1, len - e_idx);
		add_back_env(env_first, tmp_env);
		idx++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	s1_letter;
	unsigned char	s2_letter;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	s1_letter = (unsigned char)s1[i];
	s2_letter = (unsigned char)s2[i];
	return (s1_letter - s2_letter);
}

void			free_env(t_env **env_first)
{
	t_env		*temp;
	t_env		*free_temp;

	if (*env_first == NULL)
		return ;
	temp = *env_first;
	while (temp)
	{
		if (temp->key != NULL)
			free(temp->key);
		if (temp->value != NULL)
			free(temp->value);
		free_temp = temp;
		temp = temp->next;
		free(free_temp);
	}
	*env_first = NULL;
}

void			free_redir(t_redir **redir)
{
	t_redir		*temp_redir;
	t_redir		*free_temp;

	if(*redir == NULL)
		return ;
	
	temp_redir = *redir;
	while (temp_redir)
	{
		if (temp_redir->str != NULL)
			free(temp_redir->str);
		free_temp = temp_redir;
		temp_redir = temp_redir->next;
		free(free_temp);
	}
	*redir = NULL;
}


void			free_one(t_split_one **one)
{
	t_split_one *t_one;
	t_split_one *free_temp;

	if (*one == NULL)
		return ;
	t_one = *one;
	while (t_one)
	{
		if (t_one->redir_first != NULL)
			free_redir(&t_one->redir_first);
		if (t_one->str != NULL)
			free(t_one->str);
		if (t_one->split_str != NULL)
			free_2d_arr(&t_one->split_str);
		free_temp = t_one;
		t_one = t_one->next;
		free(free_temp);
	}
	*one = NULL;
}

void			free_cmd(t_cmd_list **cmd)
{
	t_cmd_list	*t_cmd;
	t_cmd_list	*free_temp;

	if (*cmd == NULL)
		return ;
	t_cmd = *cmd;
	while (t_cmd)
	{
		if (t_cmd->str != NULL)
			free(t_cmd->str);
		free_temp = t_cmd;
		t_cmd = t_cmd->next;
		free(free_temp);
	}
	*cmd = NULL;
}

void			free_two(t_split_two **two)
{
	t_split_two	*t_two;
	t_split_two	*free_temp;

	if (*two == NULL)
		return ;
	t_two = *two;
	while (t_two)
	{
		if (t_two->redir_first != NULL)
			free_redir(&t_two->redir_first);
		if (t_two->cmd_first != NULL)
			free_cmd(&t_two->cmd_first);
		free_temp = t_two;
		t_two = t_two->next;
		free(free_temp);
	}
	*two = NULL;
}

int main(int ac , char **av , char *env[])
{
	int			idx;
	int			tidx;
	char		*cmd;
	char		*cnv_d_quoat;
	char		*temp_env_key;
	char		*temp_env_value;
	int			start;
	int			end;
	t_split_one	*first_cmd;
	t_split_one *last_cmd;
	t_split_two *first_two;
	t_split_two *last_two;
	t_cmd_list	*tmp_cmd;
	t_redir		*temp_redir;
	t_env		*env_first;
	t_env		*tmp_env;
	first_cmd = NULL;
	last_cmd = NULL;
	first_two = NULL;
	temp_redir = NULL;
	env_first = NULL;
	
	last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
	get_env(env, &env_first);
	init_s_one(&last_cmd);
	add_back_one(&first_cmd, last_cmd);
	cmd = "echo 'hi  \"    \"    a' ; echo \"$HOME  $TERM\"  | cat a.txt > hello > cat >d <\"$HOME  \" \"$HOME\" >> fuck |    ls";
	
	idx = 0;
	while (cmd[idx])
	{
		if (cmd[idx] == '|')
		{
			last_cmd->pipe_flag = 1;
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
		}
		else if (cmd[idx] == ';')
		{
			last_cmd->termi_flag = 1;
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
		}
		else if (cmd[idx] == '\'')
		{
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
			idx++;
			last_cmd->quote_flag = 1;
			while (cmd[idx] != '\'' && cmd[idx])
			{
				last_cmd->str[last_cmd->top++] = cmd[idx];
				idx++;
			}
			if (!cmd[idx])
			{
				printf("invalid\n");
				//free()
				break;
			}
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
		}
		else if (cmd[idx] == '\"')
		{
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
			idx++;
			last_cmd->d_quote_flag = 1;
			while (cmd[idx] != '\"' && cmd[idx])
			{
				last_cmd->str[last_cmd->top++] = cmd[idx];
				idx++;
			}
			if (!cmd[idx])
			{
				printf("invalid\n");
				//free()
				break;
			}
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
		}
		else if (cmd[idx] == '<' || cmd[idx] == '>')
		{
			last_cmd->str[last_cmd->top++] = cmd[idx];
			last_cmd->redir_flag = 1;
		}
		else
			last_cmd->str[last_cmd->top++] = cmd[idx];
		idx++;
	}
	last_cmd->termi_flag = 1;

	//print for check and make char arr to string add \0
	last_cmd = first_cmd;
	while (last_cmd)
	{
		last_cmd->str[last_cmd->top] = '\0';
		//printf("%s$\n", last_cmd->str);// 이것만 지우면 됩니다.
		last_cmd = last_cmd->next;
	}
	//0421
	last_cmd = first_cmd;
	while (last_cmd)
	{
		if (last_cmd->d_quote_flag)
		{
			idx = 0;
			cnv_d_quoat = (char*)malloc(sizeof(char) * BUFFS);
			tidx = 0;
			while (last_cmd->str[idx])
			{
				if (last_cmd->str[idx] == '$') //$$ $? 나중에 처리해줘야 할지도...
				{
					temp_env_key = NULL;
					if (last_cmd->str[idx + 1] == ' ' || last_cmd->str[idx + 1] == '\0')
					{
						cnv_d_quoat[tidx++] = last_cmd->str[idx];
						idx++;
						continue ;
					}
					else if (last_cmd->str[idx + 1] == '?' || last_cmd->str[idx + 1] == '$')
					{

					}
					else
					{
						idx++;
						start = idx;
						while (last_cmd->str[idx] != '\0' && last_cmd->str[idx] != ' ')
						{
							idx++;
						}
						end = idx;
						temp_env_key = ft_substr(last_cmd->str, start, end - start);
						tmp_env = env_first;
						while (tmp_env)
						{
							if (ft_strcmp(temp_env_key, tmp_env->key) == 0)
							{
								start = 0;
								while (tmp_env->value[start])
								{
									cnv_d_quoat[tidx++] = tmp_env->value[start];
									start++;
								}
								if (temp_env_key != NULL)
								{
									free(temp_env_key);
									temp_env_key = NULL;
								}
								break;
							}
							tmp_env = tmp_env->next;
						}
						//환경 변수가 없을 때는 그냥 비워 버리넹..
						continue ;
					}
					if (temp_env_key != NULL)
					{
						free(temp_env_key);
						temp_env_key = NULL;
					}
				}
				cnv_d_quoat[tidx++] = last_cmd->str[idx];
				idx++;
			}
			cnv_d_quoat[tidx] = '\0';
			free(last_cmd->str);
			last_cmd->str = NULL;
			last_cmd->str = cnv_d_quoat;
		}
		last_cmd = last_cmd->next;
	}
	// 여기서 따옴표를 전 부 치환 해 버릴 거시다.!!!!!!!!!!!!!!!!!!!
	last_cmd = first_cmd;
	while (last_cmd)
	{
		if (last_cmd->d_quote_flag == 0 && last_cmd->quote_flag == 0)
		{
			last_cmd->split_str = ft_split(last_cmd->str, ' ');
		}
		last_cmd = last_cmd->next;
	}

	last_two = (t_split_two*)malloc(sizeof(t_split_two));
	init_s_two(&last_two);
	add_back_two(&first_two, last_two);
	last_cmd = first_cmd;
	while (last_cmd)
	{
		if (last_cmd->disable)
		{
			last_cmd = last_cmd->next;
			continue ;
		}
		if (last_cmd->quote_flag || last_cmd->d_quote_flag)
		{
			//add_back_cmd , init_cmd 함수를 만들어야함.... 아오 빡쳐
			tmp_cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
			init_cmd_list(&tmp_cmd);
			tmp_cmd->str = ft_strdup(last_cmd->str);
			add_back_cmd(&last_two->cmd_first, tmp_cmd);
		}
		else
		{
			idx = 0;
			while (last_cmd->split_str[idx])
			{
				tmp_cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
				init_cmd_list(&tmp_cmd);
				tmp_cmd->str = ft_strdup(last_cmd->split_str[idx]);
				add_back_cmd(&last_two->cmd_first, tmp_cmd);
				idx++;
			}
		}
		if (last_cmd->redir_flag)
		{
			last_two->redir_flag = 1;
			last_two->redir_first = last_cmd->redir_first;
			last_cmd->redir_first = NULL;
		}
		if (last_cmd->pipe_flag || last_cmd->termi_flag)
		{
			if (last_cmd->pipe_flag)
				last_two->pipe_flag = 1;
			else
				last_two->termi_flag = 1;
			// 새로운 노드를 붙여야 할 상황 
			if (last_cmd->next != NULL)
			{
				//이거는 새로운 노드를 만들 필요 없이 종료해야징
				last_two = (t_split_two*)malloc(sizeof(t_split_two));
				init_s_two(&last_two);
				add_back_two(&first_two, last_two);
			}
		}
		last_cmd = last_cmd->next;
	}
	
	last_two = first_two;
	while (last_two)
	{
		if (last_two->redir_flag)
		{
			tmp_cmd = last_two->cmd_first;
			while (tmp_cmd)
			{
				if (ft_strncmp(tmp_cmd->str, ">>", 2) == 0)
				{
					temp_redir = (t_redir*)malloc(sizeof(t_redir)); 
					init_redir_list(&temp_redir);
					if (tmp_cmd->str[2]) //>>text의 경우
					{
						tmp_cmd->disable = 1;
						temp_redir->d_out_flag = 1;
						temp_redir->str = ft_substr(tmp_cmd->str, 2, ft_strlen(tmp_cmd->str) - 2);
					}
					else // >> 만 있는 경우
					{
						if (tmp_cmd->next == NULL)
						{
							printf("syntex error\n");
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->d_out_flag = 1;
						tmp_cmd = tmp_cmd->next;
						if (ft_strncmp(tmp_cmd->str, "<", 1) == 0 || ft_strncmp(tmp_cmd->str, ">", 1) == 0)
						{
							printf("syntex error\n");
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->str = ft_strdup(tmp_cmd->str);
					}
					add_back_redir(&last_two->redir_first, temp_redir);
				}
				else if (ft_strncmp(tmp_cmd->str, ">", 1) == 0)
				{
					temp_redir = (t_redir*)malloc(sizeof(t_redir));
					init_redir_list(&temp_redir);
					if (tmp_cmd->str[1]) //>>text의 경우
					{
						tmp_cmd->disable = 1; 
						temp_redir->out_flag = 1;
						temp_redir->str = ft_substr(tmp_cmd->str, 1, ft_strlen(tmp_cmd->str) - 1);
					}
					else // >> 만 있는 경우
					{
						if (tmp_cmd->next == NULL)
						{
							printf("syntex error\n");
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->out_flag = 1;
						tmp_cmd = tmp_cmd->next;
						if (ft_strncmp(tmp_cmd->str, "<", 1) == 0 || ft_strncmp(tmp_cmd->str, ">", 1) == 0)
						{
							printf("syntex error\n");
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->str = ft_strdup(tmp_cmd->str);
					}
					add_back_redir(&last_two->redir_first, temp_redir);
				}
				else if (ft_strncmp(tmp_cmd->str, "<", 1) == 0)
				{
					temp_redir = (t_redir*)malloc(sizeof(t_redir));
					init_redir_list(&temp_redir);
					if (tmp_cmd->str[1]) //>>text의 경우
					{
						tmp_cmd->disable = 1;
						temp_redir->in_flag = 1;
						temp_redir->str = ft_substr(tmp_cmd->str, 1, ft_strlen(tmp_cmd->str) - 1);
					}
					else // >> 만 있는 경우
					{
						if (tmp_cmd->next == NULL)
						{
							printf("syntex error\n");
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->in_flag = 1;
						tmp_cmd = tmp_cmd->next;
						if (ft_strncmp(tmp_cmd->str, "<", 1) == 0 || ft_strncmp(tmp_cmd->str, ">", 1) == 0)
						{
							printf("syntex error\n");
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->str = ft_strdup(tmp_cmd->str);
					}
					add_back_redir(&last_two->redir_first, temp_redir);
				}
				tmp_cmd = tmp_cmd->next;
			}
		}
		last_two = last_two->next;
	}

	

	last_two = first_two;
	while (last_two)
	{
		tmp_cmd = last_two->cmd_first;
		while (tmp_cmd)
		{
			if (tmp_cmd->disable == 0)
				printf("%s ", tmp_cmd->str);
			tmp_cmd = tmp_cmd->next;
		}

		temp_redir = last_two->redir_first;
		printf(" redir : ");
		while (temp_redir)
		{
			if (temp_redir->in_flag)
				printf(" < ");
			if (temp_redir->out_flag)
				printf(" > ");
			if (temp_redir->d_out_flag)
				printf(" >> ");
			printf("%s", temp_redir->str);
			temp_redir = temp_redir->next;
		}
		printf("\n");
		last_two = last_two->next;
	}
	free_one(&first_cmd);
	free_two(&first_two);
	free_env(&env_first);
}