input=$1
echo $input
output=$2
monName=$3



cmd=${4:-echo python3}
echo cmd=$cmd

#echo $cmd

$cmd TriggerStudies/plotting/MakeOffToOffComparison.py --in $input --out $output  --labName Reference,$monName
#$cmd TriggerStudies/plotting/OffToOffPlots.py $input --labName Monitored,Reference --out $output
$cmd TriggerStudies/plotting/OffvsOff_BvL.py --input $input  --out $output --labName Reference,$monName
$cmd TriggerStudies/plotting/innerHitvsNoInnerHit.py --input $input --out $output
$cmd TriggerStudies/plotting/jetDeltaHists_BvL.py --input $input  --out $output --labName Reference,$monName
$cmd TriggerStudies/plotting/makeRocCurvesOffToOff.py --in $input --out $output --labName Reference,$monName
$cmd TriggerStudies/plotting/makeOfflineDQMPresentation.py -d $output -n ${output}/${output}_slides
