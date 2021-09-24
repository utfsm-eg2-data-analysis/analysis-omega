ThreePionFinder
===============

`ThreePionFinder` reads `GetSimpleTuple` files, collects all the events with at least $1 \pi^+$, $1 \pi^-$, and $2 \gamma$, forms all possible combinations and reconstructs the possible $\omega$ candidates.

## Compilation

Just execute:

```
make
```

## Usage

To select a file with the following name scheme `pruned<target>_<rn>.root`, combine all the final-state particles per event and **reconstruct** the possible $\omega$ candidates:

```
./ThreePionFinder_<kind> -t<target> -r<rn>
```

Where:

* `<kind>` = `data` or `sim`
* `<target>` = `D`, `C`, `Fe`, `Pb`
* `<rn>` = string to identify the run number

One can also generate **event-mixed background** by running the following command. A file with the following name scheme `redu<target>_<rn>.root` must exist in the same directory.

```
./ThreePionFinder_<kind> -t<target> -r<rn> -m<pid>
```

Where:

* `<pid>` corresponds to the particle to swap, which can be:
  * `211` : swap all the positive pions
  * `-211` : swap all the negative pions
  * `111` : swap all the neutral pions (pair of gammas)
  * `999` : swap all pions
