*
*      Include file ecifl.inc
*

	integer Mhits,Msct

        parameter (Mhits = 10)
        parameter (Msct = 6)

        integer ifl(Mhits,Msct)
        common /ecifl/ ifl

*       integer  iflh1,ifl1(Mhits,Msct)
*       common /ecifl1/ ifl1
