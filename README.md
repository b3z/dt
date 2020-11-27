### What

> Gaining terminal independence for tasks.

dt emulates the detach feature of
screen, which allows a program to be executed in an environment that is
protected from the controlling terminal. 
That means the task running detached is not beeing affected by the terminal being
disconnected and can be accesed from other terminals.


### Why

* not as bulky as screen (actually pretty slim)
* `&` just doesn't do the job when sending jobs to background. They are still bound to the terminal session.


### How

Unix-domain sockets are used to represent sessions. These are network
sockets that are stored in the filesystem. 

```sh
$ dt -A /tmp/aTask ping 8.8.8.8 
```

This will ping 8.8.8.8 but lets you detach with `CTRL + \`. Detaching should be intuitiv for screen users.

### Compiling

```sh
$ ./configure
$ make
```

