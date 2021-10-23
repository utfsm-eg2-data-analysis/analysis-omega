Reductor
========

`Reductor` reduces `GetSimpleTuple` files into events that have at least 2 $\gamma$, 1 $\pi^+$, and 1 $\pi^-$.

## Requirements

* [**ClasTool**](https://github.com/utfsm-eg2-data-analysis/clas_software)

* **ROOT**: it must be the same version that was used to compile **ClasTool**.

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
```

To select the file to read:

```
./Reductor -t<target> -r<rn>
```

If it's a simulation file:

```
./Reductor -t<target> -r<rn> -s
```
