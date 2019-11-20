The Bct.Common.Messages.Cpp folders are provided by the firefly team and can be grabbed from their git repo: 
http://usbsrdtfs18:8080/tfs/ActiveDevelopment/Common%20Components/_git/BCT.Common.Messages.Cpp
Check the branch! The develop branch was well loved, but master was out of date... really neat right?

Simulator note: To run on the simulator would take compiling with CPU=SIMPENTIUM, but I (Chris) just recieve seg faults when running.
It would be super valuable to have some automated unit tests, so this might be worth exploring more.

To build, either build the folder or add serialization to the tools' makefile targets

To run the RTP vxe on target, “You will need to place a copy of /WindRiver6.9/vxworks-6.9/target/lib/usr/root/PENTIUMgnu/bin/libc.so.1 
onto the Optia in /machine/tools or define a LD_LIBRARY_PATH to point to another directory on the Optia so that sql_rtp.vxe will load and run.”

If you get a S_rtpLib_INSTANTIATE_FAILED error, you need to transfer the file in binary mode.


*** BUILDING the serializer prototype, unit tests:
***   (NOTE: Since this is just a proto for now, I haven't put the effort into things like
***          checking cross-makefile dependencies, etc.)
----------------------------------------------------------------------------------------
0. Get the BCT.Common.Message.Cpp repo, put it under taos/base (see http://ceswiki/doku.php?id=optia:ser_deser_prototyping#accessing_the_bctcommonmessagecpp_source)	.
1. Go to the most recent updated_messages_files/YYYY-MM-DD folder.
2. Copy the (modified) *.h and *.cpp files to their respective subfolders under base/BCT.Common.Messages.Cpp. (ignore the *.orig.* ones – I saved them just for reference.)
   2a. Put a copy of Bct.Workflow.Aggregates.CPP.Test\src\AssessUnitTests.cpp in ..\test (needed for unit tests to build.)
3. Also copy the makefile.* to their respective subfolders in base\BCT.Common.Messages.Cpp\ (you can rename them to just ‘makefile’ for ease of building.)
4. cd base\BCT.Common.Messages.Cpp
5. cd Bct.Workflow.Aggregates.CPP.GeneratedCode\src; make
6. cd Bct.Workflow.Aggregates.CPPLib\BCT.RPNEvaluator.CPP\src; make
7. cd Bct.Workflow.Aggregates.CPPLib\src; make
8. cd Bct.Workflow.Aggregates.CPP.Test\src; make
9. cd Bct.Workflow.Aggregates.CPP.Test\test; make
10. cd tools\serialization; make

*** RUNNING the serializer proto, and the unit tests, on Optia:
----------------------------------------------------------------
FTP tools/serialization/serialize_test.vxe file to /machine/tools/
FTP base/BCT.Common.Messages.Cpp/Bct.Workflow.Aggregates.CPP.Test/test/unit_test.vxe to /machine/tools/
Telnet to the machine
-> cmd
[vxWorks *]# cd /machine/tools
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/serialize_test.vxe        //serialize proto
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/serialize_test.vxe -- -d  //de-serialize proto
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/unit_test.vxe             
	...or, to get more debug info:
[vxWorks *]# rtp exec -u 16834 -c /machine/tools/unit_test.vxe -- -r xml


/* EOF */

