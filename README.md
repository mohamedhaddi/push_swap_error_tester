# push_swap error tester

A small tester for 42 school's [push_swap project](./subject/en.subject.pdf) that's focused on checking if the arguments to the `push_swap` program are well handled, as well as the operations input to the `checker` program, based on the real checker behavior at validating arguments and operations. (It was specifically tested with checker_Mac).

<img width="396" alt="image" src="https://user-images.githubusercontent.com/6943864/124407851-d10d0600-dd3c-11eb-87a9-e92983ff9e74.png"> <img width="415" alt="image" src="https://user-images.githubusercontent.com/6943864/124407888-e2eea900-dd3c-11eb-99be-8ed86cdf3271.png">

This tester doesn't actually test your operations output, there are plenty of other testers for checking your score/performance, these are some of my favorites:

- [lmalki-h/push_swap_tester](https://github.com/lmalki-h/push_swap_tester)
- [minckim42/push_swap_tester](https://github.com/minckim42/push_swap_tester)
- [LeoFu9487/push_swap_tester](https://github.com/LeoFu9487/push_swap_tester)

# Usage

Copy `error_checker.sh` into the root of your project, and make sure that the name of the binaries are `push_swap` and `checker`. (If you have a Makefile, the script will make them for you).

Run the bash script with any of the following options:

```
-a, --all		check errors on both push_swap and checker programs.
-p, --push_swap		check errors on the push_swap program only.
-c, --checker		check errors on the checker program only.
```

e.g.: `./error_checker.sh -a`
