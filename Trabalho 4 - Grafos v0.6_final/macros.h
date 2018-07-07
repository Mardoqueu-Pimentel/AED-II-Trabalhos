#ifndef MACROS_H
#define MACROS_H

enum TYPE{
	CHAR, UCHAR, INT, UINT, FLOAT, DOUBLE, LDOUBLE, BOOL
};
void macros_debug (const char *s, ...);

#define DBUG(x...)\
macros_debug(#x, x)

#define log_info(M, ...)\
fprintf(\
	stderr,\
	"[INFO] (%s:%d) " M "\n",\
	__FILE__,\
	__LINE__,\
	##__VA_ARGS__\
)

#define call(conteiner, obj)\
conteiner->all(conteiner, obj)

#define cany(conteiner, obj)\
conteiner->any(conteiner, obj)

#define cassign(conteiner, param...)\
conteiner->assign(conteiner, param)

#define cback(conteiner)\
conteiner->back(conteiner)

#define copy(conteiner)\
conteiner->copy(conteiner)

#define cget(conteiner, param...)\
conteiner->get(conteiner, param)

#define cpop(conteiner)\
conteiner->pop(conteiner)

#define cpush(conteiner, obj...)\
conteiner->push(conteiner, obj)

#define csize(conteiner)\
conteiner->size(conteiner)

#endif