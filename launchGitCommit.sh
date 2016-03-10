#!/bin/bash

clean

find . -name '*.orig' -delete

git add .

echo "Cleaned and added with .gitignore"

git commit

echo "Commited changes"