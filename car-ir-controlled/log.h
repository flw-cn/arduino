# ifndef __FLW_LOG_H__
# define __FLW_LOG_H__

# ifdef DEBUG
# define DBG_LOG( fmt, args... ) logMsg( fmt, ##args )
# else
# define DBG_LOG( fmt, args... )
# endif

void logMsg(const char *fmt, ...);

# endif
