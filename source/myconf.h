/*********************************************************/
/*                                                       */
/* myconf.h                                              */
/* (c)1999-2017 | Juraj Vidéky | videky@breviar.sk       */
/*                                                       */
/* description | interface to config file CONFIG_FILE    */
/*                                                       */
/*********************************************************/

#include "vstudio.h"

#ifndef __MYCONF_H_
#define __MYCONF_H_

#include "mysystem.h"
#include "mysysdef.h"
#include "mydefs.h"
#include "common.h"

#define MAIL_ADDRESS_DEFAULT "videky@breviar.sk"

#define MAX_HTTP_STR	80
#define MAX_MAIL_STR	50
#define MAX_INCD_STR	50
#define MAX_OPTION_LENGTH	40
#define MAX_VALUE_LENGTH	80

#ifdef OS_Windows_Ruby
#define CONFIG_FILE "breviar-local.cfg"
#elif defined(IO_ANDROID)
#define CONFIG_FILE "breviar-android.cfg"
#elif defined(BEHAVIOUR_CMDLINE)
#define CONFIG_FILE "breviar-cmdline.cfg"
#else // defined(BEHAVIOUR_WEB)
#define CONFIG_FILE "breviar-web.cfg"
#endif

#ifdef OS_Windows_Ruby
#define DEFAULT_FONT_FAMILY_SERIF "Cambria, Constantia, Georgia, Liberation, Gentium, Garamond, Serif"
#define DEFAULT_FONT_FAMILY_SANS_SERIF "Candara, Tahoma, Verdana, Helvetica, Sans-Serif"
#else
#define DEFAULT_FONT_FAMILY_SERIF "Serif"
#define DEFAULT_FONT_FAMILY_SANS_SERIF "Sans-Serif"
#endif
#define DEFAULT_FONT_FAMILY_INHERIT "inherit"
#define DEFAULT_FONT_SIZE_INHERIT "inherit"

extern char cfg_INCLUDE_DIR_default [MAX_INCD_STR];

extern long cfg_option_default[POCET_GLOBAL_OPT][POCET_JAZYKOV + 1];

#define POCET_DALSICH_CONF 3

extern char cfg_http_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
extern char cfg_http_display_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
extern char cfg_mail_address_default[POCET_JAZYKOV + 1][MAX_MAIL_STR];

#define CFG_OPTION_DEFAULT(i) cfg_option_default[i][_global_jazyk]

const long cfg_option_default_PROG[POCET_GLOBAL_OPT] = 
{130, 5376, 29432, 0, 0, 0, 0};

void readConfig(void);
void printConfig(void);

#endif /* __MYCONF_H_ */

