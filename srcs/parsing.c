/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:29:54 by ukim              #+#    #+#             */
/*   Updated: 2021/05/18 14:16:06 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				count_cmd(t_cmd_list *cmd)
{
	int			idx;

	idx = 0;
	while (cmd)
	{
		if (cmd->disable == 0)
			idx++;
		cmd = cmd->next;
	}
	return (idx);
}

int add_cmd_txt(t_split_one **s_cmd, char *str_cmd)
{
	int i;

	i = 0;
	while (str_cmd[i] != '\'' && str_cmd[i])
	{
		s_cmd->str[s_cmd->top++] = str_cmd[i];
		i++;
	}
	return i;
}

t_split_two		*parsing(char *str_ori) //스플릿 원과 투 구조체가 있는데 투로 리턴한다..
{// 파싱 길이 실화냐..
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
	t_env		*tmp_env;
	first_cmd = NULL;
	last_cmd = NULL;
	first_two = NULL;
	temp_redir = NULL; //얘네 초기화안되나?
	//void init_all_s_cmd() one과 two가 어떻게 나뉘어졌는지 알아봐야겠음.. 그리고 둘을 합친 구조체 만들수있는지도.

	last_cmd = (t_split_one*)malloc(sizeof(t_split_one)); //마지막 명령어
	init_s_one(&last_cmd); // 초기화 / s_one 실화냐..
	add_back_one(&first_cmd, last_cmd); //마지막 명령어를 뒤에 넣어준다
	// 여기까지 one 구조체의 연결리스트 초기화(first, last one 구조체의 변수를 포함한)

	cmd = str_ori; //char arr의 명령어 원본

	idx = 0;
	while (cmd[idx]) //명령어 파싱 시작
	{
		if (cmd[idx] == '|') //파이프일때 pipe
		{
			//현재 명령어에 수정
			last_cmd->pipe_flag = 1;

			//명령어 새로 추가
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
			//처음이랑 같음 중복코드
		}
		else if (cmd[idx] == ';') // semicolon
		{
			last_cmd->termi_flag = 1; //왜 termi?

			// 중복코드. 명령어 또 추가함
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);
		}
		else if (cmd[idx] == '\'')//quote 변수로 만들어서 관리하면 좋을듯.
		{
			last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			init_s_one(&last_cmd);
			add_back_one(&first_cmd, last_cmd);

			idx++;
			last_cmd->quote_flag = 1; //왜 전에 만든건 빈채로 내비두고 한개 더만든거에 플래그를 수정?
			idx += add_cmd_txt(&last_cmd, &cmd[idx])

			if (!cmd[idx])// 명령어가 널문자라면? -> ' 하나만 있고 끝인 경우
			{
				printf("invalid\n"); // 종료
				//free()
				break;
			}
			// init_cmd(&last_cmd, &first_cmd)
			// void init_cmd(t_split_one **last_cmd, t_split_one **first_cmd)
			// {
			// 	last_cmd = (t_split_one*)malloc(sizeof(t_split_one));
			// 	init_s_one(last_cmd);
			// 	add_back_one(first_cmd, *last_cmd);
			// }
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
			if (cmd[idx + 1] != 0)
			{
				last_cmd->redir_flag = 1;
				if (cmd[idx] == '>' && cmd[idx + 1] == '>')
				{
					last_cmd->str[last_cmd->top++] = ' ';
					last_cmd->str[last_cmd->top++] = cmd[idx];
					last_cmd->str[last_cmd->top++] = cmd[idx++];
				}
				else if (cmd[idx + 1] == '>' || cmd[idx + 1] == '<')
				{
					if (cmd[idx] == cmd[idx + 1])
					{
						syntax_error();
						return NULL;
					}
				}
				else
				{
					last_cmd->str[last_cmd->top++] = ' ';
					last_cmd->str[last_cmd->top++] = cmd[idx];
				}
			}
			else
			{
				last_cmd->redir_flag = 1;
				last_cmd->str[last_cmd->top++] = ' ';
				last_cmd->str[last_cmd->top++] = cmd[idx];
			}
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
		last_cmd = last_cmd->next;
	}
	//0421
	last_cmd = first_cmd;
	while (last_cmd)
	{
		if (last_cmd->d_quote_flag)
		{
			idx = 0;
			tidx = 0;
			cnv_d_quoat = (char*)malloc(sizeof(char) * BUFFS);
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
						while (last_cmd->str[idx] != '\0' && last_cmd->str[idx] != ' ' &&\
								last_cmd->str[idx] != '$')
						{
							idx++;
						}
						end = idx;
						temp_env_key = ft_substr(last_cmd->str, start, end - start);
						tmp_env = g_all.env_first;
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
	char *temp_str;
	char *front_str;
	char *final_str;
	int sidx = 0;
	int iidx = 0;
	while (last_cmd)
	{
		if (last_cmd->d_quote_flag == 0 && last_cmd->quote_flag == 0)
		{
			last_cmd->split_str = ft_split(last_cmd->str, ' ');
		}
		if (last_cmd->split_str != NULL)
		{
			idx = 0;
			while (last_cmd->split_str[idx])
			{
				tidx = 0;
				iidx = 0;
				cnv_d_quoat = (char*)malloc(sizeof(char) * BUFFS);
				while (last_cmd->split_str[idx][iidx])
				{
					if (last_cmd->split_str[idx][iidx] == '$') //$$ $? 나중에 처리해줘야 할지도...
					{
						temp_env_key = NULL;
						if (last_cmd->split_str[idx][iidx + 1] == ' ' || last_cmd->split_str[idx][iidx + 1] == '\0')
						{
							cnv_d_quoat[tidx++] = last_cmd->split_str[idx][iidx];
							iidx++;
							continue ;
						}
						else if (last_cmd->split_str[idx][iidx + 1] == '?' || last_cmd->split_str[idx][iidx + 1] == '$')
						{

						}
						else
						{
							iidx++;
							start = iidx;
							while (last_cmd->split_str[idx][iidx] != '\0' && last_cmd->split_str[idx][iidx] != ' ' && \
									last_cmd->split_str[idx][iidx] != '$')
							{
								iidx++;
							}
							end = iidx;
							temp_env_key = ft_substr(last_cmd->split_str[idx], start, end - start);
							tmp_env = g_all.env_first;
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
							//환경 변수가 없을 때는 그냥 비워 버려
							continue ;
						}
						if (temp_env_key != NULL)
						{
							free(temp_env_key);
							temp_env_key = NULL;
						}
					}
					cnv_d_quoat[tidx++] = last_cmd->split_str[idx][iidx];
					iidx++;
				}
				cnv_d_quoat[tidx] = '\0';
				free(last_cmd->split_str[idx]);
				last_cmd->split_str[idx] = NULL;
				last_cmd->split_str[idx] = cnv_d_quoat;
				idx++;
			}
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
					if (tmp_cmd->str[2]) //>>text>> <<의 경우 추가로 해결 해줘야함...
					{
						tmp_cmd->disable = 1;
						temp_redir->d_out_flag = 1;
						temp_redir->str = ft_substr(tmp_cmd->str, 2, ft_strlen(tmp_cmd->str) - 2);
					}
					else // >> 만 있는 경우
					{
						if (tmp_cmd->next == NULL)
						{
							syntax_error();
							break;
						}
						tmp_cmd->disable = 1;
						temp_redir->d_out_flag = 1;
						tmp_cmd = tmp_cmd->next;
						if (ft_strncmp(tmp_cmd->str, "<", 1) == 0 || ft_strncmp(tmp_cmd->str, ">", 1) == 0)
						{
							syntax_error();
							return NULL;
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
							syntax_error();
							return NULL;
						}
						tmp_cmd->disable = 1;
						temp_redir->out_flag = 1;
						tmp_cmd = tmp_cmd->next;
						if (ft_strncmp(tmp_cmd->str, "<", 1) == 0 || ft_strncmp(tmp_cmd->str, ">", 1) == 0)
						{
							syntax_error();
							return NULL;
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
							syntax_error();
							return NULL;
						}
						tmp_cmd->disable = 1;
						temp_redir->in_flag = 1;
						tmp_cmd = tmp_cmd->next;
						if (ft_strncmp(tmp_cmd->str, "<", 1) == 0 || ft_strncmp(tmp_cmd->str, ">", 1) == 0)
						{
							syntax_error();
							return NULL;
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
	free_one(&first_cmd);
	int cmd_cnt;
	idx = 0;
	last_two = first_two;
	while (last_two)
	{
		tmp_cmd = last_two->cmd_first;
		cmd_cnt = count_cmd(tmp_cmd);
		last_two->cmd = (char**)malloc(sizeof(char*) * (cmd_cnt + 1));
		last_two->cmd[cmd_cnt] = NULL;
		cmd_cnt = 0;
		idx = 0;
		while (tmp_cmd)
		{
			if (tmp_cmd->disable == 0)
			{
				last_two->cmd[idx] = ft_strdup(tmp_cmd->str);
				idx++;
			}
			tmp_cmd = tmp_cmd->next;
		}
		last_two = last_two->next;
	}

	t_redir *new_redir = NULL;
	last_two = first_two;
	while (last_two)
	{
		if (last_two->redir_flag == 1)
		{
			temp_redir = last_two->redir_first;
			while (temp_redir)
			{
				if (temp_redir->in_flag == 1)
				{
					new_redir = (t_redir*)malloc(sizeof(t_redir));
					init_redir_list(&new_redir);
					new_redir->in_flag = 1;
					new_redir->str = temp_redir->str;
					temp_redir->str = NULL;
					add_back_redir(&last_two->redir_in, new_redir);
				}
				else if(temp_redir->out_flag == 1 || temp_redir->d_out_flag == 1)
				{
					new_redir = (t_redir*)malloc(sizeof(t_redir));
					init_redir_list(&new_redir);
					if (temp_redir->out_flag == 1)
						new_redir->out_flag = 1;
					else
						new_redir->d_out_flag = 1;
					new_redir->str = temp_redir->str;
					temp_redir->str = NULL;
					add_back_redir(&last_two->redir_out, new_redir);
				}
				temp_redir = temp_redir->next;
			}
		}
		last_two = last_two->next;
	}
	//int xxx;
	//char **popo;
	//printf("\n");
	//last_two = first_two;
	//while (last_two)
	//{
	//	popo = last_two->cmd;
	//	xxx = 0;
	//	while (popo[xxx])
	//	{
	//		printf("%s ", popo[xxx]);
	//		xxx++;
	//	}

	//	temp_redir = last_two->redir_first;
	//	printf(" redir : ");
	//	while (temp_redir)
	//	{
	//		if (temp_redir->in_flag)
	//			printf(" < ");
	//		if (temp_redir->out_flag)
	//			printf(" > ");
	//		if (temp_redir->d_out_flag)
	//			printf(" >> ");
	//		printf("%s", temp_redir->str);
	//		temp_redir = temp_redir->next;
	//	}
	//	printf("\n");
	//	last_two = last_two->next;
	//}
	return (first_two);
}
