
#//////////////////////////////////////////////////
#                                                 #
# Get total Ntuples tobeprocessed form condor dir #
# Get processed Ntuples from condor output        #
# Get paths of the unprocessed Ntuples            #
#                                                 #
#//////////////////////////////////////////////////


import os
import sys
import datetime


#Sample paths at T2
processedPaths = open("procNtuples.log", "w")

#condor output histo files
print ""
print"----------------------------------------------------"
print" Fetching the un-processed ntuples, please wait ... "
print"----------------------------------------------------"
for line_out in open("outHistoFiles.log"):
    line_out = line_out.strip()
    split_line_out = line_out.split("/")
    ntuple_out = split_line_out[-1].replace("_Anal", "")
    #print ntuple_out
    for line_in_all_ntuple in open("allNtuples.log"):
        ntuple_input = line_in_all_ntuple.strip()
	if ntuple_out in ntuple_input:
	    processedPaths.write(ntuple_input+"\n")
processedPaths.close()

##------------------------------------------------
# compare the two file, output the unmatched lines
##------------------------------------------------
def compare1(File1,File2):
    with open(File1,'r') as f1:
        d=set(f1.readlines())
    with open(File2,'r') as f2:
        e=set(f2.readlines())
    open('unProcNtuples1.log','w').close() #Create the file
    with open('unProcNtuples1.log','a') as f:
        for line in list(d-e):
           f.write(line)
	   #print line

def compare2(File1, File2):
    with open(File1, 'r') as file1:
        with open(File2, 'r') as file2:
            diff = set(file1).difference(file2)
    #same.discard('\n')
    with open('unProcNtuples.log', 'w') as file_out:
        for line in diff:
            file_out.write(line)


#compare("allNtuples.log", processedPaths)
compare2("allNtuples.log", "procNtuples.log")

print ""
print"----------------------------------------------------"
print": 		Done       			 :"
print": 	See unProcNtuples.log                    :"
print"----------------------------------------------------"

