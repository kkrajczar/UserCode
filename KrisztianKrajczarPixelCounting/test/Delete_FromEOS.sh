#!/bin/bash

#cmsLs /store/caf/user/krajczar/16x16_NEWCENT_SELECTION_v2_LessSelection_NoVtx | awk '{print $5}' > check.log
#cmsLs /store/caf/user/krajczar/B0_Express_HF | awk '{print $5}' > check.log
#cmsLs /store/caf/user/krajczar/B0_Express_NewTable | awk '{print $5}' > check.log
#cmsLs /store/caf/user/krajczar/MPproduction/mp0837 | awk '{print $5}' > check.log
cmsLs /store/caf/user/krajczar/MPproduction/mp0841 | awk '{print $5}' > check.log

declare -i i
i=0
for execute_file in `cat check.log`
do
i=i+1
cmsRm $execute_file
echo $i;
done

rm check.log

