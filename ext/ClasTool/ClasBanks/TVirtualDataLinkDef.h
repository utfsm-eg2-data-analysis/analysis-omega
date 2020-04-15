#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class TVirtualData;

// Custom streamer was not needed afterall....
// NOTICE: The - at the end tells rootcint NOT to generate the Streamer. 
// We suppy a custom streamer. This is needed because of the data type change for the
// status words between class version 2 and version 3.

#endif
