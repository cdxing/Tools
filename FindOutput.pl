#!/usr/bin/perl
#0, 3000
#3001, 6000
#6001, 9000
#9001, 12000
#12001, 15000
#15001, 18000
#18001, 20689


use strict;
use warnings;

# 3 Directories:
# Dir 1: scheduler/out
# Dir 3: scheduler/tmp
my $dir_to_open = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/scheduler/out";
my $dir_to_open_1 = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/scheduler/tmp";

# entryRange low limit and up limit
my $lowLimit  = $ARGV[0];
my $upLimit   = $ARGV[1];

# open result/ directory
opendir my $dh, $dir_to_open or die " Could not open $!\n";
# Array of unsorted
my @unsorted;
while(my $thing = readdir $dh)
{

    if($thing =~ m/entryRange_\d{1,5}_\w*/)
    {
	     my @aFiles = split /_/, $thing;
       # entryRange_xxxxx_JOBID_0.err
       #
	     push(@unsorted, $aFiles[1]);
	     #print "$aFiles[1]\n";
       #print " $thing \n";
    }
}
closedir $dh;

# Array of sorted files
my @sorted = sort{$a <=> $b} @unsorted;

my %missingnum;
for(my $i=0; $i<=20689; $i++)
{
    $missingnum{$i} = 0;
}

foreach my $number (@sorted)
{
    $missingnum{$number} = 1;
    print "$number \n";
}
opendir my $dh_1, $dir_to_open_1 or die " Could not open $dir_to_open_1 $!\n";

my %missingJobid;

while(my $thing_1 = readdir $dh_1)
{
  if($thing_1 =~ m/entryRange_\d{1,5}_\w*\.err/)
  {
     #print "$thing_1\n";
     my @aFiles = split /_/, $thing_1;
     $missingJobid{$aFiles[1]} = $aFiles[2];
     #print "$missingJobid{$aFiles[1]}\n";

  }
}
closedir $dh_1;
#my @missingEntry;

#Keys in missingnum and missingJobid match here
chdir "${dir_to_open_1}";
foreach my $i (keys %missingnum)
{
    if ($i>=$lowLimit and $i<= $upLimit)
    {
      if($missingnum{$i}==0)
      {
  	   print "$i ";#$missingJobid{$i}\n";
  	   #system ("cd ${dir_to_open_2}/") or die "could not execute $!\n";
  	   #my $out = `cd ${dir_to_open_2}`;

  	   #print "$out\n";
  	   #my $pwdout = `pwd`;
  	   #print "$pwdout\n";
  	   #system("ls *$missingJobid{$i}*");
  	   #print ("star-submit-template -template submitPicoDstJobs1.xml -entities myFileName=entryRange_$i,entryTestPar1=$i\n");
  	   #system ("star-submit-template -template submitPicoDstJobs1.xml -entities myFileName=entryRange_$i,entryTestPar1=$1\n");# or die "could not execute $!\n";
      }
    }

}

`ls .`;
