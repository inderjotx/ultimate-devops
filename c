#!/bin/bash

git add .
git commit -m "updating Jenkinsfile"

if [ "$1" == "y" ]; then
    git push origin
fi

