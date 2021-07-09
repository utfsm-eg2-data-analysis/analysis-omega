analysis-omega/scripts
======================

Here are located all the necessary **bash** scripts for sending jobs and executing bulk operations.

The `usm_` scripts are prepared to run exclusively at the USM cluster, `ui.hpc.utfsm.cl`, while the `jlab_` scripts are prepared to run exclusively at the JLAB cluster, `ifarmXXXX.jlab.org`.

To send jobs to the farm, one must execute:

```
./<script> <options>
```

For the $\omega$ analysis, there are two main scripts: `<cluster>_GTRE_data.sh` and `<cluster>_GTRE_data.sh` (`<cluster> = usm, jlab`). The first one is in charge of executing **GetSimpleTuple**, **ThreePionFinder**, **Reductor** and running the **Event Mixing** on the data. The second one is in charge of running the same programs, but this time for the simulations.

For the $\eta$ analysis, there are two main scripts: `<cluster>_TRE_data.sh` and `<cluster>_TRE_sim.sh`, which execute **TwoGammaFinder**, **Reductor** and the **Event Mixing** on data and simulations, respectively.
