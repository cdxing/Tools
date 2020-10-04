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
./resubmitJobs.pl EpCorrection_OUTPUT_sys_dca_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_dca_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_dedx_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_dedx_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_dipAngle_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaGap_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaGap_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaRange_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_etaRange_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_mass2_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_mass2_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_nHitsFit_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_nHitsFit_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_nSigK_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_nSigK_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_primary_var0_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_pT_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_pT_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_ratio_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_ratio_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_vr_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_vr_var2_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_vz_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_vz_var2_iter3
# ./resubmitJobs.pl EpCorrection_OUTPUT_sys_TPCpid_var0_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_TPCpid_var1_iter3
./resubmitJobs.pl EpCorrection_OUTPUT_sys_TPCpid_var2_iter3
