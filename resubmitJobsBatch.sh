#!/bin/sh
#nJob1=$1
######################################################
#
# This script is for the resubmit jobs for analysis of Run 18 7.2 GeV
# Flow analysis
# author: Ding Chen
# date: 9/22/2020
#
######################################################
./resubmitJobs.pl sys_dca_var1_iter1
./resubmitJobs.pl sys_dca_var2_iter1
./resubmitJobs.pl sys_dedx_var1_iter1
./resubmitJobs.pl sys_dedx_var2_iter1
./resubmitJobs.pl sys_dipAngle_var1_iter1
./resubmitJobs.pl sys_mass2_var1_iter1
./resubmitJobs.pl sys_mass2_var2_iter1
./resubmitJobs.pl sys_nHitsFit_var1_iter1
./resubmitJobs.pl sys_nHitsFit_var2_iter1
./resubmitJobs.pl sys_nSigK_var1_iter1
./resubmitJobs.pl sys_nSigK_var2_iter1
./resubmitJobs.pl sys_pT_var1_iter1
./resubmitJobs.pl sys_pT_var2_iter1
./resubmitJobs.pl sys_ratio_var1_iter1
./resubmitJobs.pl sys_ratio_var2_iter1
./resubmitJobs.pl sys_TPCpid_var1_iter1
./resubmitJobs.pl sys_vr_var1_iter1
./resubmitJobs.pl sys_vr_var2_iter1
./resubmitJobs.pl sys_vtxDiff_var1_iter1
./resubmitJobs.pl sys_vtxDiff_var2_iter1
./resubmitJobs.pl sys_vz_var1_iter1
./resubmitJobs.pl sys_vz_var2_iter1
