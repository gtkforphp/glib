### Glib Fundamentals

### Version Information

| Symbol | PHP | Notes |
| --- | --- | --- |
| glib_check_version() | Glib\check_version() | namespace function |
| GLIB_VERSION_CHECK | Glib\check_compiled_version() | C Macro |
| glib_major_version | Glib::MAJOR_VERSION | namespaced constant |
| glib_minor_version | Glib::MINOR_VERSION | namespaced constant |
| glib_micro_version | Glib::MICRO_VERSION | namespaced constant |
| glib_binary_age | Glib::BINARY_AGE | namespaced constant |
| glib_interface_age | Glib::INTERFACE_AGE | namespaced constant |
| GLIB_MAJOR_VERSION | Glib::COMPILED_MAJOR_VERSION | C compile time constant |
| GLIB_MINOR_VERSION | Glib::COMPILED_MINOR_VERSION | C compile time constant |
| GLIB_MICRO_VERSION | Glib::COMPILED_MICRO_VERSION | C compile time constant |
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



GTimer					Glib\Timer
g_timer_new				(__construct)		
g_timer_start				Timer->start
g_timer_stop				Timer->stop
g_timer_elapsed				Timer->elapsed
g_timer_reset				IGNORED (use start)	
g_timer_destroy				(__destruct)

GMainLoop				Glib\Main\Loop
g_main_loop_new				(__construct)
g_main_loop_ref 			(__construct)
g_main_loop_unref 			(__destruct)
g_main_loop_run				Loop->run
g_main_loop_quit			Loop->quit
g_main_loop_is_running			Loop->isRunning
g_main_loop_get_context			Loop->getContext
g_main_new				IGNORED (use new Loop)
g_main_destroy				IGNORED (use unset(Loop))
g_main_run				IGNORED (use Loop->run)
g_main_quit				IGNORED (use Loop->quit)
g_main_is_running			IGNORED (use Loop->isRunning)

GMainContext				Glib\Main\Context
g_main_context_new			(__construct)
g_main_context_ref      		(__construct)
g_main_context_unref    		(__destruct)
g_main_context_aquire			(used in prepare, query, check, dispatch)
g_main_context_release			(used in prepare, query, check, dispatch)
g_main_iteration 			IGNORED (use Context->iteration)
g_main_pending				IGNORED (use Context->pending)
g_main_set_poll_func			IGNORED (use Context->setPoll)
g_main_context_get_thread_default	IGNORED (use Context->getThreadDefault)

Static:
g_main_context_default  		Context::getDefault (static constructor)
g_main_context_ref_thread_default	Context::getThreadDefault (static constructor)

Methods:
g_main_context_iteration		Context->iteration
g_main_context_pending			Context->pending
g_main_context_wakeup			Context->wakeup
g_main_context_is_owner			Context->isOwner
g_main_context_wait			Context->wait
g_main_context_prepare			Context->prepare
g_main_context_query			Context->query
g_main_context_check			Context->check
g_main_context_dispatch			Context->dispatch
g_main_context_set_poll_func		Context->setPoll
g_main_context_get_poll_func		Context->getPoll
g_main_context_add_poll			Context->addPoll
g_main_context_remove_poll		Context->removePoll
g_main_context_push_thread_default	Context->pushThreadDefault
g_main_context_pop_thread_default	Context->popThreadDefault

Merged Methods:
Might do these separate OR merged, waiting on source completion
g_main_context_find_source_by_id	Context->findSourceById
g_main_context_find_source_by_user_data Context->findSourceByData
g_main_context_find_source_by_funcs_user_data Context->findSourceByFuncsData

g_main_context_invoke
g_main_context_invoke_full		Context->invoke

functions in Glib\Main
g_main_depth		Glib\Main\depth() : int
g_main_current_source	Glib\Main\current_source() : Glib\Main\Source



GSource		Glib\Source

https://github.com/davidmalcolm/pygobject/tree/master/gi/_glib











