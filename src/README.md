# analysis-omega/src

Here are located all the source codes of every program and routine used in the analysis.

* `GetSimpleTuple` (described below)

* `FilterNCombine` (described below)

* `MakePlots`
  plots different kinematic variables (kinvar) for data, simrec or gsim

* `MakePlots-DvsR` ("Data vs Reconstructed")
  plots the same kinvar for data and simrec

* `MakePlots-DvsD` ("Data vs Data")
  plots different kinvar for a same data sample for comparison
  (for example, IMD vs IM)

* `MakePlots-2D`
  does 2D histograms, generally `Q2:Nu` and `Z:Pt2` for data and simrec

* `GetQuantiles`
  fix a kinvar and fix a number! it obtains the equally distributed bins

* `GetElectronNumber`
  it obtains the electron numbers, directly from pruned data

* `MakeRooFits`
  main program for the bkg subtraction
  it is suggested to run it twice, to gather better fit ranges

* `PlotParams`
  plot the parameter results of the fits

* `MakeMR-nbs`
  from the fits results, calculates MR integrating `n*sigma` around the peak
  `nbs` stands for no background subtraction

* `MakeMR-bs`
  from the fits results, calculates MR direcly from the omega number
  and bkg number parameters

* `GetEvents`
  extract the numbers of events in a raw simulation file

* `MakeSimFits`
  main program for the Acceptance
  it is suggested to run it twice, to gather better fit ranges

* `Acceptance`
  does the acceptance from filtered simulation files
  
* `CutFlow`
  does a cut flow chart from raw data files

Others programs are:

* `Dalitz` Saga
* `SystPi0` Saga
* `MakeMR-sn` and `MakeMR-sim`
* `DiffractiveProcesses`
* `CheckGSIMCards`
* `OnLuminosities`
* `SumPtVectors`

## Stage 1: `GetSimpleTuple`

Takes **pass2-cooked** data by using `Analyser` and `ClasTool` to filter the signals
and assign the respective particles identification.

It employs `Analyser` (especifically, the `aborquez/analysis-omega` branch),
all particle id cuts are described in `Analyser/doc/CUTS.md`

The corrections applied in this stage are: (they are documented in `Analyser/doc/CORR.md`)

* Vertex correction
* Time correction
* Sampling fraction cut
* DC fiducial cut

## Stage 2: `FilterNCombine`

Takes the pruned data and keeps every omega candidate,

The corrections applied in this stage are:

* Gamma's energy correction, based on Taisiya's Mineeva Analysis
* Gamma's momentum correction, using the ECPB treatment
* Pion's energies derived from detected momentum and pdg mass value

## Post-FilterNCombine

For all the posterior programs (ie: `MakePlots`, `MakeRooFits`, etc.), all the following
cuts are recommended (they are also described in `include/analysisConfig.h`)

* DIS cuts:
  * `Q2 > 1`
  * `W > 2`
  * `y < 0.85`
* Neutral pion id from reconstruction
* Exclusion of charged kaons' band
* Electron/photon opening angle
* Electron/charged pion vertex matching

More optional cuts:

* Quality cuts:
  * Low momentum cut `P > 0.15` for positive pions
  * Low momentum cut `P > 0.15` for negative pions
  * Low momentum cut `P > 0.15` for gammas
* SC TOF `M^2` for photons
* Beta cut for pions
* `PhiPQ` cut
