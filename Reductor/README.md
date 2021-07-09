Reductor
========

`Reductor` reduces `GetSimpleTuple` files into events that have at least 2 $\gamma$, 1 $\pi^+$, and 1 $\pi^-$, while `Reductor_2G` reduces them into events that have at least 2 $\gamma$.

## Compilation

Just execute:

```
make
```

## Execution

At least one `pruned<target>_<rn>.root` file must be located in the same directory as the executable. Usage is:

To print usage and exit program:

```
./Reductor -h
./Reductor_2G -h
```

To select the file to read:

```
./Reductor -t<target> -r<rn>
./Reductor_2G -t<target> -r<rn>
```
