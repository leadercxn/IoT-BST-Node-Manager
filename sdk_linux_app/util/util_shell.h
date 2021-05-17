/* Copyright (c) 2018 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef __UTIL_SHELL_H__
#define __UTIL_SHELL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * [util_shell_execute description]
 *
 * @param     cmd       [description]
 * @param     result    [description]
 *
 * @return              [description]
 */
int util_shell_execute(const char *cmd, char *result);
#define shell_execute util_shell_execute

/**
 * [util_shell_execute_with_no_results description]
 *
 * @param     cmd    [description]
 *
 * @return           [description]
 */
int util_shell_execute_with_no_results(const char *cmd);
#define shell_execute_with_no_results util_shell_execute_with_no_results



#ifdef __cplusplus
}
#endif

#endif
