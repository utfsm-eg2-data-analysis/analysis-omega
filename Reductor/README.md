Reductor
==========

Program that reduces GetSimpleTuple-formatted ROOT files into the events that have at least 2 gamma, 1 pi+, and 1 pi-.

## Execution of Reductor

At least one `pruned<target>_<rn>.root` file must be located in the same directory as the executable. Usage is:

* To print usage and exit program:

  ```
  ./Reductor -h
  ```

* To select the file to read:

  ```
  ./Reductor -t[target] -r[run number]
  ``` 
