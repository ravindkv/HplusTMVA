
#//////////////////////////////////////////////////
#                                                 #
# Copy Ntuple root files from T2_IN_TIFR to T3.   #
# Merge them into a single root file at T3.       #
# Send the merged file back to T2_IN_TIFR.        #
# Store the full path of merged file for Analysis #
#                                                 #
#//////////////////////////////////////////////////


#import FWCore.ParameterSet.Config as cms
import os
import sys
import datetime


#USERS INPUTS
#-------------------------------
isMuon = False
isElectron = True
isMC = False
isData = True
#-------------------------------


#Sample paths at T2
muMC_T2Paths = []
muData_T2Paths = []
eleMC_T2Paths = []
eleData_T2Paths = []

def getSampName(line, sampName, sampPaths):
    if line.find(sampName)!=-1:
        s1 = line.replace("]","").split(",")
        for n in range(1, len(s1)-1):
            sampPaths.append(s1[n].replace(" ",""))

for line in open("ntupleT2Paths_20170919.txt"):
    line = line.strip()
    if len(line)!=0:
        getSampName(line, "MUON MC", muMC_T2Paths)
        getSampName(line, "MUON DATA", muData_T2Paths)
        getSampName(line, "ELECTRON MC", eleMC_T2Paths)
        getSampName(line, "ELECTRON DATA", eleData_T2Paths)


def execme(command):
    print "\033[01;32m"+ "Excecuting: "+ "\033[00m",  command
    os.system(command)

#T2 path of one sample
#/cms/store/user/rverma/multicrab_09april17/MuMC_20170409/TTJets_MuMC_20170409/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/TTJets_MuMC_20170409

#read T2 Paths of ntuples, merge them, send merged file back to T2
def mergeNtuples(T2Paths, range_):
    for m in range(range_):
        pathT2 = T2Paths[m].replace("'","")
        #print pathT2

        #local dir at T3 for the samples
        #dirT3 = pathT2.split("/")[-4]
        sampT3dir = pathT2.split("/")[-1]
        execme("rfdir  /dpm/indiacms.res.in/home/"+pathT2+ " >"+sampT3dir+".log")
	for line in open(sampT3dir+".log"):
	    line = line.strip()
	    sp1 = line.split(" ")
        execme("rfdir  /dpm/indiacms.res.in/home/"+pathT2+"/"+sp1[-1]+ " >"+sampT3dir+"_1.log")
	    
	for line in open(sampT3dir+"_1.log"):
	    line = line.strip()
	    sp2 = line.split(" ")
        execme("rfdir  /dpm/indiacms.res.in/home/"+pathT2+"/"+sp1[-1]+"/"+sp2[-1]+ " >"+sampT3dir+"_2.log")
	
	f = open(sampT3dir+"_Ntuples_Paths.log", "w")
	for line in open(sampT3dir+"_2.log"):
	    line = line.strip()
	    sp3 = line.split(" ")
	    print sp3[-1]
	    f.write(pathT2+"/"+sp1[-1]+"/"+sp2[-1]+"/"+sp3[-1]+"\n")
 	execme("rm "+sampT3dir+".log")	
 	execme("rm "+sampT3dir+"_1.log")	
 	execme("rm "+sampT3dir+"_2.log")	
	"""
        ############### COPY ###################
        #command to be excecuted to merge ntuples
        cmdT3 = []
        #cmdT3.append("mkdir %s" % sampT3dir)
        #cmdT3.append("cd %s" % sampT3dir)
        ##cmdT3.append("mkdir %s" % sampT3dir)
        ##cmdT3.append("cd %s" % sampT3dir)

        execme(cmdT3)
        #copy files from T2 to T3, get the last dir contaning ntuples
        #cmdT3.append("xrdcp -r root://se01.indiacms.res.in:1094/"+pathT2+" .")
        cmdT3_comb = ''
        for cmd in cmdT3:
            if cmd!=cmdT3[-1]:
                cmdT3_comb += cmd +" && "
            else:
                cmdT3_comb += cmd
        execme(cmdT3_comb)
        print  "\033[01;32m"+" Ntuples copied !""\033[00m"

        ################## MERGE #################
        cmdT3 = []
        for x in os.walk(sampT3dir):
            dirNtup = x[0].replace("failed","")
        print dirNtup
        #total number of ntuple files
        tot_files = len([name for name in os.listdir(dirNtup)])
        merged_ntuple = sampT3dir+ "_Ntuple_Merged.root"
        cmdT3.append("cd %s" %dirNtup)
        #merge all the ntuples by hadd command
        cmdT3.append("hadd -k "+ merged_ntuple+" "+ sampT3dir+"_Ntuple_{1.."+str(tot_files)+"}.root")

        #move the merged ntuple to back to T2
        #cmdT3.append("echo "+ "\033[01;32m"+"moving merged ntuple, back to T2 ..."+"\033[00m")
        cmdT3.append("xrdcp -r "+merged_ntuple+ " root://se01.indiacms.res.in:1094/"+pathT2)
        cmdT3.append("rm -r *")

        #execute all the commands, in one go
        cmdT3_comb = ''
        for cmd in cmdT3:
            if cmd!=cmdT3[-1]:
                cmdT3_comb += cmd +" && "
            else:
                cmdT3_comb += cmd
        execme(cmdT3_comb)
        print "\033[01;32m"+"merging done !" "\033[00m"
	"""

#muon channel
range_muMC = len(muMC_T2Paths)
range_muData = len(muData_T2Paths)
print range_muData
if isMuon:
    if isMC:
        mergeNtuples(muMC_T2Paths, range_muMC)
    if isData:
        mergeNtuples(muData_T2Paths, range_muData)

#electron channel
range_eleData = len(eleData_T2Paths)
if isElectron:
    if isMC:
        mergeNtuples(eleMC_T2Paths, range_eleMC)
    if isData:
        mergeNtuples(eleData_T2Paths, range_eleData)

#store the paths of all merged files
today_date = str(datetime.date.today()).replace("-","")
file_merged_paths = open("MergedT2Paths_"+ today_date +".txt", 'w')

all_merged_paths = []
def getMergedPath(ntuple_T2Paths):
    for n in range(len(ntuple_T2Paths)):
        all_merged_paths.append(ntuple_T2Paths[n]+"_Ntuple_Merged.root")
    all_merged_paths.append("\n")
'''
getMergedPath(muMC_T2Paths)
getMergedPath(muData_T2Paths)
getMergedPath(eleMC_T2Paths)
getMergedPath(eleData_T2Paths)
file_merged_paths.write(all_merged_paths)
'''

