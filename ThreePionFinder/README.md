ThreePionFinder
===============

`ThreePionFinder` reads `GetSimpleTuple` files, collects all the events with at least $1\pi^+$, $1\pi^-$ and $2 \gamma$, forms all possible combinations and reconstructs the possible $\omega$ candidates.

## Compilation

Just execute:

```
make
```

## Execution

The execution steps require the following parameters:

* `<kind>` = `data` or `sim`
* `<target>` = `D`, `C`, `Fe`, `Pb`
* `<rn>` = string to identify the run number
* `<pid>` = `211`, `-211`, `111`, `999`

To print usage and exit program:

```
./ThreePionFinder_<kind> -h
```

To select a file with the following name scheme `pruned<target>_<rn>.root`, combine all the final-state particles per event and reconstruct the possible $\omega$ candidates:

```
./ThreePionFinder_<kind> -t<target> -r<rn>
```

To select a file with the name scheme `pruned<target>_<rn>_red.root` and create artificial $\omega$ candidates from random events for the **Event Mixing** background subtraction method:

```
./ThreePionFinder_<kind> -t<target> -r<rn>_red -m<pid>
```
