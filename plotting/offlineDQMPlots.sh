input=$1
echo $input
output=$2
monName=$3
cmd="python3"
#cmd="echo python3"
$cmd TriggerStudies/plotting/MakeOffToOffComparison.py --in $input --out $output  --labName Reference,$monName
#$cmd TriggerStudies/plotting/OffToOffPlots.py $input --labName Monitored,Reference --out $output
$cmd TriggerStudies/plotting/OffvsOff_BvL.py --input $input  --out $output --labName Reference,$monName
$cmd TriggerStudies/plotting/makeRocCurvesOffToOff.py --in $input --out $output --labName Reference,$monName
$cmd TriggerStudies/plotting/makeOfflineDQMPresentation.py -d $output -n ${output}/${output}_slides
