TwoGammaFinder
===============

`TwoGammaFinder` reads `GetSimpleTuple` files, collects all the events with at least $2 \gamma$, forms all possible combinations and reconstructs the possible $\eta$ candidates.

## Compilation

Just execute:

```
make
```

## Usage

To select a file with the following name scheme `pruned<target>_<rn>.root`, combine all the final-state particles per event and reconstruct the possible $\eta$ candidates:

```
./TwoGammaFinder_<kind> -t<target> -r<rn>
```

Where:

* `<kind>` = `data` or `sim`
* `<target>` = `D`, `C`, `Fe`, `Pb`
* `<rn>` = string to identify the run number
