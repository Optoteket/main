#!/bin/bash

clear

echo "Adding CPLEX module"

# Load module definitions
. /sw/modules/init/bash.init
module add cplex/12.5-fullampl
ampl < /edu/emeka813/MasterThesis/AMPLmodel/librarystaff.run
echo "Module added"
