#ifndef MAIN_H
#define MAIN_H

#include "structs.h"

extern char *__progname;

#define PROGNAME __progname

/* alias.c */
void print_alias_list(kv_list *list);
void print_alias(char *key, char *value);

/* builtins.c */
void alias(char **args, data *datash);
void env(char **args, data *datash);
void exit_shell(char **args, data *datash);
void (*get_builtin(char *name)) (char **args, data *datash);

/* builtins2.c */
void cd(char **args, data *datash);
void _setenv(char **args, data *datash);
void _unsetenv(char **args, data *datash);

/* errors.c */
void print_cd_error(char *dirname, data *datash);
void print_cmd_not_found(char *cmd, data *datash);
void print_err_from_builtin(char *funcname, char *err_msg, data *datash);

/* exec.c */
void exec(data *datash);
void _exec(char **args, data *datash);
void exec_from_file(char **args, data *datash);

/* helpers.c */
int sizeofarr(char **arr);
char **pop_array(char **arr);
int size_of_kv_list(kv_list *list);

/* init.c */
void init_data(data *datash, char **argv, char **env);
void init_env_list(data *datash, char **env);
void init_command_list(data *datash, char **args);

/* io.c */
int _print(char *s, int fd);

/* kv_list.c */
char *add_var(kv_list **list, char *key, char *value);
char *get_var(char *key, kv_list *list);
char **kv_list_to_array(kv_list *list);
void print_kv_list(kv_list *list);
int remove_kv_list_node(kv_list **list, char *key);

/* mainloop.c */
void mainloop(data *datash);

/* mem.c */
void free_array(char **mem);
void free_data(data *datash);
void free_kv_list(kv_list *list);
void free_command_list(commands *commands_list);
void *_calloc(unsigned int nmemb, unsigned int size);

/* parser.c */
char **tokenize(char *s, char *delimiter);
int count_tokens(char *s, char *delimiter);
int locate_comment(char **args);
char **remove_comment(char **args);
void substitute_args(char **args, data *datash);

/* path.c */
int is_executable_file(char *path);
int is_dir(char *path);
char *get_fullpathname(char *fname, data *datash);

/* strings.c */
int _atoi(char *s);
char *_strdup(char *str);
int _strlen(char *s);
char *str_concat(char *s1, char *s2);
int _strcmp(char *s1, char *s2);

/* strings2.h */
char *_strchr(char *s, char c);
char *_itoa(int n);
int count_chars(int n);

#endif
