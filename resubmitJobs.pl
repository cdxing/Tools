#!/usr/bin/perl
####################################################
#
# This Perl script is used to find missing jobs
# Auhtor: Ding Chen, David Kapukchyan
# Date: Sep.22 2020
#
# How to use this script:
#
# a) change the file paths: 1. $dir_to_open; 2.$dir_to_open_1
# They are the the paths of result .root files and scheduler .xml files
#
# b) change the total number of jobs of the scheduelr in the for loop of %missingnum
# %missingnum is a hash table for the missing jobs
#
# c) Depending on the THE_COMMOM_PATTERN_OF_RESULT_FILES,
# one may want to tweak the parameter of $aFiles, one can find an example in the while loop
# my $vAppend  = $aFiles[1]; # XX.picoDst.result.root
#       $JobID = $aFiles[0]; # JOBID
#
# d) Run this scipt:
# chmod u+x resubmitJobs.pl
# ./resubmitJobs.pl THE_COMMOM_PATTERN_OF_RESULT_FILES
#
####################################################
use strict;
use warnings;

my $dir_to_open = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/result";
#my $dir_to_open = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/result";
# Directory where the output files are

my $dir_to_open_1 = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/scheduler/tmp";
#my $dir_to_open_1 = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/scheduler/tmp";
# Directory where you submit jobs

#my $dir_to_open_2 = "/star/data01/pwg/dchen/Ana/fxtPicoAna/phiAna/phiInvMass/scheduler/tmp";

#tmp/

opendir my $dh, $dir_to_open or die " Could not open $!\n";
# define a handle to open $dir_to_open

my $name   = $ARGV[0];
# $ARGV[0] is the first input argument: ./myPerl1_jobID.pl AB8F79ABBB628CC0B96256E4863BF059
my $JobID;

my @unsorted;
# creat an unsorted array

# Read contents in the first directory
while(my $thing = readdir $dh)
{
    # Choose files which have the pattern "name"
    if($thing =~ m/$name\w*/)
    {
      my @aFiles   = split /_/, $thing;
	    #split the file name into several sections by "_"
	    #Example: AB8F79ABBB628CC0B96256E4863BF059_50.picoDst.result.root ==> @aFiles = {AB8F79ABBB628CC0B96256E4863BF059, 50.picoDst.result.root}
      my $vAppend  = $aFiles[7]; # Modify the parameter to get the last section divided by "_"
	    # 50.picoDst.result.root
      $JobID = $aFiles[6]; # Modify the parameter to get the JOBID
	    # AB8F79ABBB628CC0B96256E4863BF059
      my @aNumbers = split /\./, $vAppend;
	    #  50.picoDst.result.root ==> @aNumbers = {50, picoDst, result, root}
      push(@unsorted, $aNumbers[0]);
	    # Put 50 into array @unsorted

	    #print "$aNumbers[0]\n";
	    # print " $thing \n";
    }
}
closedir $dh;

my @sorted = sort{$a <=> $b} @unsorted;
# sort the array of numbers by order

my %missingnum;
# a hash of missing numbers
for(my $i=0; $i<=800; $i++) # modify the total # of Jobs here
{
    $missingnum{$i} = 0;
}

foreach my $number (@sorted)
{
    $missingnum{$number} = 1;
    #print "$number\n";
}

chdir "${dir_to_open_1}";
# change directory to the one submitting jobs

my @missingDst;
# an array of missing Dst
foreach my $i (keys %missingnum)
{
    if($missingnum{$i}==0)
    {
      push(@missingDst, $i);

      # print ("star-submit -r $i $JobID.session.xml\n");

    }

}
# print  join(',',@missingDst);
my $jobString = join(',',@missingDst);
# make array of missingDst into a string separated by ","

# print ("star-submit -r $jobString $JobID.session.xml\n");
system("star-submit -r $jobString $JobID.session.xml\n");
# Uncomment the line above to re-submit jobs directly
