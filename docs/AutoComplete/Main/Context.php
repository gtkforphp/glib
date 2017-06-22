<?php

namespace Glib\Main;

class Context
{
    public function __construct()
    {
    }
    
    /*
    static public function getDefault() : Context
    {
    }
    
    static public function getThreadDefault() : Context
    {
    } */
    
    public function iteration(bool $may_block) : bool
    {
    }
    
    public function pending() : bool
    {
    }
    
    /*
     These need Source wrapped before they can be completed
     And may be wrapped into one or two find methods
    public function findSourceById(int sourceId) : Glib\Main\Source
    {
    }
   
    public function findSourceByData(mixed $args) : Glib\Main\Source
    {
    }
 
    public function findSourceByFuncsData(mixed $funcs, mixed $args) : Glib\Main\Source
    {
    }
    */
    
    public function wakeup() : void
    {
    }
    
    public function isOwner() : bool
    {
    }
    
    /*
    Waiting on condition and mutex to be wrapped
    public function wait(Glib\Condition $cond, Glib\Mutex $mutex) : bool
    {
    }
    */
    
    /**
     * Returns an array where [0] == boolean status
     * and [1] == integer priority
     */
    public function prepare() : array
    {
    }
    
    /*
    Waiting on pollfds to be wrapped
    public function query(int $max_priority, Glib\Poll\Fds $fds) : bool
    {
    }
    */
    
    /*
    Waiting on pollfds to be wrapped
    public function check(int $max_priority, Glib\Poll\Fds $fds) : bool
    {
    }
    */
    /*
    Waiting on gpollfunc
    public function setPoll(Glib\Poll $poll) : void
    {
    }

    public function getPoll() : Glib\Poll
    {
    }
    
    public function addPoll(GPollFd, int $priority) : void
    {
    }

    public function removePoll(GPollFd $pollfd) : void
    {
    }
    */
    
    public function dispatch() : void 
    {
    }
    
    /*
    this will mean wrappers around gsourcefunc, grpointer, and gdestroynotify
    public function invoke(callable $callback, ?int $priority, ?callable $notify_callback) : void
    {
    }*/
    
    public function pushThreadDefault() : void
    {
    }
    
    public function popThreadDefault() : void
    {
    }
    
}
