#!/bin/sh
######################################################
#
# This script is usd to find the resoltions for multiple EP files of Run 18 7.2 GeV
# Flow analysis
# author: Ding Chen
# date: 9/24/2020
#
######################################################
# string sys_object[18]  = {"primary", # 0
#                           "etaGap", # 1
#                           "etaRange", # 2
#                           "vz", # 3
#                           "vr", # 4
#                           "dedx", # 5
#                           "dca", # 6
#                           "nHitsFit", # 7
#                           "ratio", # 8
#                           "nSigK", # 9
#                           "mass2", # 10
#                           "pT", # 11
#                           "dipAngle", # 12
#                           "vtxDiff", # 13
#                           "mthdDiff", # 14
#                           "binning", # 15
#                           "TPCpid", # 16
#
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_dca_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_dca_var1_iter3.root",6,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_dca_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_dca_var2_iter3.root",6,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_dedx_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_dedx_var1_iter3.root",5,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_dedx_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_dedx_var2_iter3.root",5,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_dipAngle_var1_iter2_
# root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_dipAngle_var1_iter3.root",12,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaGap_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_etaGap_var1_iter3.root",1,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaGap_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_etaGap_var2_iter3.root",1,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaRange_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_etaRange_var1_iter3.root",2,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaRange_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_etaRange_var2_iter3.root",2,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_mass2_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_etaRange_var3_iter3.root",2,3,2)'
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_mass2_var1_iter3.root",10,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_mass2_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_mass2_var2_iter3.root",10,2,2)'
# resubmitJobs.pl EpCorrection_OUTPUT_sys_nHitsFit_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_nHitsFit_var1_iter3.root",7,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_nHitsFit_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_nHitsFit_var2_iter3.root",7,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_nSigK_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_nSigK_var1_iter3.root",9,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_nSigK_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_nSigK_var2_iter3.root",9,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_primary_var0_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_primary_var0_iter3.root",0,0,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_pT_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_pT_var1_iter3.root",11,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_pT_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_pT_var2_iter3.root",11,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_ratio_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_ratio_var1_iter3.root",8,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_ratio_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_ratio_var2_iter3.root",8,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_vr_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_vr_var1_iter3.root",4,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_vr_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_vr_var2_iter3.root",4,2,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_vz_var1_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_vz_var1_iter3.root",3,1,2)'
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_vz_var2_iter2_
root -b -q -l corrFinder2.cxx'("/mnt/c/Users/pjska/github/FlowExtractor/res_v2_7p2/sys/merged_EpCorrection_OUTPUT_sys_vz_var2_iter3.root",3,2,2)'
