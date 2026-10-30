# contributing to rswc

rswc is maintained on [sourcehut](https://sr.ht/~juanvel400/rswc) -- this document explains how to report bugs and send patches there.

## reporting bugs / requesting features

use the [ticket tracker](https://todo.sr.ht/~juanvel400/rswc). when filing a bug include

- your OS and rswc version
- steps to reproduce
- what you expected vs. what happened

## sending patches

rswc doesn't use GitHub-style pull requests. instead:

1. clone the repo and make your changes on a branch
2. commit with a clear, scoped message (see "commit style" below)
3. configure `git send-email` if you haven't already -- see
   [sr.ht's send-email tutorial](https://git-send-email.io/)
4. send your patch to: **~juanvel400/rswc-devel@lists.sr.ht**

```sh
 $ git send-email --to=~juanvel400/rswc-devel@lists.sr.ht origin/main..HEAD
```

## commit style

- one logical change per commit
- imperative, lowercase summary line (`add X`, not `Added X` or `adds X`) -- matches the existing log
- keep the summary under ~72 chars; use the body for anything that needs more explanation

## license

by contributing, you agree your changes are licensed under BSD-3-Clause, matching the rest of the project (see [LICENSE](LICENSE)).
