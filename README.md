
# TriggerStudies

> mkdir run
> cd run

> python ../python/procNtupleExample.py -i ../tree_Oct3_20kEvents.root -o TestFile.root

# Run over multiple files
> python     ../python/procNtupleExample.py -i inputList.txt  --inputList  -o TestFile.root

# Make ROC
> python ../python/makeROC.py -i TestFile.root -o TestROC.root
# Plot ROC
> cd ../../

checkout PlotTools
> git clone git@github.com:patrickbryant/PlotTools.git

> cd TriggerStudies/run

> python ../python/plotROC.py -i TestROC.root -o TestROC

# Plot All The Things
> python ../python/plots.py -i TestFile.root

This will make a run/plots directory with lots and lots of plots. 

# Making commits
Any new feature you wish to add will need to be in a new branch:
> git checkout -b feature/newFeature

And then rebase with master to make sure your branch is as up-to-date as possible when making the pull-request:
> git pull --rebase origin master

and push your commits to the remote (setting upstream):
> git push -u origin feature/newFeature

and then submit a pull request. When it’s been merged, you can run:
> git checkout master

> git pull --rebase origin master

> git remote prune origin