#!/usr/bin/perl

use strict;
use warnings;

my $dir_to_open = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/result";
my $dir_to_open_1 = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/scheduler/tmp";
my $dir_to_open_2 = "/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/scheduler/out";

#tmp/

opendir my $dh, $dir_to_open or die " Could not open $!\n";

my @unsorted;


while(my $thing = readdir $dh)
{

    if($thing =~ m/entryRangeEffCorr_\d{1,4}_\w*/)
    {
	my @aFiles = split /_/, $thing;
	push(@unsorted, $aFiles[1]);
	#print "$aFiles[1]\n";
       # print " $thing \n";
    }

}

closedir $dh;
my @sorted = sort{$a <=> $b} @unsorted;


my %missingnum;
for(my $i=0; $i<=3000; $i++)
{
    $missingnum{$i} = 0;
}

foreach my $number (@sorted)
{
    $missingnum{$number} = 1;
    #print "$number \n";
}
opendir my $dh_1, $dir_to_open_1 or die " Could not open $dir_to_open_1 $!\n";

my %missingJobid;

while(my $thing_1 = readdir $dh_1)
{
  if($thing_1 =~ m/entryRangeEffCorr_\d{1,4}_\w*\.out/)
  {
     #print "$thing_1\n";
     my @aFiles = split /_/, $thing_1;
     $missingJobid{$aFiles[1]} = $aFiles[2];


  }
}
closedir $dh_1;
#my @missingEntry;

#Keys in missingnum and missingJobid match here
chdir "${dir_to_open_2}";

foreach my $i (keys %missingnum)
{
    if($missingnum{$i}==0)
    {
	print "$i $missingJobid{$i}\n";
	#system ("cd ${dir_to_open_2}/") or die "could not execute $!\n";
	#my $out = `cd ${dir_to_open_2}`;

	#print "$out\n";
	#my $pwdout = `pwd`;
	#print "$pwdout\n";
	#system("ls *$missingJobid{$i}*");
	print ("star-submit -r 0 $missingJobid{$i}.session.xml\n");

	#system ("star-submit -r 0 $missingJobid{$i}.session.xml\n");# or die "could not execute $!\n";
    }

}
#system("ls -a") or die "could not execute $!\n";

#foreach my $i (@missingEntry)
#{
    #my $entry = $missingEntry[$i];
    #print "$entry \n";
   # while(my $thing_1 = readdir $dh_1)
   # {
   #	    #print "$missing \n";
    #  if($thing_1 =~ m/entryRange_$entry*/)
     # {
	  #my @aFiles_1 = split /_/, $thing_1;
	  #push(@unsorted, $aFiles[1]);
	  #print "$aFiles_1[1]\n";
	  #print "$aFiles_1[2]\n";
#	   print " $thing_1 \n";
 #     }

  #  }
#}
#opendir my $dh_1, $dir_to_open_1 or die " Could not open $dir_to_open_1 $!\n";

`ls .`;

#`ls .`;
