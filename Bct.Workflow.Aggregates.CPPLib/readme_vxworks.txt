BCT.Common.Messages.Cpp notes for Optia/VxWorks

Last updated: 19-Dec-2019, by Peter Lochowicz
================================================================

The Bct.Common.Messages.Cpp folders are provided by the Firefly team and can be grabbed from their git repo: 
http://usbsrdtfs18:8080/tfs/ActiveDevelopment/Common%20Components/_git/BCT.Common.Messages.Cpp
Check the branch! The develop branch was well loved, but master was out of date... really neat right?

Simulator note: The code is not ready yet to be run in the simulator. Doing so would require building the RTP version of the simulator kernel first.

*** BUILDING the Aggregates library (AWL), unit tests, serialization test executable:
----------------------------------------------------------------------------------------
0. Get the BCT.Common.Message.Cpp repo (from develop branch), put it under taos/base (see http://ceswiki/doku.php?id=optia:ser_deser_prototyping#accessing_the_bctcommonmessagecpp_source).
   For example, your local folder may be /taos/base/BCT.Common.Messages.Cpp
1. cd Bct.Workflow.Aggregates.CPPLib/src; make -f makefile.vx
	- Will create aggregates_lib.a
2. Bct.Workflow.Aggregates.CPP.Test/test; make -f makefile.vx
	- Will create aggregates_unit_tests.vxe (Firefly's unit tests, which can be run on the Optia - see "RUNNING..." below).
	- (Will build aggregates_lib.a and generated_code_lib.a as needed.)
3. Bct.Workflow.Aggregates.CPP.Test/serialize_test; make -f makefile.vx
	- Will create serialize_test.vxe (HGT's de-/serialization test tool, which can be run on the Optia - see "RUNNING..." below).
	- (Will build aggregates_lib.a and generated_code_lib.a as needed.)

In order to do a clean build, first run "make -f makefile.vx BUILD_TYPE=CLEAN" in the respective folder. Then, run one of the above 1.-3. make commands.

*** RUNNING the serializer proto, and the unit tests, on Optia:
----------------------------------------------------------------
Prerequisite: FTP a copy /WindRiver6.9/vxworks-6.9/target/lib/usr/root/PENTIUMgnu/bin/libc.so.1 
onto the Optia in /machine/tools/.
If you get a S_rtpLib_INSTANTIATE_FAILED error, you need to transfer the file in binary mode.

FTP serialize_test/serialize_test.vxe file to /machine/tools/
FTP Bct.Workflow.Aggregates.CPP.Test/test/aggregates_unit_tests.vxe to /machine/tools/
Telnet to the machine
-> cmd
[vxWorks *]# cd /machine/tools
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/serialize_test.vxe        //serialize proto
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/serialize_test.vxe -- -d  //de-serialize proto
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/aggregates_unit_tests.vxe
	...or, to get more debug info:
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/aggregates_unit_tests.vxe -- -r xml


/* EOF */

