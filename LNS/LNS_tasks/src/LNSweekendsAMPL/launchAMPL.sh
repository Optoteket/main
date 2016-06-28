#!/bin/bash

echo "Adding CPLEX module"

# Load module definitions
. /sw/modules/init/bash.init
module add cplex/12.5-fullampl
echo "Module added"
ampl < /edu/emeka813/MasterThesis/LNS/LNS_tasks/src/LNSweekendsAMPL/librarystaff10W.run
