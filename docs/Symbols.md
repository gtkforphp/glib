# Glib Symbols

## Glib Fundamentals

### Version Information

| Symbol | PHP | Notes |
| --- | --- | --- |
| glib_check_version() | Glib\check_version() | namespace function |
| GLIB_VERSION_CHECK | Glib\check_compiled_version() | C Macro |
| glib_major_version | Glib\major_version | namespaced constant |
| glib_minor_version | Glib\minor_version | namespaced constant |
| glib_micro_version | Glib\micro_version | namespaced constant |
| glib_binary_age | Glib\binary_age | namespaced constant |
| glib_interface_age | Glib\interface_age | namespaced constant |
| GLIB_MAJOR_VERSION | Glib\MAJOR_VERSION | C compile time constant |
| GLIB_MINOR_VERSION | Glib\MINOR_VERSION | C compile time constant |
| GLIB_MICRO_VERSION | Glib\MICRO_VERSION | C compile time constant |
| GLIB_VERSION_2_26 | IGNORED | C Macro |
| GLIB_VERSION_2_28 | IGNORED | C Macro |
| GLIB_VERSION_2_30 | IGNORED | C Macro |
| GLIB_VERSION_2_32 | IGNORED | C Macro |
| GLIB_VERSION_2_34 | IGNORED | C Macro |
| GLIB_VERSION_2_36 | IGNORED | C Macro |
| GLIB_VERSION_2_38 | IGNORED | C Macro |
| GLIB_VERSION_2_40 | IGNORED | C Macro |
| GLIB_VERSION_2_30 | IGNORED | C Macro |
| GLIB_VERSION_2_42 | IGNORED | C Macro |
| GLIB_VERSION_2_44 | IGNORED | C Macro |
| GLIB_VERSION_2_46 | IGNORED | C Macro |
| GLIB_VERSION_2_48 | IGNORED | C Macro |
| GLIB_VERSION_2_50 | IGNORED | C Macro |
| GLIB_VERSION_MIN_REQUIRED | IGNORED | C Macro |
| GLIB_VERSION_MAX_ALLOWED | IGNORED | C Macro |
| GLIB_DISABLE_DEPRECATION_WARNINGS | IGNORED | C Macro |	

### Basic Types

| Symbol | PHP | Notes |
| --- | --- | --- |
| gint | IGNORED | use php's integer (long) |
| guint | IGNORED | use php's integer (long) |
| G_GINT64_CONSTANT() | IGNORED | C Macro |
| G_GUINT64_CONSTANT() | IGNORED | C Macro |
| G_GOFFSET_CONSTANT() | IGNORED | C Macro |
| gboolean | IGNORED | use php's boolean (zend_bool) |
| gpointer | IGNORED | pointers are hidden from php users |
| gconstpointer | IGNORED | pointers are hidden from php users |
| gchar | IGNORED | use php's string (char) |
| guchar | IGNORED | use php's string (char) |
| G_MININT | IGNORED | C Macro |
| G_MAXINT | IGNORED | C Macro |
| G_MAXUINT | IGNORED | C Macro |
| gshort | IGNORED | use php's integer (long) |
| G_MINSHORT | IGNORED | C Macro |
| G_MAXSHORT | IGNORED | C Macro |
| gushort | IGNORED | use php's integer (long) |	
| G_MAXUSHORT | IGNORED | C Macro |
| glong | IGNORED | use php's integer (long) |
| G_MINLONG | IGNORED | C Macro |
| G_MAXLONG | IGNORED | C Macro |
| gulong | IGNORED | use php's integer (long) |
| G_MAXULONG | IGNORED | C Macro |
| gint8 | IGNORED | use php's integer (long) |
| G_MININT8 | IGNORED | C Macro |
| G_MAXINT8 | IGNORED | C Macro |
| guint8 | IGNORED | use php's integer (long) |
| G_MAXUINT8 | IGNORED | C Macro |
| gint16 | IGNORED | use php's integer (long) |
| G_MININT16 | IGNORED | C Macro |
| G_MAXINT16 | IGNORED | C Macro |
| G_GINT16_MODIFIER | IGNORED | C Macro |
| G_GINT16_FORMAT | IGNORED | C Macro |	
| guint16 | IGNORED | use php's integer (long) |
| G_MAXUINT16 | IGNORED | C Macro |
| G_GUINT16_FORMAT | IGNORED | C Macro |
| gint32 | IGNORED | use php's integer (long) |	
| G_MININT32 | IGNORED | C Macro |
| G_MAXINT32 | IGNORED | C Macro |
| G_GINT32_MODIFIER | IGNORED | C Macro |
| G_GINT32_FORMAT | IGNORED | C Macro |
| guint32 | IGNORED | use php's integer (long) |	
| G_MAXUINT32 | IGNORED | C Macro |
| G_GUINT32_FORMAT | IGNORED | C Macro |
| gint64 | IGNORED | Use PHP's GMP |
| G_MININT64 | IGNORED | C Macro |
| G_MAXINT64 | IGNORED | C Macro |
| G_GINT64_MODIFIER | IGNORED | C Macro |
| G_GINT64_FORMAT | IGNORED | C Macro |				
| guint64 | IGNORED | use php's GMP |
| G_MAXUINT64 | IGNORED | C Macro |
| G_GUINT64_FORMAT | IGNORED | C Macro |	
| gfloat | IGNORED | use php's float (double) |
| G_MINFLOAT | IGNORED | C Macro |
| G_MAXFLOAT | IGNORED | C Macro |
| gdouble | IGNORED | use php's float (double) |
| G_MINDOUBLE | IGNORED | C Macro |
| G_MAXDOUBLE | IGNORED | C Macro |
| gsize | IGNORED | pointers are hidden from php users |
| G_MAXSIZE | IGNORED | C Macro |
| G_GSIZE_MODIFIER | IGNORED | C Macro |
| G_GSIZE_FORMAT | IGNORED | C Macro |
| gssize | IGNORED | pointers are hidden from php users |
| G_MINSSIZE | IGNORED | C Macro |
| G_MAXSSIZE | IGNORED | C Macro |
| G_GSSIZE_MODIFIER | IGNORED | C Macro |
| G_GSSIZE_FORMAT | IGNORED | C Macro |
| goffset | IGNORED | file offsets are hidden from php users |
| G_MAXOFFSET | IGNORED | C Macro |
| G_GOFFSET_MODIFIER | IGNORED | C Macro |
| G_GOFFSET_FORMAT | IGNORED | C Macro |
| gintptr | IGNORED | pointers are hidden from php users |
| G_GINTPTR_MODIFIER | IGNORED | C Macro |
| G_GINTPTR_FORMAT | IGNORED | C Macro |
| guintptr | IGNORED | pointers are hidden from php users |
| G_GUINTPTR_FORMAT | IGNORED | C Macro |
	
### Standard Macros

| Symbol | PHP | Notes |
| --- | --- | --- |
| G_IS_DIR_SEPARATOR() | IGNORED | write in PHP |
| MIN() | IGNORED | use php min() |
| MAX() | IGNORED | use php max() |
| ABS() | IGNORED | use php abs() |
| CLAMP() | IGNORED | write in PHP |
| G_STRUCT_MEMBER() | IGNORED | no structs in PHP |
| G_STRUCT_MEMBER_P() | IGNORED | no structs in PHP |
| G_STRUCT_OFFSET() | IGNORED | no structs in PHP |
| G_N_ELEMENTS() | IGNORED | no arrays on stack in PHP |
| G_OS_WIN32 | Glib\OS_WIN32 | defined only on windows |
| G_OS_UNIX | Glib\OS_UNIX | defined only on non-windows |
| G_DIR_SEPARATOR | IGNORED | use php DIRECTORY_SEPARATOR |
| G_DIR_SEPARATOR_S | IGNORED | use php DIRECTORY_SEPARATOR |
| G_SEARCHPATH_SEPARATOR | IGNORED | use php PATH_SEPARATOR |
| G_SEARCHPATH_SEPARATOR_S | IGNORED | use php PATH_SEPARATOR |
| TRUE | IGNORED | use php true |
| FALSE | IGNORED | use php false |
| NULL | IGNORED | use php null |
| G_MEM_ALIGN | IGNORED | php aligns memory |
| G_CONST_RETURN | DEPRECATED |  |

### Type Conversion Macros

| Symbol | PHP | Notes |
| --- | --- | --- |
| GINT_TO_POINTER | IGNORED | pointers are hidden from php users |
| GPOINTER_TO_INT | IGNORED | pointers are hidden from php users |
| GUINT_TO_POINTER | IGNORED | pointers are hidden from php users |
| GPOINTER_TO_UINT | IGNORED | pointers are hidden from php users |
| GSIZE_TO_POINTER | IGNORED | pointers are hidden from php users |
| GPOINTER_TO_SIZE | IGNORED | pointers are hidden from php users |

### Byte Order Macros

#define 	g_htonl()
#define 	g_htons()
#define 	g_ntohl()
#define 	g_ntohs()
#define 	GINT_FROM_BE()
#define 	GINT_FROM_LE()
#define 	GINT_TO_BE()
#define 	GINT_TO_LE()
#define 	GUINT_FROM_BE()
#define 	GUINT_FROM_LE()
#define 	GUINT_TO_BE()
#define 	GUINT_TO_LE()
#define 	GLONG_FROM_BE()
#define 	GLONG_FROM_LE()
#define 	GLONG_TO_BE()
#define 	GLONG_TO_LE()
#define 	GULONG_FROM_BE()
#define 	GULONG_FROM_LE()
#define 	GULONG_TO_BE()
#define 	GULONG_TO_LE()
#define 	GSIZE_FROM_BE()
#define 	GSIZE_FROM_LE()
#define 	GSIZE_TO_BE()
#define 	GSIZE_TO_LE()
#define 	GSSIZE_FROM_BE()
#define 	GSSIZE_FROM_LE()
#define 	GSSIZE_TO_BE()
#define 	GSSIZE_TO_LE()
#define 	GINT16_FROM_BE()
#define 	GINT16_FROM_LE()
#define 	GINT16_TO_BE()
#define 	GINT16_TO_LE()
#define 	GUINT16_FROM_BE()
#define 	GUINT16_FROM_LE()
#define 	GUINT16_TO_BE()
#define 	GUINT16_TO_LE()
#define 	GINT32_FROM_BE()
#define 	GINT32_FROM_LE()
#define 	GINT32_TO_BE()
#define 	GINT32_TO_LE()
#define 	GUINT32_FROM_BE()
#define 	GUINT32_FROM_LE()
#define 	GUINT32_TO_BE()
#define 	GUINT32_TO_LE()
#define 	GINT64_FROM_BE()
#define 	GINT64_FROM_LE()
#define 	GINT64_TO_BE()
#define 	GINT64_TO_LE()
#define 	GUINT64_FROM_BE()
#define 	GUINT64_FROM_LE()
#define 	GUINT64_TO_BE()
#define 	GUINT64_TO_LE()
#define 	GUINT16_SWAP_BE_PDP()
#define 	GUINT16_SWAP_LE_BE()
#define 	GUINT16_SWAP_LE_PDP()
#define 	GUINT32_SWAP_BE_PDP()
#define 	GUINT32_SWAP_LE_BE()
#define 	GUINT32_SWAP_LE_PDP()
#define 	GUINT64_SWAP_LE_BE()
Types and Values
#define 	G_BYTE_ORDER
#define 	G_LITTLE_ENDIAN
#define 	G_BIG_ENDIAN
#define 	G_PDP_ENDIAN

### Bounds-checking integer arithmetic

| Symbol | PHP | Notes |
| --- | --- | --- |
| g_uint_checked_add() | IGNORED | php converts type or use gmp |
| g_uint_checked_mul() | IGNORED | php converts type or use gmp |
| g_uint64_checked_add() | IGNORED | php converts type or use gmp |
| g_uint64_checked_mul() | IGNORED | php converts type or use gmp |
| g_size_checked_add() | IGNORED | php converts type or use gmp |
| g_size_checked_mul() | IGNORED | php converts type or use gmp |

### Numerical Definitions

| Symbol | PHP | Notes |
| --- | --- | --- |
| G_IEEE754_FLOAT_BIAS | IGNORED | bias of floats |
| G_IEEE754_DOUBLE_BIAS | IGNORED | bias of doubles |
| GFloatIEEE754 | IGNORED | internal details of floats |
| GDoubleIEEE754 | IGNORED | internal details of doubles |
| G_E | IGNORED | use M_E |
| G_LN2 | IGNORED | use M_LN2 |
| G_LN10 | IGNORED | use M_LN10 |
| G_PI | IGNORED | use M_PI |
| G_PI_2 | IGNORED | use M_PI_2 |
| G_PI_4 | IGNORED | use M_PI_4 |
| G_SQRT2 | IGNORED | use M_SQRT2 |
| G_LOG_2_BASE_10 | IGNORED | use M_LOG2E |

### Miscellaneous Macros

| Symbol | PHP | Notes |
| --- | --- | --- |
| g_auto() | IGNORED | gcc/clang specific c cleanup feature |
| g_autoptr() | IGNORED | gcc/clang specific c cleanup feature |
| G_DEFINE_AUTOPTR_CLEANUP_FUNC() | IGNORED | gcc/clang specific c cleanup feature |
| G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC() | IGNORED | gcc/clang specific c cleanup feature |
| G_DEFINE_AUTO_CLEANUP_FREE_FUNC() | IGNORED | gcc/clang specific c cleanup feature |
| G_VA_COPY() | IGNORED | php has variable args and ... |
| G_STRINGIFY() | IGNORED | C Macro |
| G_PASTE() | IGNORED | C Macro |
| G_STATIC_ASSERT() | IGNORED | Compile time assert |
| G_STATIC_ASSERT_EXPR() | IGNORED | Compile time assert |
| G_GNUC_CHECK_VERSION() | IGNORED | Compiler Macro |
| G_GNUC_ALLOC_SIZE() | IGNORED | Compiler Macro |
| G_GNUC_ALLOC_SIZE2() | IGNORED | Compiler Macro |
| G_GNUC_DEPRECATED_FOR() | IGNORED | Compiler Macro |
| G_GNUC_PRINTF() | IGNORED | Compiler Macro |
| G_GNUC_SCANF() | IGNORED | Compiler Macro |
| G_GNUC_FORMAT() | IGNORED | Compiler Macro |
| G_GNUC_PRINTF() | IGNORED | Compiler Macro |
| G_DEPRECATED_FOR() | IGNORED | PHP has it's own deprecation mechanism |	
| G_UNAVAILABLE() | IGNORED | Compiler Macro |
| G_LIKELY() | IGNORED | Compiler Macro |
| G_UNLIKELY() | IGNORED | Compiler Macro |
| G_INLINE_FUNC | DEPRECATED |  |
| g_autofree | IGNORED | Memory Management Macro |
| G_STMT_START | IGNORED | C Macro |
| G_STMT_END | IGNORED | C Macro |
| G_BEGIN_DECLS | IGNORED | C Macro |
| G_END_DECLS | IGNORED | C Macro |
| G_GNUC_EXTENSION| IGNORED | Compiler Macro |
| G_GNUC_CONST | IGNORED | Compiler Macro |
| G_GNUC_PURE | IGNORED | Compiler Macro |
| G_GNUC_MALLOC | IGNORED | Compiler Macro |
| G_GNUC_DEPRECATED | IGNORED | Compiler Macro |
| G_GNUC_BEGIN_IGNORE_DEPRECATIONS | IGNORED | Compiler Macro |
| G_GNUC_END_IGNORE_DEPRECATIONS | IGNORED | Compiler Macro |
| G_GNUC_NORETURN | IGNORED | Compiler Macro |
| G_GNUC_UNUSED | IGNORED | Compiler Macro |
| G_GNUC_NULL_TERMINATED | IGNORED | Compiler Macro |
| G_GNUC_WARN_UNUSED_RESULT | IGNORED | Compiler Macro |
| G_GNUC_FUNCTION | DEPRECATED |  |
| G_GNUC_PRETTY_FUNCTION | DEPRECATED |  |
| G_GNUC_NO_INSTRUMENT | IGNORED | Compiler Macro |
| G_HAVE_GNUC_VISIBILITY | IGNORED | Compiler Macro |
| G_GNUC_INTERNAL | IGNORED | Compiler Macro |
| G_GNUC_MAY_ALIAS | IGNORED | Compiler Macro |
| G_DEPRECATED | IGNORED | C Macro |
| G_STRLOC | IGNORED | C Macro |
| G_STRFUNC | IGNORED | C Macro |	

### Atomic Operations

All through for now all atomic operations are ignored, they may be implemented or partially implemented if/when threading is added

| Symbol | PHP | Notes |
| --- | --- | --- |
| g_atomic_int_get | IGNORED |  |
| g_atomic_int_set | IGNORED |  |
| g_atomic_int_inc | IGNORED |  |
| g_atomic_int_dec_and_test | IGNORED |  |
| g_atomic_int_compare_and_exchange | IGNORED |  |
| g_atomic_int_add | IGNORED |  |
| g_atomic_int_and | IGNORED |  |
| g_atomic_int_or | IGNORED |  |
| g_atomic_int_xor | IGNORED |  |
| g_atomic_pointer_get | IGNORED |  |
| g_atomic_pointer_set | IGNORED |  |
| g_atomic_pointer_compare_and_exchange | IGNORED | |
| g_atomic_pointer_add | IGNORED |  |
| g_atomic_pointer_and | IGNORED |  |
| g_atomic_pointer_or | IGNORED |  |
| g_atomic_pointer_xor | IGNORED |  |
| g_atomic_int_exchange_and_add | DEPRECATED |  |
| G_ATOMIC_LOCK_FREE | IGNORED | |

## Glib Core Application Support

### The Main Event Loop

| Symbol | PHP | Notes |
| --- | --- | --- |
| g_main_loop_new() | (__construct) |  |
| g_main_loop_ref() | (__construct) | |
| g_main_loop_unref() | (__destruct) |  |
| g_main_loop_run() | Glib\Main\Loop->run() |  |
| g_main_loop_quit() | Glib\Main\Loop->quit() |  |
| g_main_loop_is_running() | Glib\Main\Loop->isRunning() |  |
| g_main_loop_get_context() | Glib\Main\Loop->getContext() |  |
| g_main_new() | DEPRECATED |  |
| g_main_destroy() | DEPRECATED |  |
| g_main_run() | DEPRECATED |  |
| g_main_quit() | DEPRECATED |  |
| g_main_is_running() | DEPRECATED |  |
| g_main_loop_new() | (__construct) |  |
| g_main_context_ref() | (__construct) |  |
| g_main_context_unref() | (__destruct) |  |
| g_main_context_default() | Glib\Main\Context::getDefault() | static constructor |
| g_main_context_iteration() | Glib\Main\Context->iteration() |  |
| g_main_iteration() | DEPRECATED |  |
| g_main_context_pending() | Glib\Main\Context->pending() |  |
| g_main_pending() | DEPRECATED |  |
| g_main_context_find_source_by_id() | Glib\Main\Context->findSourceById() | TODO: waiting on source wrapping |
| g_main_context_find_source_by_user_data() | Glib\Main\Context->findSourceByData() | TODO: waiting on source wrapping |
| g_main_context_find_source_by_funcs_user_data() | Glib\Main\Context->findSourceByCallback() | TODO: waiting on source wrapping |
| g_main_context_wakeup() | Glib\Main\Context->wakeup() |  |
| g_main_context_acquire() | (used in prepare, query, check, dispatch) |  |
| g_main_context_release() | (used in prepare, query, check, dispatch) |  |
| g_main_context_is_owner() | Glib\Main\Context->isOwner() |  |
| g_main_context_wait() | Glib\Main\Context->wait() | TODO: condition and mutex wrapped |
| g_main_context_prepare() | Glib\Main\Context->prepare() |  |
| g_main_context_query() | Glib\Main\Context->query() | TODO: pollfds need to be fixed |
| g_main_context_check() | Glib\Main\Context->check() |  |
| g_main_context_dispatch() | Glib\Main\Context->dispatch() | TODO: pollfds need to be fixed |
| g_main_context_set_poll_func() | Glib\Main\Context->setPollFunc() | TODO: poll func marshaler |
| g_main_context_get_poll_func() | Glib\Main\Context->getPollFunc() | TODO: poll func marshaler |
| GPollFunc() | Glib\Main\Poll | Extends PHP closure |
| g_main_context_add_poll() | Glib\Main\Context->addPoll() | TODO: gpollfd stuff |
| g_main_context_remove_poll() | Glib\Main\Context->removePoll() | TODO: gpollfd stuff |
| g_main_depth() | Glib\Main::depth() |  |
| g_main_current_source() | Glib\Main::current_source() | TODO: get source objects working |
| g_main_set_poll_func() | DEPRECATED |  |
| g_main_context_invoke() | IGNORED | wrapped the full version only |
| g_main_context_invoke_full() | Glib\Main\Context->invoke() | TODO: need gsourcefun working |
| g_main_context_get_thread_default() | IGNORED | wrapped ref thread version instead |
| g_main_context_ref_thread_default() | Glib\Main\Context::getThreadDefault() | static construtor |
| g_main_context_push_thread_default() | Glib\Main\Context->pushThreadDefault() | static construtor |
| g_main_context_pop_thread_default() | Glib\Main\Context->popThreadDefault() | static construtor |


GSource * 	g_timeout_source_new ()
GSource * 	g_timeout_source_new_seconds ()
guint 	g_timeout_add ()
guint 	g_timeout_add_full ()
guint 	g_timeout_add_seconds ()
guint 	g_timeout_add_seconds_full ()
GSource * 	g_idle_source_new ()
guint 	g_idle_add ()
guint 	g_idle_add_full ()
gboolean 	g_idle_remove_by_data ()
void 	(*GChildWatchFunc) ()
GSource * 	g_child_watch_source_new ()
guint 	g_child_watch_add ()
guint 	g_child_watch_add_full ()
gint 	g_poll ()
void 	(*GSourceDummyMarshal) ()
GSource * 	g_source_new ()
GSource * 	g_source_ref ()
void 	g_source_unref ()
void 	g_source_set_funcs ()
guint 	g_source_attach ()
void 	g_source_destroy ()
gboolean 	g_source_is_destroyed ()
void 	g_source_set_priority ()
gint 	g_source_get_priority ()
void 	g_source_set_can_recurse ()
gboolean 	g_source_get_can_recurse ()
guint 	g_source_get_id ()
const char * 	g_source_get_name ()
void 	g_source_set_name ()
void 	g_source_set_name_by_id ()
GMainContext * 	g_source_get_context ()
void 	g_source_set_callback ()
gboolean 	(*GSourceFunc) ()
void 	g_source_set_callback_indirect ()
void 	g_source_set_ready_time ()
gint64 	g_source_get_ready_time ()
gpointer 	g_source_add_unix_fd ()
void 	g_source_remove_unix_fd ()
void 	g_source_modify_unix_fd ()
GIOCondition 	g_source_query_unix_fd ()
void 	g_source_add_poll ()
void 	g_source_remove_poll ()
void 	g_source_add_child_source ()
void 	g_source_remove_child_source ()
gint64 	g_source_get_time ()
void 	g_source_get_current_time ()
gboolean 	g_source_remove ()
gboolean 	g_source_remove_by_funcs_user_data ()
gboolean 	g_source_remove_by_user_data ()
Types and Values
| GMainContext | Glib\Main\Loop |  |
#define 	G_PRIORITY_HIGH
#define 	G_PRIORITY_DEFAULT
#define 	G_PRIORITY_HIGH_IDLE
#define 	G_PRIORITY_DEFAULT_IDLE
#define 	G_PRIORITY_LOW
#define 	G_SOURCE_CONTINUE
#define 	G_SOURCE_REMOVE
| GMainContext | Glib\Main\Context |  |
typedef 	GPid
#define 	G_PID_FORMAT
struct 	GPollFD
#define 	G_POLLFD_FORMAT
| GSource | Glib\Main\Source |  |
struct 	GSourceFuncs
struct 	GSourceCallbackFuncs


## Glib Utilities

### Timers

| Symbol | PHP | Notes |
| --- | --- | --- |
| g_timer_new() | (__construct) |  |
| g_timer_start() | Glib\Timer->start() |  |
| g_timer_stop() | Glib\Timer->stop() |  |
| g_timer_continue() | Glib\Timer->continue() |  |
| g_timer_elapsed() | Glib\Timer->elapsed() |  |
| g_timer_reset() | IGNORED | same as start, use start |
| g_timer_destroy() | (__destruct)|  |
| GTimer | Glib\Timer |  |

## Glib Data Types

## Deprecated APIs
All Ignored

## Glib Tools
All Ignored

old static glib python bindings

https://github.com/davidmalcolm/pygobject/tree/master/gi/_glib