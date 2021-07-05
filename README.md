# push_swap error tester

A small tester for 42 school's [push_swap project](./en.subject.pdf) that's focused on checking invalid arguments to the `push_swap` program and invalid input to the `checker` program, based on the real checker behavior (specifically tested with checker_Mac). \
This tester doesn't actually test the operations, only errors. \
There are plenty of other testers for score/performance, here are some of my favorites:

- [lmalki-h](https://github.com/lmalki-h/push_swap_tester)
- [minckim42](https://github.com/minckim42/push_swap_tester)
- [LeoFu9487](https://github.com/LeoFu9487/push_swap_tester)

# How to use

Copy `error_checker.sh` into the root of your project, and make sure that the name of the binaries are `push_swap` and `checker`. (If you have a Makefile, the script will make them for you).

Run the script with either of the following options:

```
-a, --all		check errors on both push_swap and checker programs.
-p, --push_swap		check errors on the push_swap program only.
-c, --checker		check errors on the checker program only.
```

e.g.: `./error_checker.sh -a`
